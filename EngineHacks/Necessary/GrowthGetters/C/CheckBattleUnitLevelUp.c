#include "CheckBattleUnitLevelUp.h" 

#define regularGrowths 0 
#define fixedGrowths 1 
#define bracketedGrowths 2 

#define hpStat 0
#define strStat 1
#define sklStat 2
#define spdStat 3
#define defStat 4
#define resStat 5
#define lukStat 6
#define magStat 7

// repurpose bwl->moveAmt into bwl->promotionLvl 
u8 GetUnitPromotionLevel(struct Unit* unit) // https://github.com/FireEmblemUniverse/fireemblem8u/blob/ba48415eb29806813106e5874969421ea759d507/src/bmsave-bwl.c#L375
{
    extern u8 gBWLDataStorage[];
	int maxLevel = Class_Level_Cap_Table[unit->pClassData->number]; 
	int uid = unit->pCharacterData->number;
	if (uid > 0x45) { return maxLevel; }
	int result = *(gBWLDataStorage + 0x10 * (uid - 1) + 8); // repurpose bwl->moveAmt into bwl->promotionLvl 
	if (result < 10) { return 10; } 
	
	if (result > maxLevel) { return maxLevel; } 
    return result; 
}

// repurpose bwl->moveAmt into bwl->promotionLvl 
void SetUnitPromotionLevel(struct Unit* unit, int level) // https://github.com/FireEmblemUniverse/fireemblem8u/blob/ba48415eb29806813106e5874969421ea759d507/src/bmsave-bwl.c#L375
{
    extern u8 gBWLDataStorage[];
	int uid = unit->pCharacterData->number;
	if (uid > 0x45) { return; }
    gBWLDataStorage[(0x10 * (uid - 1)) + 8] = level; // repurpose bwl->moveAmt into bwl->promotionLvl 
}

u8 NewPromoHandler_SetInitStat(struct ProcPromoHandler *proc) // repoint so we also save the unit's promo level 
{
    proc->stat = PROMO_HANDLER_STAT_INIT;
	if (proc->unit) { 
		SetUnitPromotionLevel(proc->unit, proc->unit->level); 
	} 
    return 0;
}


int GetAverageStat(int growth, int stat, struct Unit* unit, int levels) { // unit required because bunit includes stats from temp boosters (eg. weapon provides +5 str) in their raw stats 
	int result = 0; 
	int baseStat = GetBaseStatFromDefinition(stat, unit); 
	result = ((growth * levels) / 100) + baseStat; 
	return result; 

} 

int GetStatFromDefinition(int id, struct Unit* unit) { // unit required because bunit includes stats from temp boosters (eg. weapon provides +5 str) in their raw stats 
	switch (id) { 
	case hpStat: return unit->maxHP; 
	case strStat: return unit->pow; 
	case sklStat: return unit->skl; 
	case spdStat: return unit->spd; 
	case defStat: return unit->def; 
	case resStat: return unit->res; 
	case lukStat: return unit->lck; 
	case magStat: return unit->_u3A; // mag 
	}
	return 0; 
} 

int GetBaseStatFromDefinition(int id, struct Unit* unit) { 
	switch (id) { 
	case hpStat: return unit->pCharacterData->baseHP + unit->pClassData->baseHP; 
	case strStat: return unit->pCharacterData->basePow + unit->pClassData->basePow; 
	case sklStat: return unit->pCharacterData->baseSkl + unit->pClassData->baseSkl; 
	case spdStat: return unit->pCharacterData->baseSpd + unit->pClassData->baseSpd; 
	case defStat: return unit->pCharacterData->baseDef + unit->pClassData->baseDef; 
	case resStat: return unit->pCharacterData->baseRes + unit->pClassData->baseRes; 
	case lukStat: return unit->pCharacterData->baseLck; // classes do not have base luck + unit->pClassData->baseLck; 
	case magStat: return MagCharTable[unit->pCharacterData->number].base + MagClassTable[unit->pClassData->number].base; 
	} 
	return 0; 
} 

int GetMaxStatFromDefinition(int id, struct Unit* unit) { // only used to avoid rerolls 
	switch (id) { 
	//case hpStat: return unit->pClassData->maxHP; // classes do not have hp caps 
	case strStat: return unit->pClassData->maxPow; 
	case sklStat: return unit->pClassData->maxSkl; 
	case spdStat: return unit->pClassData->maxSpd; 
	case defStat: return unit->pClassData->maxDef; 
	case resStat: return unit->pClassData->maxRes; 
	//case lukStat: return unit->pClassData->maxLck; // classes do not have luck caps 
	case magStat: return MagClassTable[unit->pClassData->number].cap; 
	} 
	return 255; // doesn't really matter much that you'll still roll for stat ups in hp / luck even if you've capped them 
} 

