.text

.global sirena
sirena:

PUSH {r4, r5, lr}
LDR R4, =sirenad

loop:

LDRB R5, [R4], #1

MOV R0, R5
BL disp_binary //display on screen

MOV R0, R5
BL ledShow

MOV R0, #3 //Index for array in c
BL delay

CMP R0, #0
BNE loop

POP {R4, R5, PC}


.data
sirenad:
.byte 0x0
.byte 0xF
.byte 0xF
.byte 0xF0
.byte 0xF0
.byte 0x0
.byte 0x1
.byte 0x2
.byte 0x4
.byte 0x8
.byte 0x10
.byte 0x20
.byte 0x40
.byte 0x80
.byte 0x40
.byte 0x20
.byte 0x10
.byte 0x8
.byte 0x4
.byte 0x2
.byte 0x1
