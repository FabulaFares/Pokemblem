#pragma once

#include "global.h"
#include "proc.h"
#include "fontgrp.h"
#include "ekrlevelup.h"

struct ProcPrepSallyCursor {
    PROC_HEADER;

    /* 2C */ int unk_2C;
    /* 30 */ int unk_30;
    /* 34 */ int unk_34;
    /* 38 */ int unk_38;
    /* 3C */ int unk_3C;
    /* 40 */ int unk_40;

    /* 44 */ u8 _pad44[0x49-0x44];

    /* 4A */ s16 unk_4A;
    /* 4C */ short unk_4C;

    /* 4E */ u8 _pad4E[0x53-0x4E];

    /* 54 */ struct APHandle* unk_54;

    /* 58 */ u32 unk_58;
};

struct PrepUnitList {
    struct Unit *units[0x40];
    int max_num;        /* A cunter maybe related to the amount of units in team */
    int latest_pid;     /* Last unit char-id when you leave the prep-unit-screen */
};

enum prep_atmenu_item_index {
    PREP_MAINMENU_UNIT = 0,
    PREP_MAINMENU_ITEM = 1,
    PREP_MAINMENU_SAVE = 2,
    PREP_MAINMENU_UNK3 = 3,
    PREP_MAINMENU_SUPPORT = 4,
    PREP_MAINMENU_CHECKMAP = 7,
};

struct ProcAtMenu {
    PROC_HEADER;
    /* 29 */ u8 unit_count;
    /* 2A */ u8 max_counter; // Total unit number can be on battle
    /* 2B */ u8 cur_counter; // Total unit number to be on battle
    /* 2C */ u8 unk_2C;
    /* 2D */ u8 cur_cmd;
    /* 2E */ u8 hand_pos;     // related to the displayed line maybe (also for handle sprite)
    /* 2F */ u8 unk_2F;
    /* 30 */ u8 unk_30;
    /* 31 */ u8 unk_31;
    /* 32 */ u8 unk_32;
    /* 33 */ u8 state;
    /* 34 */ u8 do_help;     // 1 if helpBox on
    /* 35 */ u8 unk_35;
    /* 36 */ bool8 end_prep;
    /* 38 */ u8 unk_38[0x3C - 0x38];
    /* 3C */ u16 yDiff; // y Pos offset of Unit SMS
    /* 3E */ u16 unk3E;
    /* 40 */ u32 xDiff;
};

struct ProcPrepMenuDesc {
    PROC_HEADER;
    /* 29 */ u8 _pad29_[0x4C - 0x29];
    /* 4C */ u16 unk4C;
    /* 4E */ u8 _pad4E_[0x58 - 0x4E];
    /* 58 */ int msg;
};

struct Proc08A184B4 {
    PROC_HEADER;
    /* 29 */ u8 _pad29_[0x4C - 0x29];
    /* 4C */ s16 game_lock;
};

struct ProcPrepSpecialChar {
     PROC_HEADER;
    /* 29 */ u8 _pad29_[0x2A - 0x29];
    /* 2A */ u8 unk2A;
    /* 2B */ u8 unk2B;
    /* 29 */ u8 _pad2C_[0x2F - 0x2C];
    /* 2F */ u8 unk2F;
    /* 30 */ u8 unk30;
    /* 31 */ u8 unk31;
    /* 32 */ u8 unk32;
    /* 33 */ u8 blink_Start;
    /* 34 */ u8 blink_B;
    /* 35 */ u8 unk35;
    /* 36 */ u16 unk36;
    /* 38 */ ProcPtr apProc;
};

struct ProcPrepMenuItem {
	PROC_HEADER;
	/* 29 */ u8 pad_29[0x2C - 0x29];
	/* 2C */ void (*effect)(ProcPtr);
	/* 30 */ int msg_rtext;
	/* 34 */ u32 msg;
	/* 38 */ u8 color;
	/* 39 */ u8 index;
	/* 3A */ u8 pad_3A[0x3C - 0x3A];
	/* 3C */ struct TextHandle text;
};