int GetNumberOfLevelUps(struct BattleUnit* bu) { // This doesn't really account for trainees, but there isn't much we can do about that 
	int numberOfLevels = bu->unit.level - 1; 
	if ((bu->unit.pCharacterData->attributes | bu->unit.pClassData->attributes) & CA_PROMOTED) { 
		numberOfLevels += GetUnitPromotionLevel(&bu->unit); 
	} 
	if (numberOfLevels < 0) return 0; // probably unnecessary 
	return numberOfLevels; 
} 

int NewGetStatIncrease(int growth, int mode, int stat, struct BattleUnit* bu,  struct Unit* unit) { 
    int result = 0;
	int currentStat = GetStatFromDefinition(stat, unit); 
	if (GetMaxStatFromDefinition(stat, unit) < currentStat+1) { return 0; } // no point trying to raise a stat if we've hit the caps. This'll improve our rerolled statups when caps have been hit 

	if (mode == fixedGrowths) { 
		int averageStat = GetAverageStat(growth, stat, unit, GetNumberOfLevelUps(bu)); 
		while (growth > 100) {
			result++;
			growth -= 100;
		}
		if (currentStat < averageStat) { 
			result++; 
		} 
		return result; 
	} 
	
	if (mode == bracketedGrowths) { 
		int averageStat = GetAverageStat(growth, stat, unit, GetNumberOfLevelUps(bu)); 
		while (growth > 100) {
			result++;
			growth -= 100;
		}
		if (currentStat >= (averageStat + PreventWhenAboveAverageBy_Link)) { 
		return result; 
		} 
		if ((currentStat + ForceWhenBelowAverageBy_Link) < averageStat) { 
		result++; 
		} 
		else if (Roll1RN(growth))
        result++;
		return result; 
	} 
	
	
	
    while (growth > 100) {
        result++;
        growth -= 100;
    }

    if (Roll1RN(growth))
        result++;

    return result;
}

extern int (*gGet_Hp_Growth)(struct Unit* unit); 
extern int (*gGet_Str_Growth)(struct Unit* unit); 
extern int (*gGet_Skl_Growth)(struct Unit* unit); 
extern int (*gGet_Spd_Growth)(struct Unit* unit); 
extern int (*gGet_Def_Growth)(struct Unit* unit); 
extern int (*gGet_Res_Growth)(struct Unit* unit); 
extern int (*gGet_Luk_Growth)(struct Unit* unit); 
extern int (*gMagGrowth)(struct Unit* unit); 

