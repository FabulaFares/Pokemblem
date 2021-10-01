
.thumb
.align 4

.equ MemorySlot,0x30004B8


.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm


	.equ NewFlagsRam, 0x203F548
	.equ GetUnit, 0x8019430
	.equ EventEngine, 0x800D07C
	.equ CurrentUnit, 0x3004E50

@.global TrainerDeathFlags
@.type TrainerDeathFlags, %function
@TrainerDeathFlags:
push {lr}

ldr r1, [r2] @ Char pointer 
ldrb r1, [r1, #4] @ Unit ID 
cmp r1, #0xD0 
blt End 
sub r1, #0xD0 


ldr r3, =0x202BCF0 @ Chapter Data 
ldrb r0, [r3, #0x0E] @ +0x0E	Byte	Chapter ID
lsl r0, #4 @ 16 trainers per area allowed 

add r0, r1 @ which trainer exactly 


ldrb r3, =TrainerDefeatedFlagOffset @0xA0 
lsl r1, r3, #3 @ 8 flags per byte so +0x500 
add r0, r1 @ Full offset 
@ some ram address + 0x500 + ChapterID*8 + unit id over 0xD0 
blh SetNewFlag 

End:

pop {r0}
bx r0 

.global ShouldTrainerSummonTeam
.type ShouldTrainerSummonTeam, %function 
ShouldTrainerSummonTeam: 
push {r4-r7, lr}
@ save their # of pokemon to wexp +0x2D ? 
@ save each one that dies to trainer/commander's wexp + 0x2E? 
@ 8 bits - 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80 

blh ModularSummonUsability 
cmp r0, #0 
beq ReturnFalse 
mov r5, r2 @ Unit group to summon 
ldr r0, [r2] 
cmp r0, #0 
beq ReturnFalse @ Unit group is empty 
ldr r4, =CurrentUnit
ldr r4, [r4] @ Active unit trying to summon 

@ they can summon at least 1 unit 
ldr r2, =MemorySlot 
ldr r3, [r2, #4*1] @ Mem Slot 1 has total summonable 
lsr r0, r3, #8 @ # we can summon 
lsl r1, r3, #24 
lsr r1, #24 @ # pokemon they have
cmp r0, r1 
blt ReturnFalse @ 1 or more of the units have already been summoned 
mov r6, r1 @ Total party size 





mov r1, #0x2D 
ldrb r0, [r4, r1] 
cmp r0, #0 
bne ReturnFalse 


strb r6, [r4,r1] @ Wexp1 as # of team members 
mov r0, #0 
mov r1, #0x2E 
strb r0, [r4, r1] @ Wexp2 as which ones that have fainted (none so far) 

ldr r3, =0x202BCF0 @ gChapterData
mov r2, #0x2F @ Dark WEXP as additional level bonus 
mov r1, #0x14 
ldrb r0, [r3, r1] 
mov r1, #0x40 @+0x40	Set for hard mode
and r1, r0 
cmp r1, #0 
beq NotHard
@ Hard mode 
mov r0, #0x8 
strb r0, [r4, r2] 
b ReturnTrue 

NotHard:
mov r1, #0x42
ldrb r0, [r3, r1] 
mov r1, #0x20 @ 0x20	Set if not easy mode
and r1, r0 
cmp r1, #0 
beq NotEasy @ Easy mode we do not 
mov r0, #0 
strb r0, [r4, r2] @ Easy mode gets no extra level bonus 
b ReturnTrue 

NotEasy: 
@ Must be normal 
mov r0, #4 
strb r0, [r4, r2] @ 4 levels bonus 



ReturnTrue:
mov r0, #1 
b Exit 

ReturnFalse:
mov r0, #0 

Exit:

pop {r4-r7}
pop {r1}
bx r1 

.global IsTrainersTeamDefeated
.type IsTrainersTeamDefeated, %function 
IsTrainersTeamDefeated: 
push {r4-r7, lr}
@ checks if the whole team was defeated whenever a unit dies 
ldr r4, =0x203A4EC  @ Atkr 
ldr r5, =0x203A56C @ Dfdr



CheckAtkrFirst:
ldrb r0, [r4, #0x13] @ CurrentHP 
cmp r0, #0 
bne CheckDfdrSecond
ldrb r0, [r4, #0x0B] @ Deployment id 
lsr r1, r0, #6 @ allegiance 
cmp r1, #0 
beq CheckDfdrSecond

blh GetUnit 
mov r4, r0 
cmp r0, #0 
beq CheckDfdrSecond 
mov r1, #0x38 @ Commander 
ldrb r0, [r4, r1] @ Commander 
cmp r0, #0 
beq CheckDfdrSecond 
blh GetUnitByEventParameter
cmp r0, #0 
beq CheckDfdrSecond 
mov r6, r0 @ Commander 



mov r1, #0x2D 
ldrb r0, [r6,r1] @ Wexp1 as # of team members 
cmp r0, #50 
beq CheckDfdrSecond 

mov r1, #0x38 @ Commander 
mov r2, #0 
strb r2, [r5, r1] @ Make dfdr have no commander so this doesn't trigger again 

mov r2, #0x2E 
ldrb r1, [r6, r2] @ Wexp2 as how many that have fainted 
add r1, #1 @ 1 more has died 
strb r1, [r6, r2] 
cmp r0, r1 
bne CheckDfdrSecond 



mov r0, r6 @ Defeated trainer 
bl DefeatedTrainerRoutine



b True_IsTrainersTeamDefeated


CheckDfdrSecond:

ldrb r0, [r5, #0x13] @ CurrentHP 
cmp r0, #0 
bne False_IsTrainersTeamDefeated


ldrb r0, [r5, #0x0B] @ Deployment id 
lsr r1, r0, #6 @ allegiance 
cmp r1, #0 
beq False_IsTrainersTeamDefeated

blh GetUnit 

cmp r0, #0 
beq False_IsTrainersTeamDefeated
mov r5, r0 
mov r1, #0x38 @ Commander 
ldrb r0, [r5, r1] @ Commander 

cmp r0, #0 
beq False_IsTrainersTeamDefeated
blh GetUnitByEventParameter
cmp r0, #0 
beq False_IsTrainersTeamDefeated
mov r6, r0 @ Commander 


mov r1, #0x2D 
ldrb r0, [r6,r1] @ Wexp1 as # of team members 
cmp r0, #50 
beq False_IsTrainersTeamDefeated @ just now, anyway (they were previously defeated) 

mov r1, #0x38 @ Commander 
mov r2, #0 
strb r2, [r5, r1] @ Make dfdr have no commander so this doesn't trigger again 


mov r2, #0x2E 
ldrb r1, [r6, r2] @ Wexp2 as which ones that have fainted (none so far) 
add r1, #1 @ 1 more has died 
strb r1, [r6, r2] 
cmp r0, r1 
bne False_IsTrainersTeamDefeated  




mov r0, r6 @ Defeated trainer 
bl DefeatedTrainerRoutine
b True_IsTrainersTeamDefeated

True_IsTrainersTeamDefeated: 
mov r0, #1 
b Exit_IsTrainersTeamDefeated 

False_IsTrainersTeamDefeated:
mov r0, #0 

Exit_IsTrainersTeamDefeated:


pop {r4-r7}
pop {r1}
bx r1 

.global AreAnyTrainerBattlesActive
.type AreAnyTrainerBattlesActive, %function 
AreAnyTrainerBattlesActive:

push {r4-r7, lr}



mov r4, #0xDF 
mov r5, #0x2D @ number of summoned units 

AreAnyTrainerBattlesActive_Loop:
add r4, #1 
cmp r4, #0xF0 
bge BreakLoop
mov r0, r4 
blh GetUnitByEventParameter 
cmp r0, #0 
beq AreAnyTrainerBattlesActive_Loop
ldrb r1, [r0, r5]
cmp r1, #0 
beq AreAnyTrainerBattlesActive_Loop 
cmp r1, #50 
beq AreAnyTrainerBattlesActive_Loop

@ if we got here, at least one battle is active, so ret true 
mov r0, #1 
b AreAnyTrainerBattlesActive_Exit

BreakLoop:



mov r0, #0 @ False 

AreAnyTrainerBattlesActive_Exit:

pop {r4-r7}
pop {r1}
bx r1 







.global DefeatedTrainerRoutine
.type DefeatedTrainerRoutine, %function 

DefeatedTrainerRoutine:
push {r4-r7, lr}
mov r6, r0 @ Defeated trainer 

mov r1, #0x2D 
ldrb r0, [r6, r1] 
cmp r0, #50
beq ExitDefeatedTrainer 

ldr r3, =0x30017C4
str r6, [r3] @ my ram 2


ldr r0, =TrainerDefeatedEvent 
mov r1, #1 
blh EventEngine 

ExitDefeatedTrainer:



pop {r4-r7}
pop {r1}
bx r1 


.global ASMC_CheckTrainerFlag
.type ASMC_CheckTrainerFlag, %function 
ASMC_CheckTrainerFlag: 
push {lr} 
ldr r3, =MemorySlot 
ldr r0, [r3, #4] @ Slot 1 as unit ID to check 
bl CheckTrainerFlagByID @ result in r0 
Exit_ASMC_CheckTrainerFlag:
ldr r3, =MemorySlot 
mov r1, #0x0C*4 
str r0, [r3, r1] @ Store result to sC 
pop {r1} 
bx r1 



.global CallCheckTrainerFlag 
.type CallCheckTrainerFlag, %function 
CallCheckTrainerFlag: 
push {lr} 
ldr r0, =CurrentUnit
ldr r0, [r0] 
bl CheckTrainerFlag 
ldr r3, =MemorySlot 
mov r1, #0x0C*4 
str r0, [r3, r1] @ Store result to sC 

pop {r1} 
bx r1 

.global CheckTrainerFlagByID
.type CheckTrainerFlagByID, %function 
CheckTrainerFlagByID:
push {r4-r5, lr}
mov r5, #0 
mov r1, r0 

b StartCheckTrainerFlag 

@ Trainers use IDs 0xE0 - 0xEF 
.global CheckTrainerFlag
.type CheckTrainerFlag, %function 
CheckTrainerFlag:
push {r4-r5, lr}

@ given unit struct r0, check if their flag is set or not 
mov r4, r0 
mov r5, #0 

ldr r1, [r4] 
ldrb r1, [r1, #4] @ Unit ID we're interested in 
StartCheckTrainerFlag:

cmp r1, #0xE0 
blt TrainerFlagTrue 
cmp r1, #0xF0 
bge TrainerFlagTrue 

ldr r3, =0x202BCF0 @ Chapter Data 
ldrb r0, [r3, #0x0E] @ +0x0E	Byte	Chapter ID
lsl r0, #4 @ 16 trainers per area allowed 
add r0, r1 @ which trainer exactly 
ldrb r3, =TrainerDefeatedFlagOffset @0xA0 
lsl r3, #24 
lsr r3, #24 
lsl r1, r3, #3 @ 8 flags per byte so +0x500 
add r0, r1 @ Full offset 
mov r5, r0 
blh CheckNewFlag 
b ExitCheckTrainerFlag 


TrainerFlagTrue:
mov r0, #1 
b ExitCheckTrainerFlag 

TrainerFlagFalse:
mov r0, #0 

ExitCheckTrainerFlag: 
mov r1, r5 @ Offset of flag 
pop {r4-r5} 
pop {r2}
bx r2 


.global GetTargetAndStoreToRam
.type GetTargetAndStoreToRam, %function 
GetTargetAndStoreToRam:
push {lr} 

ldr r3, =0x203A958
ldrb r0, [r3, #0x0D] 

blh GetUnit @ by deployment byte 
ldr r3, =0x30017C4 
cmp r0, #0 
beq Error 
str r0, [r3] 
b Exit2




Error: 
str r0, [r3] @ put in 0 

Exit2: 


pop {r1}
bx r1 




.global MarkTrainerAsDefeated_ASMC
.type MarkTrainerAsDefeated_ASMC, %function 
MarkTrainerAsDefeated_ASMC: 
push {r4, lr} 

ldr r3, =MemorySlot 
ldr r0, [r3, #4] @ s1 as unit ID 
blh GetUnitByEventParameter
cmp r0, #0 
beq ExitMarkTrainerAsDefeated

ldr r3, =0x30017C4 @ my ram 
str r0, [r3] 
bl PostTrainerBattleActions 



ExitMarkTrainerAsDefeated: 

pop {r4} 
pop {r0} 
bx r0 


.global PostTrainerBattleActions
.type PostTrainerBattleActions, %function 

PostTrainerBattleActions:
push {r4, lr} 


ldr r3, =0x30017C4 @ my ram 
ldr r4, [r3] @


ldr r1, [r4] 
ldrb r1, [r1, #4] @ Leader's unit ID 

sub r1, #0xE0 @ we only have trainers from unit IDs 0xE0 - 0xEF 
lsl r1, #2 @ 4 bytes per entry 


ldr r3, =0x202BCF0 @ gChapterData 
ldrb r0, [r3, #0xE] @ what chapter is it 
ldr r3, =TrainerDefeatPoinTable
lsl r0, #2 @ 4 bytes per poin 
add r3, r0 
ldr r3, [r3] @ Specific chapter's table of quotes 
ldrh r0, [r3, r1] @ TextID we want 
add r1, #2 @ Gold amount 
ldrh r1, [r3, r1] @ Gold amount we want 

ldr r3, =MemorySlot 

strh r1, [r3, #4*0x03] @ Gold to give in s3 


strh r0, [r3, #4*0x02] @ Store to mem slot 2 


ldrb r0, [r4, #0x10] @ X 
ldrb r1, [r4, #0x11] @ Y 

lsl r1, #16 
add r1, r0 
str r1, [r3, #4*0x0B] @ Coords 

mov r0, r4 
bl CheckTrainerFlag 
ldr r3, =MemorySlot 
mov r2, #0x0C*4 
str r0, [r3, r2] @ store result to sC 
mov r0, r1 @ returned address offset to set 
blh SetNewFlag 

mov r0, #50 
mov r1, #0x2D 
strb r0, [r4, r1] @ to not trigger the battle again 

bl AreAnyTrainerBattlesActive 
cmp r0, #1
beq DontTurnOffFlag

ldr r0, =TrainerBattleActiveFlag 
lsl r0, #24 
lsr r0, #24 
blh 0x8083cd8 @UnsetGlobalEventId

ldr r0, =CallCountdownFlag_2
lsl r0, #24 
lsr r0, #24 
blh 0x8083cd8 @UnsetGlobalEventId

DontTurnOffFlag: 


pop {r4}
pop {r0}
bx r0 



	.equ GetUnitByEventParameter, 0x0800BC51
	
.global RemoveFoughtTrainers
.type RemoveFoughtTrainers, %function

RemoveFoughtTrainers:
@ Check if currently examindd unit's commander is the trainer 
@ Check if currently examined unit is the trainer 
@ If either is true, delete the unit 
push {r4-r7, lr}

ldr r0, =MemorySlot 
mov r4, #0x80 
mov r7, #0
LoopThroughUnits:
mov r0,r4

blh GetUnit @ 19430
cmp r0,#0
beq NextUnit
ldr r3,[r0] @ Char table pointer 
cmp r3,#0
beq NextUnit


ldrb r1, [r3, #4] @ Unit ID 
@ Their unit ID ranges from 0xD0 to 0xDF, so they are a trainer 
cmp r1, #0xD0 
blt CheckLeaderNow
cmp r1, #0xDF 
ble ValidUnit

CheckLeaderNow:
mov r2, #0x38 @ Leader unit ID 
ldrb r1, [r0, r2]

@ r1 is 
@ Their leader's ID ranges from 0xD0 to 0xDF, so they are a trainer 
cmp r1, #0xD0 
blt NextUnit 
cmp r1, #0xDF 
bgt NextUnit 

ValidUnit:
add r7, #1 
mov r5, r0 
mov r6, r1 @ Unit ID we're interested in 

sub r1, #0xD0 @ Unit ID offset 

ldr r3, =0x202BCF0 @ Chapter Data 
ldrb r0, [r3, #0x0E] @ +0x0E	Byte	Chapter ID
lsl r0, #4 @ 16 trainers per area allowed 

add r0, r1 @ which trainer exactly 


ldrb r3, =TrainerDefeatedFlagOffset @0xA0 
lsl r1, r3, #3 @ 8 flags per byte so +0x500 
add r0, r1 @ Full offset 

blh CheckNewFlag
cmp r0, #1 
@if completion flag is true, then we do not spawn this trap :-) 
bne NextUnit 


mov r0, r5 
blh 0x80177f4 @ClearUnit
sub r7, #1 




NextUnit:
add r4,#1
cmp r4,#0xAF
ble LoopThroughUnits
End_LoopThroughUnits:
ldr r3, =MemorySlot
str r7, [r3, #4*0x0C] @ # of trainers left 


pop {r4-r7}
pop {r1}
bx r1 