struct ProcPrepMenu {
    PROC_HEADER;
    /* 29 */ s8 do_help;
    /* 2A */ u8 cur_index;
    /* 2B */ u8 max_index;
    /* 2C */ void (*unk2C)(ProcPtr);
    /* 30 */ int msg_rtext;
    /* 34 */ s16 xPos;
    /* 36 */ s16 yPos;
    /* 38 */ struct ProcPrepMenuItem* cmds[0x8];
    /* 58 */ u8 (*on_PressB)(ProcPtr);
    /* 5C */ u8 (*on_PressStart)(ProcPtr);
    /* 60 */ u8 (*on_End)(ProcPtr);
};

struct ProcPrepUnit {
    PROC_HEADER;
    /* 29 */ u8 cur_counter; // Total unit number to be on battle
    /* 2A */ u8 max_counter; // Total unit number can be on battle
    /* 2B */ u8 unk_2B;
    /* 2C */ u16 list_num_pre; // pre unit index in prep-list(for scroll)
    /* 2E */ u16 list_num_cur; // current unit index in prep-list
    /* 30 */ u16 yDiff_cur; // y Pos offset of Unit SMS (current)
    /* 32 */ u16 unk_32;
    /* 34 */ u16 unk34;
    /* 36 */ u8 scroll_val; // each px to scroll at each frame
    /* 37 */ u8 button_blank;
    /* 38 */ u8 pad_38[0x3C - 0x38];
    /* 3C */ u16 unk_3C;
};

enum proc_label_prep_unit_select {
    PROC_LABEL_PREPUNIT_0 = 0,
    PROC_LABEL_PREPUNIT_IDLE,
    PROC_LABEL_PREPUNIT_2,
    PROC_LABEL_PREPUNIT_PRESS_SELECT,
    PROC_LABEL_PREPUNIT_PRESS_R,
    PROC_LABEL_PREPUNIT_PRESS_B = 0xA,
    PROC_LABEL_PREPUNIT_GAME_START = 0x63,
    PROC_LABEL_PREPUNIT_END = 0x64,
};

struct ProcPrepItemUse {
    PROC_HEADER;

    /* 2C */ struct Unit *unit;
    /* 30 */ int slot;
    /* 34 */ int unk34;
    /* 38 */ int slot_rtext;
    /* 3C */ int pos_subbox;
    /* 40 */ int game_lock;
};

enum proc_label_prep_item_use {
    PROC_LABEL_PREPITEMUSE_INIT,
    PROC_LABEL_PREPITEMUSE_MAIN,
    PROC_LABEL_PREPITEMUSE_CONFIRM,
    PROC_LABEL_PREPITEMUSE_EXEC_ITEMEFFECT,
    PROC_LABEL_PREPITEMUSE_EXEC_JUNA,
    PROC_LABEL_PREPITEMUSE_EXEC_PROMO,
    PROC_LABEL_PREPITEMUSE_EXIT_FADE,
    PROC_LABEL_PREPITEMUSE_END
};

struct ProcPrepItemUseBooster {
    PROC_HEADER;

    /* 2C */ int timer;
    /* 30 */ u8 status_pre[EKRLVUP_STAT_MAX];
    /* 38 */ u8 status_pst[EKRLVUP_STAT_MAX];
    /* 40 */ int xpos, ypos, width, height;
};

struct ProcPrepItemUseJunaFruit {
    PROC_HEADER;

    /* 2C */ int timer;
    /* 30 */ s8 lv_pre, lv_pst;

    /* 34 */ int xpos, ypos, width, height;
};

enum prepitem_textindex {
    TEXT_PREPITEM_HP,
    TEXT_PREPITEM_POW,
    TEXT_PREPITEM_SKL,
    TEXT_PREPITEM_SPD,
    TEXT_PREPITEM_LCK,
    TEXT_PREPITEM_DEF,
    TEXT_PREPITEM_RES,
    TEXT_PREPITEM_CON,
    TEXT_PREPITEM_CLASS,
    TEXT_PREPITEM_LEVEL,

    TEXT_PREPITEM_DESC1 = 25,
    TEXT_PREPITEM_DESC2 = 26,
    TEXT_PREPITEM_POPUP = 27,
    TEXT_PREPITEM_DESC3 = 29,
};

extern struct TextHandle gPrepItemTexts[32];

