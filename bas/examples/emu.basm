START:
    ; Tell the emulator to identify itself
    IDENT
    CALL PRINT_CHAR
    MOV A, B
    CALL PRINT_CHAR
    MOV A, C
    CALL PRINT_CHAR
    MOV A, D
    CALL PRINT_CHAR
    HLT

PRINT_CHAR:
    ; preserve A
    MOV E, A
    MVI A, 0x01
    OUT
    MOV A, E
    OUT
    RET