void CheckBattleUnitLevelUp(struct BattleUnit* bu) {
    if (CanBattleUnitGainLevels(bu) && bu->unit.exp >= 100) {
		int mode = regularGrowths; // default  
		struct Unit* unit = GetUnit(bu->unit.index); // required because bunit includes stats from temp boosters (eg. weapon provides +5 str) in their raw stats 
		if (GrowthOptions_Link.FIXED_GROWTHS_MODE) { 
			if (CheckEventId(GrowthOptions_Link.FIXED_GROWTHS_FLAG_ID) || (!GrowthOptions_Link.FIXED_GROWTHS_FLAG_ID)) { 
			mode = fixedGrowths; 
			}
		} 
		if (GrowthOptions_Link.STAT_BRACKETING_EXISTS) { 
			if (CheckEventId(BRACKETED_GROWTHS_FLAG_ID_Link) || (!BRACKETED_GROWTHS_FLAG_ID_Link)) { 
				if (mode != fixedGrowths) { 
					mode = bracketedGrowths; 
				} 
			}
		} 
		
		
        int statGainTotal = 0;

        bu->unit.exp -= 100;
        bu->unit.level++;

        if (UNIT_CATTRIBUTES(&bu->unit) & CA_MAXLEVEL10) {
            if (bu->unit.level == 10) {
                bu->expGain -= bu->unit.exp;
                bu->unit.exp = UNIT_EXP_DISABLED;
            }
        } else if (bu->unit.level >= Class_Level_Cap_Table[bu->unit.pClassData->number]) {
            bu->expGain -= bu->unit.exp;
            bu->unit.exp = UNIT_EXP_DISABLED;
        }

		int hpGrowth =  gGet_Hp_Growth(&bu->unit); 
		int strGrowth = gGet_Str_Growth(&bu->unit); 
		int sklGrowth = gGet_Skl_Growth(&bu->unit); 
		int spdGrowth = gGet_Spd_Growth(&bu->unit); 
		int defGrowth = gGet_Def_Growth(&bu->unit); 
		int resGrowth = gGet_Res_Growth(&bu->unit); 
		int lukGrowth = gGet_Luk_Growth(&bu->unit); 
		int magGrowth = 0; 
		if (gMagGrowth) { magGrowth = gMagGrowth(&bu->unit); } 
		
        bu->changeHP  = NewGetStatIncrease(hpGrowth, mode, hpStat, bu, unit);
        statGainTotal += bu->changeHP;

        bu->changePow = NewGetStatIncrease(strGrowth, mode, strStat, bu, unit);
        statGainTotal += bu->changePow;

        bu->changeSkl = NewGetStatIncrease(sklGrowth, mode, sklStat, bu, unit);
        statGainTotal += bu->changeSkl;

        bu->changeSpd = NewGetStatIncrease(spdGrowth, mode, spdStat, bu, unit);
        statGainTotal += bu->changeSpd;

        bu->changeDef = NewGetStatIncrease(defGrowth, mode, defStat, bu, unit);
        statGainTotal += bu->changeDef;

        bu->changeRes = NewGetStatIncrease(resGrowth, mode, resStat, bu, unit);
        statGainTotal += bu->changeRes;

        bu->changeLck = NewGetStatIncrease(lukGrowth, mode, lukStat, bu, unit);
        statGainTotal += bu->changeLck;
		
		bu->changeCon = NewGetStatIncrease(magGrowth, mode, magStat, bu, unit); // mag uses the changeCon byte (and always has) 
        statGainTotal += bu->changeCon;
		
        if ((statGainTotal < minStatGain_Link) && (mode != fixedGrowths)) {
            for (int attempts = 0; attempts < 5; attempts++) {

				// if we did not get atleast x stat ups on level, try each of these in order 
				// previously you'd often get +1 hp and nothing else on bad level ups because of the order 
				// so I've changed the order to Str > Mag > Spd > Def > Res > Luk > Hp > Skl 
				// you're more likely to get a more useful single stat levelup this way 
				if (!bu->changePow) { // don't count changePow multiple times in statGainTotal 
					bu->changePow = NewGetStatIncrease(strGrowth, mode, strStat, bu, unit);
					statGainTotal += bu->changePow;
					if (statGainTotal >= minStatGain_Link)
						break;
				} 
				if (!bu->changeCon) { 
					bu->changeCon = NewGetStatIncrease(magGrowth, mode, magStat, bu, unit); // mag uses the changeCon byte (and always has) 
					statGainTotal += bu->changeCon;
					if (statGainTotal >= minStatGain_Link)
						break;
				} 
				
				if (!bu->changeSpd) { 
					bu->changeSpd = NewGetStatIncrease(spdGrowth, mode, spdStat, bu, unit);
					statGainTotal += bu->changeSpd;
					if (statGainTotal >= minStatGain_Link)
						break;
				}
				
				if (!bu->changeDef) { 
					bu->changeDef = NewGetStatIncrease(defGrowth, mode, defStat, bu, unit);
					statGainTotal += bu->changeDef;
					if (statGainTotal >= minStatGain_Link)
						break;
				} 
				
				if (!bu->changeRes) { 
					bu->changeRes = NewGetStatIncrease(resGrowth, mode, resStat, bu, unit);
					statGainTotal += bu->changeRes;
					if (statGainTotal >= minStatGain_Link)
						break;
				} 
				
				if (!bu->changeLck) { 
					bu->changeLck = NewGetStatIncrease(lukGrowth, mode, lukStat, bu, unit);
					statGainTotal += bu->changeLck;
					if (statGainTotal >= minStatGain_Link)
						break;
				} 
				
				if (!bu->changeHP) { 
					bu->changeHP  = NewGetStatIncrease(hpGrowth, mode, hpStat, bu, unit);
					statGainTotal += bu->changeHP;
					if (statGainTotal >= minStatGain_Link)
						break;
				} 
				if (!bu->changeSkl) { 
					bu->changeSkl = NewGetStatIncrease(sklGrowth, mode, sklStat, bu, unit);
					statGainTotal += bu->changeSkl;
					if (statGainTotal >= minStatGain_Link)
						break;
				}
				
            }
        }

        CheckBattleUnitStatCaps(GetUnit(bu->unit.index), bu);
    }
}