extern struct TextHandle gPrepMainMenuTexts[9];
extern u8 gPrepUnitPool[];
extern u8 gBanimScrRight[];
extern struct PrepUnitList gPrepUnitList;
// extern ??? gUnknown_020122D4
// extern ??? gUnknown_02012914
// extern ??? gUnknown_02012F54
// extern ??? gUnknown_02012F56
// extern ??? gUnknown_02012F58
// extern ??? gUnknown_02013458
// extern ??? gUnknown_02013460
// extern ??? gUnknown_02013510
// extern ??? gUnknown_02013538
// extern ??? gUnknown_02013560
// extern ??? gUnknown_02013570
// extern ??? gUnknown_02013588
// extern ??? gUnknown_02013590
// extern ??? gPrepUnitTexts
// extern ??? gUnknown_02013608
// extern ??? gUnknown_02013630
// extern ??? gUnknown_02013640
// extern ??? gUnknown_02013648
// extern ??? gUnknown_02013660
// extern ??? gUnknown_02013668
// extern ??? gUnknown_02013670
// extern ??? gUnknown_02013698
// extern ??? gUnknown_020136D8
// extern ??? sSupportScreenUnitCount
// extern ??? gUnknown_020136F4

extern struct ProcCmd gProcScr_SALLYCURSOR[];
extern u16 gBgConfig_ItemUseScreen[];
// extern ??? gUnknown_08A18200
extern CONST_DATA struct ProcCmd ProcScr_PrepMenuDescHandler[];
extern CONST_DATA struct ProcCmd ProcScr_AtMenu[];
extern CONST_DATA struct ProcCmd ProcScr_PrepPromoteDebug[];
extern CONST_DATA struct ProcCmd ProcScr_PrepTraineePromo[];
extern CONST_DATA u16 obj_8A1856E[];
extern CONST_DATA u16 obj_8A18582[];
extern CONST_DATA u16 obj_8A18590[];
extern CONST_DATA u16 obj_8A1859E[];
extern CONST_DATA u16 obj_8A185AC[];
extern CONST_DATA u16 *objs_8A18614[];
extern CONST_DATA struct ProcCmd ProcScr_PrepSpecialCharEff[];
extern CONST_DATA struct ProcCmd ProcScr_PrepScreenMenuDummyItem[];
extern CONST_DATA struct ProcCmd ProcScr_PrepMenu[];
// extern ??? gUnknown_08A18744
// extern ??? gUnknown_08A1874C
// extern ??? gUnknown_08A18754
// extern ??? gUnknown_08A1879C
// extern ??? gUnknown_08A187F0
// extern ??? ProcScr_menu_scroll
// extern ??? ProcScr_SallyCir
// extern ??? ProcScr_ViewCounter
// extern ??? gUnknown_08A188A8
// extern ??? gUnknown_08A188C0
// extern ??? gUnknown_08A188E4
// extern ??? gUnknown_08A188F8
// extern ??? gUnknown_08A18910
// extern ??? gUnknown_08A18928
// extern ??? gUnknown_08A18944
// extern ??? gUnknown_08A18964
// extern ??? gUnknown_08A1898C
// extern ??? ProcScr_PrepItemScreen
extern CONST_DATA u16 obj_08A18E34[];
extern CONST_DATA u16 obj_08A18E4E[];
extern CONST_DATA u16 obj_08A18E62[];
extern CONST_DATA u16 obj_08A18E76[];
extern CONST_DATA struct ProcCmd ProcScr_PrepUnitScreen[];
extern CONST_DATA struct ProcCmd ProcScr_PrepItemTradeScreen[];
extern CONST_DATA struct ProcCmd ProcScr_PrepItemUseScreen[];
extern CONST_DATA struct ProcCmd ProcScr_PrepItemUseBooster[];
extern CONST_DATA struct ProcCmd ProcScr_PrepItemUseJunaFruit[];
// extern ??? gUnknown_08A191F4
// extern ??? gUnknown_08A19200
// extern ??? gUnknown_08A19204
extern CONST_DATA struct ProcCmd ProcScr_PrepItemSupplyScreen[];
extern CONST_DATA struct ProcCmd ProcScr_BmSupplyScreen[];
extern CONST_DATA struct ProcCmd ProcScr_PrepItemListScreen[];
// extern ??? gUnknown_08A195F8
// extern ??? gUnknown_08A19608
// extern ??? gProcScr_FortuneSubMenu
extern int gUnknown_08A196BC[]; /* msg lists */
// extern ??? gUnknown_08A196D0
extern u16 CONST_DATA gUnknown_08A199C8[]; // TODO - Not sure; used in sallycursor
// extern ??? Img_PrepWindowSideBar
// extern ??? Pal_PrepWindowSideBar
// extern ??? gUnknown_08A19CCC
extern u16 gUnknown_08A1A084[]; // pal
// extern ??? gUnknown_08A1A0A4
// extern ??? gUnknown_08A1A23C
// extern ??? gUnknown_08A1A3FC
extern u8 CONST_DATA gUnknown_08A1A41C[];
extern u8 CONST_DATA gUnknown_08A1A434[];
extern u8 CONST_DATA gUnknown_08A1A474[];
extern u8 CONST_DATA gUnknown_08A1A4C8[];
// extern ??? gGfx_SupportScreenBanner
extern u8 CONST_DATA gUnknown_08A1AC88[];
extern u16 CONST_DATA gUnknown_08A1B0D8[];
extern u16 CONST_DATA gUnknown_08A1B154[]; // TODO - palette data from sallycursor
extern u16 CONST_DATA gPal_SupportScreenBanner[];
extern u16 CONST_DATA gUnknown_08A1B194[];
// extern ??? gUnknown_08A1B1FC
// extern ??? gUnknown_08A1B638
extern u8 CONST_DATA gUnknown_08A1B658[];
extern u8 CONST_DATA gUnknown_08A1B698[];
extern u8 CONST_DATA gUnknown_08A1B730[];
extern u8 CONST_DATA gUnknown_08A1B7C8[];
// extern ??? gUnknown_08A1B8B8
// extern ??? gUnknown_08A1B990
// extern ??? gUnknown_08A1B9EC
extern u16 CONST_DATA Img_PrepItemUseScreen[];
extern u16 CONST_DATA Tsa_PrepItemUseScreen[];
extern u8 gUnknown_08A1BBD0[]; // tsa?
// extern ??? gUnknown_08A1BCC0
// extern ??? gUnknown_08A1BD00
// extern ??? gUnknown_08A1BD40
// extern ??? gUnknown_08A1BD60
extern u8 gUnknown_08A1C704[]; // arrow gfx
// extern ??? gUnknown_08A1C7D8
// extern ??? gUnknown_08A1C8B4
// extern ??? gUnknown_08A1CD68
// extern ??? gUnknown_08A1CDC4
// extern ??? gUnknown_08A1D288
// extern ??? gUnknown_08A1D448
extern u16 CONST_DATA gUnknown_08A1D4C8[];
// extern ??? Img_PrepTextShadow
extern u8 CONST_DATA gUnknown_08A1D510[];
extern u16 CONST_DATA Pal_MapBattleInfoNum[]; // 'R is info' palette
// extern ??? Img_PrepPopupWindow
extern u8 Img_PrepWindow[];
// extern ??? gUnknown_08A1DB80
// extern ??? gTsa_SupportSubScreen
// extern ??? gGfx_SupportMenu
// extern ??? gPal_SupportMenu

