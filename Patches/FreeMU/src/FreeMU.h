#pragma once
#include "gbafe.h"

enum State {yield=0, no_yield=1};

typedef struct FMUProc FMUProc;
typedef bool (*ButtonFunc) (struct FMUProc*);

struct FMUProc {
	PROC_FIELDS;
	/* 29 */	u8 uTimer;
	/* 2A */	u16 Free;
	/* 2C */	s8 xCur;
	/* 2D */	s8 xTo;
	/* 2E */	s8 yCur;
	/* 2F */	s8 yTo;
	/* 30 */	Unit* FMUnit;
	/* 34 */    s8 smsFacing; 
	/* 35 */    u8 moveSpeed; // hardcoded to this proc field in MU6Cfix
	/* 36 */    u16 curInput; 
	/* 38 */    u16 lastInput; 
	/* 3a */    u8 yield; 
	/* 3b */    u8 yield_move; 
};

struct FMUTrapDef{
	u8 TrapID;
	ButtonFunc Func;
};
extern struct FMUTrapDef HookListFMU_TrapList_OnPressA[];
extern struct FMUTrapDef HookListFMU_TrapList_Auto[];


struct LocEventDef {
	u8 LocID;
	u8 TrapID;
};

struct speedToggleStruct { 
	u8 speedA; 
	u8 speedB; 
}; 
extern struct speedToggleStruct FreeMU_MovingSpeed; 
extern struct LocEventDef HookListFMU_LocationBasedEvent[];
extern struct LocEventDef HookListFMU_LocationBasedEventDoor[];
extern ButtonFunc FMU_FunctionList_OnPressA[];
extern ButtonFunc FMU_FunctionList_OnPressB[];
extern ButtonFunc FMU_FunctionList_OnPressR[];
extern ButtonFunc FMU_FunctionList_OnPressL[];
extern ButtonFunc FMU_FunctionList_OnPressSelect[];
extern ButtonFunc FMU_FunctionList_OnPressStart[];

extern const u8 TimerDelay;
//#define FreeMoveFlag iFRAM[0]
extern u8* const FreeMoveFlag;

#define RunCharacterEvents ( (void(*)(u8,u8))(0x8083FB1) )
#define CheckForCharacterEvents ( (u8(*)(u8,u8))(0x8083F69) )
extern const ProcCode FreeMovementControlProc[];
extern const MenuDefinition FreeMovementLMenu;
extern bool RunMiscBasedEvents(u8,u8);


/*------------- External --------------*/
bool FMU_CanUnitBeOnPos(Unit*, s8, s8);
void EnableFreeMovementASMC(void);
void DisableFreeMovementASMC(void);
u8 GetFreeMovementState(void);
void End6CInternal_FreeMU(FMUProc* proc);
void ChangeControlledUnitASMC(struct FMUProc*);
void NewPlayerPhaseEvaluationFunc(struct Proc*);
void NewMakePhaseControllerFunc(struct Proc*);
void pFMU_OnInit(struct FMUProc*);
void pFMU_InitTimer(struct FMUProc*);
int pFMU_CorrectCameraPosition(struct FMUProc*);
u8 FMU_ChkKeyForMUExtra(void);


/*------------- Core --------------*/
void pFMU_MainLoop(struct FMUProc*);
int pFMU_HanleContinueMove(struct FMUProc*);
int pFMU_MoveUnit(struct FMUProc*, u16 iKeyCur);
int pFMU_HandleKeyMisc(struct FMUProc*, u16 iKeyCur);
int pFMU_HandleSave(struct FMUProc*);
void pFMU_PressA(struct FMUProc*);
void pFMU_PressB(struct FMUProc*);
void pFMU_PressL(struct FMUProc*);
void pFMU_PressR(struct FMUProc*);
void pFMU_PressSelect(struct FMUProc*);
void pFMU_PressStart(struct FMUProc*);
void pFMU_UpdateSMS(struct FMUProc* proc);


/*------------- Events --------------*/
void pFMU_RunMiscBasedEvents(struct FMUProc*);
int pFMU_RunLocBasedAsmcAuto(struct FMUProc*);
bool FMUmisc_RunMapEvents(struct FMUProc*);
bool FMUmisc_RunTalkEvents(struct FMUProc*);
bool FMU_RunTrapASMC(FMUProc*);
bool FMU_RunTrapASMC_Auto(FMUProc*);

/*------------- KeyPress --------------*/
bool FMU_OnButton_StartMenu(FMUProc*);
bool FMU_OnButton_EndFreeMove(FMUProc*);
bool FMU_OnButton_ChangeUnit(FMUProc*);

/*------------- Graphics --------------*/
extern void* FMU_idleSMSGfxTable[0xFF];

