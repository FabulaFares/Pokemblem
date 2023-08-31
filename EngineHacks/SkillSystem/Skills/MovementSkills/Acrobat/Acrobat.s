.thumb
.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm
	.equ CheckEventId,0x8083da8
.equ AcrobatID, SkillChecker+4
@r0=movement cost table. Function originally at 1A4CC, now jumped to here (jumpToHack)
push  {r4-r6,r14}
mov   r4,r0
ldr 	r0, =CheckEventId
mov   r14,r0
ldr   r0,CurrentCharPtr
ldr   r6,[r0]
cmp   r6, #0
bne   NoDZ
mov   r6, r2 @if the active unit is 0, we're being called from dangerzone
NoDZ:
mov r0, #0 @ default as no acrobat 

ldrb r1, [r6, #0x0B] @ deployment byte 
lsr r1, #6 @ NPC/Enemies only 
cmp r1, #0 
beq Player
mov r0, #1 @ enemies always have acrobat i guess lol 
Player:
mov   r1,#0x0       @counter
ldr   r5,MoveCostLoc

cmp r0, #1 
beq Acrobat 
b NoAcrobat 

Acrobat: 
add   r2,r4,r1
add   r3,r5,r1
ldrb  r2,[r2]
cmp   r2,#0x80
bge   Store @ if >127, acrobat does nothing 
mov   r2,#0x1
Store: 
strb  r2,[r3]
add   r1,#0x1
cmp   r1,#0x40
ble   Acrobat
b FinishUp

NoAcrobat: @ store each value into the movement table in ram  
add   r2,r4,r1
add   r3,r5,r1
ldrb  r2,[r2]
strb  r2,[r3]
add   r1,#0x1
cmp   r1,#0x40
ble   NoAcrobat

FinishUp: 

ldr 	r0, =CheckEventId
mov   r14,r0
ldr r0,MarshbadgeObtained
.short  0xF800
cmp r0, #0 
beq NoSurf 
mov r1, #0x15 @ sea
add r3, r5, r1 
ldrb r1, [r3] 
lsr r1, #7 
cmp r1, #0 
bne NoSurf @ if movement cost is >127, then don't change it 
mov r2, #1 @ costs 1 
strb r2, [r3] 

NoSurf: 
ldrb r0, [r6, #0x0B] @ deployment byte 
lsr r0, #6 @ NPC/Enemies only 
cmp r0, #0 
beq PlayerMightHaveHoverBoard 

mov r1, #0x17 @ traps for AI to avoid 
add r3, r5, r1 
mov r2, #3 @ costs 3 
strb r2, [r3] 

mov r1, #0x2f @ traps for AI to avoid 
add r3, r5, r1 
mov r2, #2 @ costs 2
strb r2, [r3] 
b Exit 

PlayerMightHaveHoverBoard:
ldr r1, =HoverBoardID 
lsl r1, #16 
lsr r1, #16 
mov r0, r6 @ unit 
bl SkillTester 
cmp r0, #0 
beq PlayerMightHaveSurfBoard 

mov r1, #0x16 @ shallow
add r3, r5, r1 
mov r2, #1 @ costs 1
strb r2, [r3] 
mov r1, #0x26 @ cliff
add r3, r5, r1 
mov r2, #1 @ costs 1
strb r2, [r3] 

ldr 	r0, =CheckEventId
mov   r14,r0
ldr r0,MarshbadgeObtained
.short  0xF800
cmp r0, #0 
beq PlayerMightHaveSurfBoard

mov r1, #0x15 @ sea
add r3, r5, r1 
mov r2, #1 @ costs 1
strb r2, [r3] 
mov r1, #0x3C @ water
add r3, r5, r1 
mov r2, #1 @ costs 1
strb r2, [r3] 

PlayerMightHaveSurfBoard: 
ldr r1, =SurfBoardID 
lsl r1, #16 
lsr r1, #16 
mov r0, r6 @ unit 
bl SkillTester 
cmp r0, #0 
beq Exit 

mov r1, #0x16 @ shallow
add r3, r5, r1 
mov r2, #1 @ costs 1
strb r2, [r3] 

ldr 	r0, =CheckEventId
mov   r14,r0
ldr r0,MarshbadgeObtained
.short  0xF800
cmp r0, #0 
beq Exit 

mov r1, #0x15 @ sea
add r3, r5, r1 
mov r2, #1 @ costs 1
strb r2, [r3] 
mov r1, #0x3C @ water
add r3, r5, r1 
mov r2, #1 @ costs 1
strb r2, [r3] 

Exit: 
pop   {r4-r6}
pop   {r0}
bx    r0

.ltorg 
.align
CurrentCharPtr:
.long 0x03004E50
MoveCostLoc:
.long 0x03004BB0
MarshbadgeObtained:
@WORD MarshbadgeObtained
@WORD AcrobatID