/* sally-cursor */
int GetPlayerLeaderUnitId(void);
void sub_80332D0(void);
void sub_803334C(void);
void PrepMapMenu_OnViewMap(struct ProcPrepSallyCursor*);
void PrepMapMenu_OnFormation(struct ProcPrepSallyCursor*);
bool8 PrepMapMenu_OnStartPress(ProcPtr);
bool8 PrepMapMenu_OnBPress(ProcPtr);
void SALLYCURSOR_DeploySupplyUnit(void);
void PrepMapMenu_OnOptions(struct ProcPrepSallyCursor*);
void SALLYCURSOR_RemoveSupplyUnit(void);
void PrepMapMenu_OnSave(struct ProcPrepSallyCursor*);
void sub_8033468(struct ProcPrepSallyCursor*);
void sub_803348C(ProcPtr);
void PrepScreenProc_InitMapMenu(struct ProcPrepSallyCursor*);
void sub_80334CC(void);
void sub_80334E8(ProcPtr);
void sub_8033514(ProcPtr);
void sub_8033548(ProcPtr);
void sub_8033574(void);
void sub_8033608(void);
void sub_8033620(ProcPtr);
void PrepMapMenu_OnEnd(void);
void PrepScreenProc_StartMapMenu(struct ProcPrepSallyCursor*);
bool8 CanCharacterBePrepMoved(int);
void sub_8033770(struct ProcPrepSallyCursor*);
void sub_8033798(struct ProcPrepSallyCursor*);
void sub_80337B4(struct ProcPrepSallyCursor*);
void sub_80337D4(struct ProcPrepSallyCursor*);
void sub_80337F0(struct ProcPrepSallyCursor*);
void InitPrepScreenUnitsAndCamera(void);
void sub_80338C0(void);
void sub_8033940(struct ProcPrepSallyCursor*);
void PrepScreenProc_MapIdle(ProcPtr);
int sub_8033BF8(void);
void SALLYCURSOR6C_StartUnitSwap(struct ProcPrepSallyCursor*);
void sub_8033C90(struct ProcPrepSallyCursor*);
void sub_8033DD8(ProcPtr);
void sub_8033E08(ProcPtr);
void sub_8033E8C(void);
void sub_8033EA4(void);
void sub_8033EC0(ProcPtr);
void CallCursorShop(ProcPtr);
void PrepScreenProc_MapMovementLoop(ProcPtr);
void sub_8034078(ProcPtr);
void sub_8034090(ProcPtr);
void StartPrepSaveScreen(ProcPtr);
void sub_8034168(void);
void sub_8034194(void);
void sub_80341D0(void);
void sub_8034200(void);
void ShrinkPlayerUnits(void);
void EndPrepScreen(void);
bool8 sub_80342FC(void);