/*------------- Other -----------------*/
extern u8 gSMSGfxBuffer_Frame1[0x2000];                                   //! FE8U = 0x2034010
extern u8 gSMSGfxBuffer_Frame2[0x2000];                                   //! FE8U = 0x2036010
extern u8 gSMSGfxBuffer_Frame3[0x2000];                                   //! FE8U = 0x2038010
const u8 CheckEventId(u16 eventId);                                       //! FE8U = 0x8083DA8
const void CopyTileGfxForObj(void* src, void* dest, u8 width, u8 height); //! FE8U = 0x8013020
const void MuCtr_OnEnd(Proc* proc);                                       //! FE8U = 0x807A1FD
extern int CenterCameraOntoPosition(struct Proc* parent, int x, int y);

extern void MU_DisplayAsMMS(struct MUProc* proc); 

extern u16 GetCameraCenteredX(int x); 
extern u16 GetCameraAdjustedX(int x); 
extern u16 GetCameraCenteredY(int y); 
extern u16 GetCameraAdjustedY(int y); 
extern const ProcInstruction* gProc_CameraMovement; 

struct CamMoveProc {
    /* 00 */ PROC_HEADER;
	/* 2a */ short dummy; 
    /* 2C */ struct Vec2 to;
    /* 30 */ struct Vec2 from;
    /* 34 */ struct Vec2 watchedCoordinate;
    /* 38 */ s16 calibration;
    /* 3A */ s16 distance;
    /* 3C */ int frame;
    /* 40 */ s8 xCalibrated;
};
struct ProcCmd
{
    short opcode;
    short dataImm;
    const void* dataPtr;
};
extern struct ProcCmd gProcScr_CamMove[];


struct BmSt // Game State Struct
{
    /* 00 */ s8  mainLoopEndedFlag;

    /* 01 */ s8  gameLogicSemaphore;
    /* 02 */ s8  gameGfxSemaphore;

    /* 03 */ u8  _unk04;

    /* 04 */ u8  gameStateBits;

    /* 05 */ u8  _unk05;

    /* 06 */ u16 prevVCount;

    /* 08 */ u32 _unk08;

    /* 0C */ struct Vec2 camera;
    /* 10 */ struct Vec2 cameraPrevious;
    /* 14 */ struct Vec2 playerCursor;
    /* 18 */ struct Vec2 cursorPrevious;
    /* 1C */ struct Vec2 cursorTarget;
    /* 20 */ struct Vec2 playerCursorDisplay;
    /* 24 */ struct Vec2u mapRenderOrigin;
    /* 28 */ struct Vec2 cameraMax;

    /* 2C */ u16 itemUnk2C;
    /* 2E */ u16 itemUnk2E;

    /* 30 */ u16 unk30;
    /* 32 */ s16 unk32;
    /* 34 */ s16 unk34;
    /* 36 */ s8 unk36;
    /* 37 */ s8 unk37;
    /* 38 */ u8 altBlendACa;
    /* 39 */ u8 altBlendACb;
    /* 3A */ u8 altBlendBCa;
    /* 3B */ u8 altBlendBCb;
    /* 3C */ u8 just_resumed;
    /* 3D */ u8 unk3D;
    /* 3E */ u8 unk3E;
    /* 3F */ s8 unk3F;
};
extern struct BmSt gBmSt;


struct MenuRect { s8 x, y, w, h; };

struct MenuDef;
struct MenuItemDef;

struct MenuProc;
struct MenuItemProc;

struct MenuItemProc
{
    /* 00 */ PROC_HEADER;

    /* 2A */ short xTile;
    /* 2C */ short yTile;

    /* 30 */ const struct MenuItemDef* def;

    /* 34 */ struct TextHandle text;

    /* 3C */ s8 itemNumber;
    /* 3D */ u8 availability;
};

struct MenuItemDef
{
    /* 00 */ const char* name;

    /* 04 */ u16 nameMsgId, helpMsgId;
    /* 08 */ u8 color, overrideId;

    /* 0C */ u8(*isAvailable)(const struct MenuItemDef*, int number);

    /* 10 */ int(*onDraw)(struct MenuProc*, struct MenuItemProc*);

    /* 14 */ u8(*onSelected)(struct MenuProc*, struct MenuItemProc*);
    /* 18 */ u8(*onIdle)(struct MenuProc*, struct MenuItemProc*);

    /* 1C */ int(*onSwitchIn)(struct MenuProc*, struct MenuItemProc*);
    /* 20 */ int(*onSwitchOut)(struct MenuProc*, struct MenuItemProc*);
};

struct MenuDef
{
    /* 00 */ struct MenuRect rect;
    /* 04 */ u8 style;
    /* 08 */ const struct MenuItemDef* menuItems;

    /* 0C */ void(*onInit)(struct MenuProc*);
    /* 10 */ void(*onEnd)(struct MenuProc*);
    /* 14 */ void(*_u14)(struct MenuProc*);
    /* 18 */ u8(*onBPress)(struct MenuProc*, struct MenuItemProc*);
    /* 1C */ u8(*onRPress)(struct MenuProc*);
    /* 20 */ u8(*onHelpBox)(struct MenuProc*, struct MenuItemProc*);
};










