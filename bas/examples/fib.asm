Start:
    MVI A, 0x00
    SAA fib0
    MVI A, 0x01
    SAA fib1
    JMP next_fib
    HLT

next_fib:
    LAA fib0
    MOV B, A
    LAA fib1
    ADD A, B
    SAA result
    LAA fib1
    SAA fib0
    LAA result
    SAA fib1
    JMP next_fib

fib0:
    DB 0x00
fib1:
    DB 0x01
result:
    DB 0x00