void Prep_DrawChapterGoal(int VRAM_offset, int pal);
// ??? PrepAtMenu_OnInit(???);
// ??? ResetPrepMenuDescTexts(???);
void ParsePrepMenuDescTexts(int msg);
// ??? DrawPrepMenuDescTexts(???);
// ??? PrepMenuDescOnInit(???);
// ??? PrepMenuDescOnParse(???);
// ??? PrepMenuDescOnDraw(???);
void sub_8095C00(int msg, ProcPtr parent);
// ??? sub_8095C2C(???);
// ??? sub_8095C50(???);
// ??? AtMenu_Reinitialize(???);
// ??? EndPrepAtMenuIfNoUnitAvailable(???);
// ??? sub_8095F2C(???);
void sub_8095F54(struct ProcAtMenu *proc);
void CleanupPrepMenuScreen(ProcPtr proc);
// ??? sub_8096004(???);
// ??? AtMenu_CtrlLoop(???);
// ??? AtMenuSetUnitStateAndEndFlag(???);
// ??? AtMenu_ResetScreenEffect(???);
// ??? AtMenu_ResetBmUiEffect(???);
// ??? AtMenu_StartSubmenu(???);
// ??? AtMenu_OnSubmenuEnd(???);
void sub_8096404();
void AtMenu_LockGame();
void AtMenu_UnlockGame();
void StartPrepAtMenu();
void StartPrepAtMenuWithConfig();
// ??? HasConvoyAccess_(???);
// ??? TraineePromo_ResetScreenEffect(???);
// ??? DoPromoteAnimForChar100(???);
// ??? IsGameLockLevelReserved(???);
// ??? NullExpForChar100AndResetScreen(???);
// ??? PrepPromoteDebugMaybe(???);
// ??? sub_8096668(???);
// ??? NewPrepScreenTraineePromotionManager(???);
// ??? PrepScreenTraineePromotionManagerExists(???);
// ??? PrepAtMenuExists(???);
// ??? PutObj8A1856E(???);
// ??? PutObj8A18582_WithConfigs(???);
// ??? PutObj8A18590_WithConfigs(???);
// ??? PutObj8A1859E_WithConfigs(???);
// ??? PutObj8A185AC(???);
// ??? sub_8096958(???);
// ??? ProcPrepSpChar_OnInit(???);
// ??? ProcPrepSpChar_Idle(???);
// ??? ProcPrepSpChar_OnEnd(???);

