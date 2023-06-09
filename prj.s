.text

.global shiftLights
shiftLights:
PUSH {r4, r5, r6, lr}

resetS:
MOV R5, #0x1 //aux2
MOV R6, #0x80 //aux1
MOV R4, #0x0 //output
MOV R7, #5 //i

MOV R0, R4
BL disp_binary

MOV R0, R4
BL ledShow

MOV R0, #2 //Index for array in c
BL delay

loopS:

ORR R4, R5, R6
MOV R0, R4
BL disp_binary

MOV R0, R4
BL ledShow

LSR R6, R6, #1
ORR R6, R6, #0b10000000

LSL R5, R5, #1
ORR R5, R5, #0b1

MOV R0, #2 //Index for array in c
BL delay

SUBS R7, R7, #1
BEQ resetS

CMP R0, #0
BNE loopS
BL turnOff

POP {R4, R5, R6, PC}



.global sirena
sirena:

PUSH {r4, r5, r6, lr}

reset:
LDR R4, =sirenad
MOV r6, #21

loop:
LDRB R5, [R4], #1

MOV R0, R5
BL disp_binary //display on screen

MOV R0, R5
BL ledShow

MOV R0, #3 //Index for array in c
BL delay

SUBS R6, R6, #1
BEQ reset

CMP R0, #0
BNE loop
BL turnOff

POP {R4, R5, R6, PC}


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
