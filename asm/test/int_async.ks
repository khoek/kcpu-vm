LIHP int_fail

EI

MOV $0x8008 %rbp
IOW $0x0001 %rbp

MOV $0 %rc

loop:
    CALL try_wait_for_int
    INC %rc

    CMP $20 %rc
    JNE loop

HLT

try_wait_for_int:
    MOV $0 %ra
    ST data.had_int %ra

    LIHP int_success
    IOW $0xD1 %rc

    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

    LIHP int_fail

    LD data.had_int %ra
    TST %ra
    JZ fail

    RET

int_fail:
fail:
    ABRT

int_success:
    MOV $1 %ra
    ST data.had_int %ra

    MOV $0x4000 %rbp
    IOW $0x0001 %rbp
    IRET

data.had_int:
    NOP