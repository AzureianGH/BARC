SETUP:
    MVI A, 0xA0
    MVI L, 0xAF
    MVI H, 0xAF
    ; Test saving
    SUMA
    ; Test loading
    MVI A, 0x00
    LUMA
    HLT