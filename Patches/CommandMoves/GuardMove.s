.thumb
.align 4

.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm


.equ CurrentUnit, 0x3004E50
.equ MemorySlot,0x30004B8
.equ EventEngine, 0x800D07C
.equ CurrentUnitFateData, 0x203A958 

	
.global GuardCommandUsability 
.type GuardCommandUsability, %function 

GuardCommandUsability:
push {lr} 

ldr r0, =DisableMenuOptionsRamLink
ldr r0, [r0] 
ldrb r0, [r0] 
mov r1, #4 @ Guard bitflag 
and r0, r1
cmp r0, #0 
bne RetFalse 

ldr r0, =CurrentUnit 
ldr r0, [r0] 
ldr r1, =GuardMove
lsl r1, #24 
lsr r1, #24 
bl MoveTester 
cmp r0, #0
beq RetFalse  
bl IsPeaceful
cmp r0, #1 
beq RetFalse 
mov r0, #1 
b Exit 
RetFalse: 
mov r0, #3 @ Menu false usability is 3 
Exit: 

pop {r1} 
bx r1 


.global GuardCommandEffect 
.type GuardCommandEffect, %function 

GuardCommandEffect:
push {lr} 

ldr r3, =CurrentUnit 
ldr r0, [r3] 
bl GetUnitDebuffEntry
ldr r1, =GuardMoveBuffs
@r0 @ debuff entry 
@r1 debuff table to use 
@r2 entry ID of the given table 
mov r2, #0 
mov r3, r0 
bl DebuffGivenTableEntry 

bl StartBuffFxUser

ldr r3, =CurrentUnit 
ldr r3, [r3] 
ldrb r0, [r3, #0x13] @ Current HP 
ldrb r1, [r3, #0x12] @ MaxHP 
add r0, #4 
cmp r0, r1 
ble NoCap
mov r0, r1 
NoCap: 
strb r0, [r3, #0x13] @ Restore 4 hp 

ldr r1, =CurrentUnitFateData	@these four lines copied from wait routine
mov r0, #0x1
strb r0, [r1,#0x11]
mov r0, #0x17	@makes the unit wait?? makes the menu disappear after command is selected??

pop {r1} 
bx r1


.ltorg 
.align 




