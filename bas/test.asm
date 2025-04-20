START:
    MVI H, STARTOFSTRING
    CALL PRINT_STRING
    HLT


PRINT_STRING:
        LUMA
        CPI A, 0x00
        JZ .END
        CPI H, 0xFF
        JZ TINC
        INC H
        MOV B, A
        CALL PRINT_CHAR
        JMP PRINT_STRING
        TINC:
            INC L
            MVI H, 0x00
            MOV B, A
            CALL PRINT_CHAR
            JMP PRINT_STRING
        
    .END:
        RET

PRINT_CHAR:
    MVI A, 0x01
    OUT
    MOV A, B
    OUT
    RET

STARTOFSTRING:
    DB "We now have very long strings that can go over the 255 8-bit limit due to the use of the 'M' register, allowing us to use LUMA to load a 16-bit address from it and get the value.", 0x0A, 0x0