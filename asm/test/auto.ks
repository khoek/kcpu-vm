# WARNING: THIS TEST IS AUTOGENERATED, DO NOT EDIT OR DELETE
# generated by tools/gen_test_auto.cpp
#
# run_everything (mostly, except jumps and io)

STPFX $0x0080
FAR.STPFX $0x0080

ADD2 %ra %rb
ADD2NF %ra %rb
ADD3 %ra %rb %rc
ADD3NF %ra %rb %rc
AND %ra %rb
ANDNF %ra %rb
BSUB %ra %rb
BSUBNF %ra %rb
CMP %ra %rb
DI
EI
ENTER0
ENTER1 %ra
ENTERFR1 %ra
ENTERFR2 %ra %rb
FAR.LDBH %ra %hb
FAR.LDBHZ %ra %hb
FAR.LDBL %ra %lb
FAR.LDBLZ %ra %lb
FAR.LDW %ra %rb
FAR.LDWO %ra %rb %rc
FAR.STBH %ra %hb
FAR.STBL %ra %lb
FAR.STW %ra %rb
FAR.STWO %ra %rb %rc
INC %ra
LDBH %ra %hb
LDBHZ %ra %hb
LDBL %ra %lb
LDBLZ %ra %lb
LDW %ra %rb
LDWO %ra %rb %rc
LEAVE0
LEAVE1 %ra
LIHP %ra
LSFT %ra
LSFTNF %ra
MOV %ra %rb
NEG %ra
NOP
NOT %ra
OR %ra %rb
ORNF %ra %rb
POP %ra
POPA
POPx2 %ra %rb
PUSH %ra
PUSHA
PUSHx2 %ra %rb
RSFT %ra
RSFTNF %ra
STBH %ra %hb
STBL %ra %lb
STW %ra %rb
STWO %ra %rb %rc
SUB %ra %rb
SUBNF %ra %rb
TST %ra
XOR %ra %rb
XORNF %ra %rb

PUSHFG
LD %rsp %ra
LFG %ra
POPFG

HLT
ABRT