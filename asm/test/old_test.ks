FAR.STPFX $0x80

MOV $0x1337 %ra
STW $0x136 %ra
MOV $0xBEEF %ra
STW $0x138 %ra

MOV $0xDEAD %ra
FAR.STW $0x136 %ra
MOV $0x9876 %ra
FAR.STW $0x138 %ra

LDW $0x136 %rc
FAR.LDW $0x138 %rsp
MOV %rc %rb
MOV %rd %ra
MOV $1 %rc
MOV $2 %rd
ADD %rc %rd
MOV %rd %ra
XOR %rc %ra

MOV $55 %ra
MOV $71 %rb
SUB %rb %ra

JZ was_zero

MOV $0xFFFF %ra
ADD %ra %ra
JO was_ovflw

MOV $0xFFFF %ra
HLT

was_ovflw:
MOV $0xAAAA %ra
ABRT

MOV $0x1111 %ra
was_zero:
ABRT