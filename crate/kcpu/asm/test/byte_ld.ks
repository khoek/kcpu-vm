
MOV $0x1337 %ra
STW $0 %ra

MOV $0xBEEF %ra
STW $2 %ra

# at addr 0

MOV $0xAAAA %ra
LDBLZ $0 %la
CMP $0x0037 %ra
JNE fail

MOV $0xAAAA %ra
LDBHZ $0 %ha
CMP $0x3700 %ra
JNE fail

MOV $0xAAAA %ra
LDBL $0 %la
CMP $0xAA37 %ra
JNE fail

MOV $0xAAAA %ra
LDBH $0 %ha
CMP $0x37AA %ra
JNE fail

# at addr 1

MOV $0xAAAA %ra
LDBLZ $1 %la
CMP $0x0013 %ra
JNE fail

MOV $0xAAAA %ra
LDBHZ $1 %ha
CMP $0x1300 %ra
JNE fail

MOV $0xAAAA %ra
LDBL $1 %la
CMP $0xAA13 %ra
JNE fail

MOV $0xAAAA %ra
LDBH $1 %ha
CMP $0x13AA %ra
JNE fail


HLT


fail:
    ABRT