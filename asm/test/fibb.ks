MOV $12 %ra

MOV $0 %rb
MOV $1 %rc

loop:
    TST %ra
    SUB $1 %ra
    JZ end

    MOV %rc %rd
    ADD %rb %rc
    MOV %rd %rb

    JMP loop

end:
    CMP $89 %rb
    JNE fail
    CMP $144 %rc
    JNE fail

    HLT

fail:
    ABRT