struct Unit *GetUnitFromPrepList(int index);
void RegisterPrepUnitList(int index, struct Unit *);
int PrepGetUnitAmount();
void PrepSetUnitAmount(int);
int PrepGetLatestCharId();
void PrepSetLatestCharId(int);
s8 IsCharacterForceDeployed(int char_id);
int CalcForceDeployedUnitCounts();
s8 SomeLeftoverFunctionThatReturns0(struct Unit *unit);
s8 IsUnitInCurrentRoster(struct Unit *unit);
void AtMenu_AddPrepScreenSupportMenuItem(struct ProcAtMenu *proc);
s8 CanPrepScreenCheckMap();
void InitPrepScreenMainMenu(struct ProcAtMenu*);
int GetLatestUnitIndexInPrepListByUId();
int PrepGetLatestUnitIndex();
void ReorderPlayerUnitsBasedOnDeployment();
void SortPlayerUnitsForPrepScreen();
void RemoveSomeUnitItems();
void MakePrepUnitList();
int UnitGetIndexInPrepList(int pid);
void PrepUpdateSMS();
int PrepGetDeployedUnitAmt(void);
void PrepAutoCapDeployUnits(struct ProcAtMenu* proc);
void EndSlidingWallEffectMaybe();
void EndBG3Slider_(void);
void PrepSpecialChar_BlinkButtonStart();
void PrepSpecialChar_BlinkButtonB();
ProcPtr StartPrepSpecialCharEffect(ProcPtr parent);
void EndPrepSpecialCharEffect(void);
// ??? sub_8096C34(???);
// ??? PrepMenu_OnInit(???);
// ??? PrepMenu_CtrlLoop(???);
// ??? PrepMenu_CtrlLoop(???);
// ??? PrepMenu_ShowActiveHand(???);
// ??? PrepMenu_OnEnd(???);
void StartPrepScreenMenu(ProcPtr);
void SetPrepScreenMenuOnBPress(const void*);
void SetPrepScreenMenuOnStartPress(const void*);
// ??? SetPrepScreenMenuOnEnd(???);
void SetPrepScreenMenuItem(int index, const void* func, int color, int msg, int msg_rtext);
void SetPrepScreenMenuSelectedItem(int);
int GetActivePrepMenuItemIndex();
// ??? DrawPrepScreenMenuFrameAt(???);
void SetPrepScreenMenuPosition(int x, int y);
// ??? GetPrepMenuItemAmt(???);
void EndPrepScreenMenu();
void ResetPrepMenuScreen();
int PrepScreenMenuExists();
void ShowPrepScreenMenuFrozenHand();
// ??? ShowPrepScreenMenuActiveHand(???);
void EnablePrepScreenMenu();
// ??? sub_80973B0(???);
// ??? sub_80973E4(???);
// ??? sub_809764C(???);
void sub_8097668(void);
void Delete6CMenuScroll(void);
void Make6CMenuScroll(ProcPtr);
void sub_80976AC(int, int);
void sub_80976CC(int, u16, u16, int);
void InitPrepSideBarImg(int, int);
void PrepStartSideBarScroll(ProcPtr, int, int, int, int);
// ??? sub_80977AC(???);
// ??? sub_80977EC(???);
// ??? sub_8097840(???);
// ??? sub_809788C(???);
// ??? sub_80979DC(???);
// ??? sub_8097AA0(???);
// ??? sub_8097AAC(???);
// ??? sub_8097ACC(???);
// ??? sub_8097B98(???);
// ??? sub_8097CC4(???);
// ??? GetConvoyItemCount_(???);
// ??? sub_8097CD8(???);
// ??? sub_8097D14(???);
void sub_8097D54(ProcPtr);
void sub_8097D68(ProcPtr);
// ??? sub_8097D80(???);
void sub_8097DA8(int, int, int, ProcPtr);
// ??? sub_8097DE0(???);
// ??? sub_8097E08(???);
s8 sub_8097E38(struct Unit *unit);
s8 sub_8097E74(struct Unit *unit);
// ??? sub_8097EA0(???);
// ??? sub_8097F44(???);
// ??? sub_8097F98(???);
// ??? sub_8097FDC(???);
// ??? sub_8098014(???);
// ??? sub_8098048(???);
// ??? SomethingPrepListRelated(???);
// ??? sub_80982B8(???);
// ??? sub_80982FC(???);
// ??? sub_809831C(???);
// ??? sub_8098344(???);
// ??? sub_8098378(???);
// ??? CanUnitPrepScreenUse(???);
// ??? sub_80983D4(???);
// ??? sub_8098408(???);
// ??? sub_8098448(???);
// ??? sub_8098474(???);
void sub_80984A8(int, int, int, ProcPtr);
void sub_80984CC(int, int);
// ??? sub_80984EC(???);
void sub_8098500(void);
// ??? sub_8098514(???);
// ??? sub_809852C(???);
// ??? sub_8098554(???);
// ??? sub_8098570(???);
// ??? sub_8098590(???);
// ??? sub_80985A4(???);
// ??? sub_80985B8(???);
// ??? sub_8098600(???);
// ??? sub_8098620(???);
// ??? sub_80989BC(???);
// ??? sub_8098A04(???);
// ??? sub_8098A74(???);
// ??? sub_8098B48(???);
// ??? sub_8098B68(???);
// ??? sub_8098BA8(???);
// ??? sub_8098BC8(???);
// ??? sub_8098BE8(???);
void PutImg_PrepItemUseUnk(int, int);
void PutImg_PrepPopupWindow(int, int);
// ??? sub_8098CC0(???);
// ??? sub_8098E40(???);
// ??? sub_8098FAC(???);
// ??? sub_80990D4(???);
// ??? sub_8099100(???);
// ??? sub_8099120(???);
// ??? sub_8099328(???);
// ??? sub_80994C4(???);
// ??? sub_80995D4(???);
// ??? sub_8099654(???);
// ??? sub_80996B0(???);
// ??? sub_80996E8(???);
// ??? sub_8099AA0(???);
// ??? sub_8099AF8(???);
// ??? sub_8099C60(???);
// ??? sub_8099C70(???);
// ??? StartPrepItemTradeScreen(???);
// ??? sub_8099DE8(???);
// ??? StartPrepItemSupply(???);
// ??? sub_8099E18(???);
// ??? StartPrepItemListScreen(???);
// ??? sub_8099E48(???);
// ??? sub_8099E68(???);
// ??? sub_8099E98(???);
// ??? sub_8099F50(???);
ProcPtr StartPrepItemScreen(ProcPtr);
// ??? sub_8099F7C(???);
// ??? sub_809A08C(???);
// ??? sub_809A114(???);
// ??? sub_809A21C(???);
// ??? sub_809A230(???);
// ??? sub_809A274(???);
void PrepItemDrawPopupBox(int x, int y, int w, int h, int oam2);
// ??? sub_809A504(???);
// ??? sub_809A538(???);
// ??? sub_809B538(???);
// ??? sub_809B564(???);
void DrawPrepScreenItems(u16*, struct TextHandle*, struct Unit*, int);
// ??? sub_809B830(???);
// ??? sub_809B86C(???);
// ??? sub_809BB34(???);
// ??? sub_809BE24(???);
// ??? StartPrepItemTradeScreenProc(???);
// ??? sub_809BE60(???);

