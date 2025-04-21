START:
    ; Move the string to the Higher M register
    MVI H, STARTOFSTRING
    ; Call print string
    CALL PRINT_STRING
    ; End program
    HLT


PRINT_STRING:
        ; Load the value from the address in the M register
        LUMA
        ; Check if the value is 0x00 (end of string)
        CPI A, 0x00
        ; If it is, jump to the end of the string
        JZ .END
        ; Otherwise check if H is 0xFF (Max for a byte)
        CPI H, 0xFF
        ; If it is, jump to TINC
        JZ TINC
        ; Otherwise Increment H
        INC H
        ; Move value from A to B
        MOV B, A
        ; Call print char
        CALL PRINT_CHAR
        ; Loop back to the start of the call
        JMP PRINT_STRING
        TINC:
            ; Increment the L register
            INC L
            ; Reset the H register to 0x00
            MVI H, 0x00
            ; Move the value from A to B
            MOV B, A
            ; Call print char
            CALL PRINT_CHAR
            ; Loop back to the start of the call
            JMP PRINT_STRING

    .END:
        ; Return from subroutine
        RET

PRINT_CHAR:
    ; Put 1 into A
    MVI A, 0x01
    ; 1 is the selector for what action (print char )
    OUT
    ; Move the value from B to A (the char to print)
    MOV A, B
    ; Tell the subsystem to print the char in A
    OUT
    ; Return from subroutine
    RET

STARTOFSTRING:
    ; String to print
    DB "We", " now have very long strings that can go over the 255 8-bit limit due to the use of the 'M' register, allowing us to use LUMA to load a 16-bit address from it and get the value.", 0x0A, 0x0