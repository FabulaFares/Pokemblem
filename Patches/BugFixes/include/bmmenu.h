#ifndef BMMENU_H
#define BMMENU_H

// ??? sub_80225AC(???);
u8 MapMenu_IsSuspendCommandAvailable(const struct MenuItemDef*, int number);
u8 MapMenu_SuspendCommand(struct MenuProc*, struct MenuItemProc*);
u8 CommandEffectEndPlayerPhase(struct MenuProc*, struct MenuItemProc*);
u8 MapMenu_UnitCommand(struct MenuProc*, struct MenuItemProc*);
u8 MapMenu_OptionsCommand(struct MenuProc*, struct MenuItemProc*);
// ??? sub_802263C(???);
u8 MapMenu_StatusCommand(struct MenuProc*, struct MenuItemProc*);
u8 MapMenu_IsGuideCommandAvailable(const struct MenuItemDef*, int number);
int MapMenu_GuideCommandDraw(struct MenuProc*, struct MenuItemProc*);
u8 MapMenu_GuideCommand(struct MenuProc*, struct MenuItemProc*);
// ??? MapMenu_DangerZone_UnusedEffect(???);
// ??? sub_8022724(???);
// ??? sub_8022734(???);
u8 EffectWait(struct MenuProc*, struct MenuItemProc*);
// ??? GenericSelection_BackToUM(???);
// ??? BackToUnitMenu_CamWatch(???);
// ??? BackToUnitMenu_RestartMenu(???);
// ??? GenericSelection_BackToUM_CamWait(???);
u8 ItemMenu_ButtonBPressed(struct MenuProc*, struct MenuItemProc*);
// ??? RescueSelection_OnHelp(???);
u8 RescueUsability(const struct MenuItemDef*, int number);
u8 RescueEffect(struct MenuProc*, struct MenuItemProc*);
// ??? RescueSelection_OnSelect(???);
u8 DropUsability(const struct MenuItemDef*, int number);
u8 DropEffect(struct MenuProc*, struct MenuItemProc*);
// ??? DropSelection_OnSelect(???);
u8 TakeUsability(const struct MenuItemDef*, int number);
u8 TakeEffect(struct MenuProc*, struct MenuItemProc*);
u8 GiveUsability(const struct MenuItemDef*, int number);
u8 GiveEffect(struct MenuProc*, struct MenuItemProc*);
// ??? MakeUnitRescueTransferGraphics(???);
// ??? TakeSelection_OnSelect(???);
// ??? GiveSelection_OnSelect(???);
u8 UnitActionMenu_Attack(struct MenuProc*, struct MenuItemProc*);
// ??? sub_8022B8C(???);
// ??? sub_8022BD8(???);
int DisplayUnitStandingAttackRange(struct MenuProc*, struct MenuItemProc*);
int HideMoveRangeGraphicsWrapper(struct MenuProc*, struct MenuItemProc*);
u8 UnknownMenu_IsAvailable(const struct MenuItemDef*, int number);
u8 UnknownMenu_Selected(struct MenuProc*, struct MenuItemProc*);
int UnknownMenu_Draw(struct MenuProc*, struct MenuItemProc*);
int UnknownMenu_SwitchIn(struct MenuProc*, struct MenuItemProc*);
int BallistaRangeMenu_SwitchOut(struct MenuProc*, struct MenuItemProc*);
// ??? sub_8022DF0(???);
// ??? sub_8022E38(???);
// ??? sub_8022E54(???);
// ??? sub_8022E64(???);
// ??? sub_8022E8C(???);
// ??? sub_8022F10(???);
u8 ItemSubMenu_IsTradeAvailable(const struct MenuItemDef*, int number);
u8 TradeCommandEffect(struct MenuProc*, struct MenuItemProc*);
// ??? TradeSelection_OnSelect(???);
u8 UnitActionMenu_CanSeize(const struct MenuItemDef*, int number);
u8 UnitActionMenu_Seize(struct MenuProc*, struct MenuItemProc*);
u8 VisitCommandUsability(const struct MenuItemDef*, int number);
u8 VisitCommandEffect(struct MenuProc*, struct MenuItemProc*);
// ??? sub_80230F0(???);
u8 PlayCommandUsability(const struct MenuItemDef*, int number);
u8 DanceCommandUsability(const struct MenuItemDef*, int number);
u8 PlayCommandEffect(struct MenuProc*, struct MenuItemProc*);
// ??? sub_80232A4(???);
u8 ItemCommandUsability(const struct MenuItemDef*, int number);
u8 ItemCommandEffect(struct MenuProc*, struct MenuItemProc*);
int ItemSelectMenu_TextDraw(struct MenuProc*, struct MenuItemProc*);
u8 ItemSelectMenu_Usability(const struct MenuItemDef*, int number);
u8 ItemSelectMenu_Effect(struct MenuProc*, struct MenuItemProc*);
int Menu_SwitchIn(struct MenuProc*, struct MenuItemProc*);
int Menu_SwitchOut_DoNothing(struct MenuProc*, struct MenuItemProc*);
// ??? sub_80234AC(???);
void ItemSubMenuEnd(struct MenuProc*);
u8 MenuCommand_SelectNo(struct MenuProc*, struct MenuItemProc*);
// ??? sub_8023538(???);
// ??? sub_8023550(???);
// ??? sub_80235A8(???);
u8 ItemSubMenu_IsUseAvailable(const struct MenuItemDef*, int number);
u8 ItemSubMenu_IsEquipAvailable(const struct MenuItemDef*, int number);
u8 ItemSubMenu_IsDiscardAvailable(const struct MenuItemDef*, int number);
u8 ItemSubMenu_UseItem(struct MenuProc*, struct MenuItemProc*);
u8 ItemSubMenu_EquipItem(struct MenuProc*, struct MenuItemProc*);
u8 ItemSubMenu_TradeItem(struct MenuProc*, struct MenuItemProc*);
u8 ItemSubMenu_DiscardItem(struct MenuProc*, struct MenuItemProc*);
u8 MenuCommand_SelectYes(struct MenuProc*, struct MenuItemProc*);
u8 BallistaRangeMenu_BallistaUsability(const struct MenuItemDef*, int number);
int BallistaRangeMenu_Draw(struct MenuProc*, struct MenuItemProc*);
u8 BallistaRangeMenu_Select(struct MenuProc*, struct MenuItemProc*);
int FillBallistaRange(struct MenuProc*, struct MenuItemProc*);
u8 StaffCommandUsability(const struct MenuItemDef*, int number);
u8 StaffCommandEffect(struct MenuProc*, struct MenuItemProc*);
int StaffCommandRange(struct MenuProc*, struct MenuItemProc*);
int HideMoveRangeGraphicsWrapper2(struct MenuProc*, struct MenuItemProc*);
u8 StaffItemSelect_Usability(const struct MenuItemDef*, int number);
u8 StaffItemSelect_Effect(struct MenuProc*, struct MenuItemProc*);
int StaffItemSelect_TextDraw(struct MenuProc*, struct MenuItemProc*);
int StaffItemSelect_OnHover(struct MenuProc*, struct MenuItemProc*);
int StaffItemSelect_SwitchOut(struct MenuProc*, struct MenuItemProc*);
u8 TalkCommandUsability(const struct MenuItemDef*, int number);
u8 TalkCommandEffect(struct MenuProc*, struct MenuItemProc*);
// ??? TalkSelection_OnSelect(???);
u8 SupportCommandUsability(const struct MenuItemDef*, int number);
u8 SupportCommandEffect(struct MenuProc*, struct MenuItemProc*);
// ??? SupportSelection_OnSelect(???);
u8 DoorCommandUsability(const struct MenuItemDef*, int number);
u8 DoorCommandEffect(struct MenuProc*, struct MenuItemProc*);
u8 ChestCommandUsability(const struct MenuItemDef*, int number);
u8 ChestCommandEffect(struct MenuProc*, struct MenuItemProc*);
u8 PickCommandUsability(const struct MenuItemDef*, int number);
u8 PickCommandEffect(struct MenuProc*, struct MenuItemProc*);
// ??? PickSelection_OnSelect(???);
// ??? sub_8023EF0(???);
u8 SupplyUsability(const struct MenuItemDef*, int number);
u8 SupplyCommandEffect(struct MenuProc*, struct MenuItemProc*);
u8 ArmoryCommandUsability(const struct MenuItemDef*, int number);
u8 ArmoryCommandEffect(struct MenuProc*, struct MenuItemProc*);
u8 VendorCommandUsability(const struct MenuItemDef*, int number);
u8 VendorCommandEffect(struct MenuProc*, struct MenuItemProc*);
u8 SecretShopCommandUsability(const struct MenuItemDef*, int number);
u8 SecretShopCommandEffect(struct MenuProc*, struct MenuItemProc*);
u8 ArenaCommandUsability(const struct MenuItemDef*, int number);
u8 ArenaCommandEffect(struct MenuProc*, struct MenuItemProc*);
u8 StealCommandUsability(const struct MenuItemDef*, int number);
u8 StealCommandEffect(struct MenuProc*, struct MenuItemProc*);
// ??? StealTargetSelection_OnInit(???);
// ??? sub_802423C(???);
// ??? sub_8024260(???);
u8 StealItemMenuCommand_Usability(const struct MenuItemDef*, int number);
int StealItemMenuCommand_Draw(struct MenuProc*, struct MenuItemProc*);
u8 StealItemMenuCommand_Effect(struct MenuProc*, struct MenuItemProc*);
u8 SummonCommandUsability(const struct MenuItemDef*, int number);
u8 SummonCommandEffect(struct MenuProc*, struct MenuItemProc*);
// ??? SummonSelection_OnSelect(???);
u8 YobimaCommandUsability(const struct MenuItemDef*, int number);
u8 YobimaCommandEffect(struct MenuProc*, struct MenuItemProc*);
// ??? sub_8024564(???);
u8 ConvoyMenu_HelpBox(struct MenuProc*, struct MenuItemProc*);
u8 ItemMenu_HelpBox(struct MenuProc*, struct MenuItemProc*);
u8 BallistaRangeMenuHelpBox(struct MenuProc*, struct MenuItemProc*);
// ??? sub_802464C(???);
// ??? sub_8024658(???);
// ??? RescueSelection_OnConstruction(???);
// ??? RescueSelection_OnChange(???);
// ??? DropSelection_OnConstruction(???);
// ??? sub_80246DC(???);
// ??? GiveSelection_OnInit(???);
// ??? GiveSelection_OnChange(???);
// ??? TakeSelection_OnInit(???);
// ??? TakeSelection_OnChange(???);
// ??? TradeTargetSelection_OnInit(???);
// ??? TradeSelection_OnChange(???);
// ??? TalkSupportSelection_OnInit(???);
// ??? TalkSupportSelection_OnChange(???);
// ??? sub_80247F4(???);
// ??? sub_8024814(???);
// ??? sub_8024838(???);
// ??? sub_8024844(???);
// ??? SummonSelection_OnInit(???);
// ??? SummonSelection_OnChange(???);
// ??? sub_8024888(???);
// ??? sub_80248A4(???);
// ??? PickSelection_OnInit(???);
u8 RideCommandUsability(const struct MenuItemDef*, int number);
u8 RideCommandEffect(struct MenuProc*, struct MenuItemProc*);
u8 ExitCommandUsability(const struct MenuItemDef*, int number);
u8 ExitCommandEffect(struct MenuProc*, struct MenuItemProc*);
u8 AttackCommandUsability(const struct MenuItemDef*, int number);
u8 AttackBallistaCommandUsability(const struct MenuItemDef*, int number);
u8 ItemMenu_Is1stCommandAvailable(const struct MenuItemDef*, int number);
int ItemMenu_Draw1stCommand(struct MenuProc*, struct MenuItemProc*);
u8 ItemMenu_Select1stCommand(struct MenuProc*, struct MenuItemProc*);
u8 ItemMenu_AreOtherCommandsAvailable(const struct MenuItemDef*, int number);
int ItemMenu_DrawOtherCommands(struct MenuProc*, struct MenuItemProc*);
u8 ItemMenu_SelectOtherCommands(struct MenuProc*, struct MenuItemProc*);
int ItemMenu_SwitchIn(struct MenuProc*, struct MenuItemProc*);
int ItemMenu_SwitchOut_DoNothing(struct MenuProc*, struct MenuItemProc*);
u8 ItemMenuHelpBox(struct MenuProc*, struct MenuItemProc*);
u8 MapMenu_IsRecordsCommandAvailable(const struct MenuItemDef*, int number);
u8 MapMenu_RecordsCommand(struct MenuProc*, struct MenuItemProc*);
u8 MapMenu_IsRetreatCommandAvailable(const struct MenuItemDef*, int number);
u8 MapMenu_RetreatCommand(struct MenuProc*, struct MenuItemProc*);


#endif //BMMENU_H