/* PrepItemUse */
bool PrepItemUseTryMoveHand(struct ProcPrepItemUse *proc);
void DrawPrepScreenItemUseStatLabels(struct Unit *unit);
void DrawPrepScreenItemUseStatBars(struct Unit *unit, int mask);
void DrawPrepScreenItemUseStatValues(struct Unit *unit);
void DrawPrepScreenItemUseDesc(struct Unit *unit, int slot);
void PrepItemUseParallel_UpdateSMS();
// ??? PrepItemUse_OnInit(???);
// ??? PrepItemUse_InitDisplay(???);
// ??? PrepItemUse_CtrlLoop(???);
// ??? ProcPrepItemUse_OnEnd(???);
// ??? PrepItemUseDrawSubBox(???);
void PrepItemUseClearSubBox(void);
// ??? PrepItemUse_ConfirmWindowInit(???);
// ??? PrepItemUse_ConfirmWindowCtrlLoop(???);
// ??? PrepItemUse_HandleItemEffect(???);
// ??? PrepItemUse_ExecPromotionItemUnused(???);
// ??? PrepItemUse_ExecPromoDoneUnusedIDLE(???);
// ??? PrepItemUse_PostPromotion(???);
// ??? PrepItemUse_ResetBgmAfterPromo(???);
// ??? sub_809CCE0(???);
// ??? StartPrepItemUseScreen(???);

/* itemusemind */
void PrepItemUseBooster_OnDraw(struct ProcPrepItemUseBooster *proc, int x, int y, int msg, int item);
// ??? PrepItemUseBooster_OnInit(???);
// ??? PrepItemUseBooster_IDLE(???);
// ??? PrepItemUseBooster_OnEnd(???);

void PrepItemUseJuna_OnDraw(struct ProcPrepItemUseJunaFruit *proc, int x, int y, int msg, int level);
// ??? PrepItemUseJuna_OnInit(???);
// ??? PrepItemUseJuna_IDLE(???);
// ??? PrepItemUseJuna_OnEnd(???);
