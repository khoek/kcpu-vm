PUSH $0xDEAD
PUSH $0xBEEF
PUSH $0x1337

LIHP int

MOV $0x8006 %rbp
IOW $0x0001 %rbp

MOV $0xC004 %ra
IOW $0x0001 %ra

EI

NOP
NOP
NOP
NOP

POP %ra
CMP $0x1337 %ra
JNE fail

POP %ra
CMP $0xBEEF %ra
JNE fail

POP %ra
CMP $0xDEAD %ra
JNE fail

HLT

int:
    PUSH $0xF10F
    POP %ra
    IRET

fail:
    ABRT
