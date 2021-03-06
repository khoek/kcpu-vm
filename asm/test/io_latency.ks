PUSH $0xF0
PUSH $0xBEEF
CALL test_port
SUB $4 %rsp

PUSH $0xF1
PUSH $0xDEAD
CALL test_port
SUB $4 %rsp

PUSH $0xF2
PUSH $0xFEEF
CALL test_port
SUB $4 %rsp

PUSH $0xF3
PUSH $0x1337
CALL test_port
SUB $4 %rsp

PUSH $0xF4
PUSH $0xD10D
CALL test_port
SUB $4 %rsp

HLT

test_port:
    LDWO %rsp $4 %ra
    LDWO %rsp $2 %rb

    IOW %ra %rb
    IOR %ra %rc

    CMP %rb %rc
    JNE fail

    RET

fail:
    ABRT