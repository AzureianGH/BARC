# BARC

## Address Space
BARC uses a 16-bit address space, ranging from 0x0000 to 0xFFFF, allowing for a total of 65,536 addresses. The address space is divided into program memory (0x0000 to 0xCFFF) and data memory (0xD000 to 0xFFFF). While these divisions are not mandatory, adhering to them is recommended for consistency and best practices.

## Instruction Set Architecture (ISA)
BARC is an 8-bit architecture, meaning each instruction is 8 bits long. Instructions are categorized into R-type, I-type, J-type, and Extension instructions.

### Stack
There is no conventional stack in BARC. Instead, there is a 128-bit call stack, which is used for storing return addresses during subroutine calls. The stack pointer (SP) is an 8-bit register that points to the top of the stack. The stack grows upwards, meaning that when a value is pushed onto the stack, the SP increases.

### Registers
BARC has 7 primary registers for data and address storage:
- **A**: Accumulator register (8 bits)
- **B**: Base register (8 bits)
- **C**: Counter register (8 bits)
- **D**: Data register (8 bits)
- **E**: General-purpose register (8 bits)
- **L**: Lower half of M register (8 bits)
- **H**: Upper half of M register (8 bits)

Additionally:
- **M**: M is NOT a register, but is the idea of L and H combined. M is used for addressing memory locations. The address is formed by combining the values in L and H, where L represents the lower byte and H represents the higher byte of the address.

### Instruction Format
Each instruction is represented by an 8-bit opcode. View [here](#full-table-of-instructions) for a complete list of opcodes and their corresponding instructions.

### Instruction Details

#### R-type Instructions
R-type instructions operate on registers. For example:
- `MOV A, B` (`0x01`): Moves the value in register B to register A.
- `ADD A, B` (`0x02`): Adds the value in register B to register A.

#### I-type Instructions
I-type instructions use immediate values. For example:
- `MOV A, Imm` (`0x08`): Moves an immediate value to register A.
- `ADD A, Imm` (`0x09`): Adds an immediate value to register A.

#### J-type Instructions
J-type instructions handle program flow. For example:
- `JUMP Addr` (`0x0B`): Updates the program counter to the specified address.
- `CALL Addr` (`0x0C`): Calls a subroutine at the specified address.

#### Extension Instructions
The `EXTEND` instruction (`0xFF`) allows for additional instructions. The next byte specifies the extended instruction.

### Example Programs
1. **Move Immediate to Register A**:
    ```
    MOV A, 0xFF
    Opcode: 0x08
    Immediate: 0xFF
    ```

2. **Add Two Registers**:
    ```
    ADD A, B
    Opcode: 0x02
    ```

3. **Jump to Address**:
    ```
    JUMP 0x1234
    Opcode: 0x0B
    Address: 0x1234
    ```

### Full Table of Instructions

D = Destination Register

S = Source Register

I = Immediate Value

A = Address

X = Unused

| Number | Opcode   | Operand(s) | Instruction       | Description                                   | Name | Total Bitwidth | Operand Bitwidth |
|--------|----------|------------|-------------------|-----------------------------------------------|------|----------------|------------------|
| 00 | `0000-0000` | NONE  | `HLT`             | Halt CPU operation                                 | Halt | 8-bit | NONE |
| 01 | `0000-0001` | NONE  | `MOV A, B`        | Move value from A to B                      | Move | 8-bit | 8-bit | NONE |
| 02 | `0000-0010` | NONE  | `MOV A, C`        | Move value from A to C                      | Move | 8-bit | 8-bit | NONE |
| 03 | `0000-0011` | NONE  | `MOV A, D`        | Move value from A to D                      | Move | 8-bit | 8-bit | NONE |
| 04 | `0000-0100` | NONE  | `MOV A, E`        | Move value from A to E                      | Move | 8-bit | 8-bit | NONE |
| 05 | `0000-0101` | NONE  | `MOV A, L`        | Move value from A to L                      | Move | 8-bit | 8-bit | NONE |
| 06 | `0000-0110` | NONE  | `MOV A, H`        | Move value from A to H                      | Move | 8-bit | 8-bit | NONE |
| 07 | `0000-0111` | NONE  | `MOV B, A`        | Move value from B to A                      | Move | 8-bit | 8-bit | NONE |
| 08 | `0000-1000` | NONE  | `MOV B, C`        | Move value from B to C                      | Move | 8-bit | 8-bit | NONE |
| 09 | `0000-1001` | NONE  | `MOV B, D`        | Move value from B to D                      | Move | 8-bit | 8-bit | NONE |
| 0A | `0000-1010` | NONE  | `MOV B, E`        | Move value from B to E                      | Move | 8-bit | 8-bit | NONE |
| 0B | `0000-1011` | NONE  | `MOV B, L`        | Move value from B to L                      | Move | 8-bit | 8-bit | NONE |
| 0C | `0000-1100` | NONE  | `MOV B, H`        | Move value from B to H                      | Move | 8-bit | 8-bit | NONE |
| 0D | `0000-1101` | NONE  | `MOV C, A`        | Move value from C to A                      | Move | 8-bit | 8-bit | NONE |
| 0E | `0000-1110` | NONE  | `MOV C, B`        | Move value from C to B                      | Move | 8-bit | 8-bit | NONE |
| 0F | `0000-1111` | NONE  | `MOV C, D`        | Move value from C to D                      | Move | 8-bit | 8-bit | NONE |
| 10 | `0001-0000` | NONE  | `MOV C, E`        | Move value from C to E                      | Move | 8-bit | 8-bit | NONE |
| 11 | `0001-0001` | NONE  | `MOV C, L`        | Move value from C to L                      | Move | 8-bit | 8-bit | NONE |
| 12 | `0001-0010` | NONE  | `MOV C, H`        | Move value from C to H                      | Move | 8-bit | 8-bit | NONE |
| 13 | `0001-0011` | NONE  | `MOV D, A`        | Move value from D to A                      | Move | 8-bit | 8-bit | NONE |
| 14 | `0001-0100` | NONE  | `MOV D, B`        | Move value from D to B                      | Move | 8-bit | 8-bit | NONE |
| 15 | `0001-0101` | NONE  | `MOV D, C`        | Move value from D to C                      | Move | 8-bit | 8-bit | NONE |
| 16 | `0001-0110` | NONE  | `MOV D, E`        | Move value from D to E                      | Move | 8-bit | 8-bit | NONE |
| 17 | `0001-0111` | NONE  | `MOV D, L`        | Move value from D to L                      | Move | 8-bit | 8-bit | NONE |
| 18 | `0001-1000` | NONE  | `MOV D, H`        | Move value from D to H                      | Move | 8-bit | 8-bit | NONE |
| 19 | `0001-1001` | NONE  | `MOV E, A`        | Move value from E to A                      | Move | 8-bit | 8-bit | NONE |
| 1A | `0001-1010` | NONE  | `MOV E, B`        | Move value from E to B                      | Move | 8-bit | 8-bit | NONE |
| 1B | `0001-1011` | NONE  | `MOV E, C`        | Move value from E to C                      | Move | 8-bit | 8-bit | NONE |
| 1C | `0001-1100` | NONE  | `MOV E, D`        | Move value from E to D                      | Move | 8-bit | 8-bit | NONE |
| 1D | `0001-1101` | NONE  | `MOV E, L`        | Move value from E to L                      | Move | 8-bit | 8-bit | NONE |
| 1E | `0001-1110` | NONE  | `MOV E, H`        | Move value from E to H                      | Move | 8-bit | 8-bit | NONE |
| 1F | `0001-1111` | NONE  | `MOV L, A`        | Move value from L to A                      | Move | 8-bit | 8-bit | NONE |
| 20 | `0010-0000` | NONE  | `MOV L, B`        | Move value from L to B                      | Move | 8-bit | 8-bit | NONE |
| 21 | `0010-0001` | NONE  | `MOV L, C`        | Move value from L to C                      | Move | 8-bit | 8-bit | NONE |
| 22 | `0010-0010` | NONE  | `MOV L, D`        | Move value from L to D                      | Move | 8-bit | 8-bit | NONE |
| 23 | `0010-0011` | NONE  | `MOV L, E`        | Move value from L to E                      | Move | 8-bit | 8-bit | NONE |
| 24 | `0010-0100` | NONE  | `MOV L, H`        | Move value from L to H                      | Move | 8-bit | 8-bit | NONE |
| 25 | `0010-0101` | NONE  | `MOV H, A`        | Move value from H to A                      | Move | 8-bit | 8-bit | NONE |
| 26 | `0010-0110` | NONE  | `MOV H, B`        | Move value from H to B                      | Move | 8-bit | 8-bit | NONE |
| 27 | `0010-0111` | NONE  | `MOV H, C`        | Move value from H to C                      | Move | 8-bit | 8-bit | NONE |
| 28 | `0010-1000` | NONE  | `MOV H, D`        | Move value from H to D                      | Move | 8-bit | 8-bit | NONE |
| 29 | `0010-1001` | NONE  | `MOV H, E`        | Move value from H to E                      | Move | 8-bit | 8-bit | NONE |
| 2A | `0010-1010` | NONE  | `MOV H, L`        | Move value from H to L                      | Move | 8-bit | 8-bit | NONE |
| 2B | `0010-1011` | IIII-IIII-IIII-IIII  | `LAA`        | Load value from an address into A           | Load Address A | 24-bit | 16-bit |
| 2C | `0010-1100` | IIII-IIII-IIII-IIII  | `SAA`        | Store value from A into an address         | Store Address A | 24-bit | 16-bit |
| 2D | `0010-1101` | IIII-IIII  | `MVI A, Imm`        | Move immediate value to A         | Move Immediate A | 16-bit | NONE |
| 2E | `0010-1110` | IIII-IIII  | `MVI B, Imm`        | Move immediate value to B         | Move Immediate B | 16-bit | NONE |
| 2F | `0010-1111` | IIII-IIII  | `MVI C, Imm`        | Move immediate value to C         | Move Immediate C | 16-bit | NONE |
| 30 | `0011-0000` | IIII-IIII  | `MVI D, Imm`        | Move immediate value to D         | Move Immediate D | 16-bit | NONE |
| 31 | `0011-0001` | IIII-IIII  | `MVI E, Imm`        | Move immediate value to E         | Move Immediate E | 16-bit | NONE |
| 32 | `0011-0010` | IIII-IIII  | `MVI L, Imm`        | Move immediate value to L         | Move Immediate L | 16-bit | NONE |
| 33 | `0011-0011` | IIII-IIII  | `MVI H, Imm`        | Move immediate value to H         | Move Immediate H | 16-bit | NONE |
| 34 | `0011-0100` | NONE       | `LUMA`              | Load value from address selected in M into A | Load Using M   | 8-bit | NONE |
| 35 | `0011-0101` | NONE       | `SUMA`              | Store value from A into address selected in M | Store Using M  | 8-bit | NONE |
| 36 | `0011-0110` | NONE       | `ADD A, B`          | Add value in B to A                      | Add | 8-bit | NONE |
| 37 | `0011-0111` | NONE       | `ADD A, C`          | Add value in C to A                      | Add | 8-bit | NONE |
| 38 | `0011-1000` | NONE       | `ADD A, D`          | Add value in D to A                      | Add | 8-bit | NONE |
| 39 | `0011-1001` | NONE       | `ADD A, E`          | Add value in E to A                      | Add | 8-bit | NONE |
| 3A | `0011-1010` | NONE       | `ADD A, L`          | Add value in L to A                      | Add | 8-bit | NONE |
| 3B | `0011-1011` | NONE       | `ADD A, H`          | Add value in H to A                      | Add | 8-bit | NONE |
| 3C | `0011-1100` | NONE       | `ADD B, A`          | Add value in A to B                      | Add | 8-bit | NONE |
| 3D | `0011-1101` | NONE       | `ADD B, C`          | Add value in C to B                      | Add | 8-bit | NONE |
| 3E | `0011-1110` | NONE       | `ADD B, D`          | Add value in D to B                      | Add | 8-bit | NONE |
| 3F | `0011-1111` | NONE       | `ADD B, E`          | Add value in E to B                      | Add | 8-bit | NONE |
| 40 | `0100-0000` | NONE       | `ADD B, L`          | Add value in L to B                      | Add | 8-bit | NONE |
| 41 | `0100-0001` | NONE       | `ADD B, H`          | Add value in H to B                      | Add | 8-bit | NONE |
| 42 | `0100-0010` | NONE       | `ADD C, A`          | Add value in A to C                      | Add | 8-bit | NONE |
| 43 | `0100-0011` | NONE       | `ADD C, B`          | Add value in B to C                      | Add | 8-bit | NONE |
| 44 | `0100-0100` | NONE       | `ADD C, D`          | Add value in D to C                      | Add | 8-bit | NONE |
| 45 | `0100-0101` | NONE       | `ADD C, E`          | Add value in E to C                      | Add | 8-bit | NONE |
| 46 | `0100-0110` | NONE       | `ADD C, L`          | Add value in L to C                      | Add | 8-bit | NONE |
| 47 | `0100-0111` | NONE       | `ADD C, H`          | Add value in H to C                      | Add | 8-bit | NONE |
| 48 | `0100-1000` | NONE       | `ADD D, A`          | Add value in A to D                      | Add | 8-bit | NONE |
| 49 | `0100-1001` | NONE       | `ADD D, B`          | Add value in B to D                      | Add | 8-bit | NONE |
| 4A | `0100-1010` | NONE       | `ADD D, C`          | Add value in C to D                      | Add | 8-bit | NONE |
| 4B | `0100-1011` | NONE       | `ADD D, E`          | Add value in E to D                      | Add | 8-bit | NONE |
| 4C | `0100-1100` | NONE       | `ADD D, L`          | Add value in L to D                      | Add | 8-bit | NONE |
| 4D | `0100-1101` | NONE       | `ADD D, H`          | Add value in H to D                      | Add | 8-bit | NONE |
| 4E | `0100-1110` | NONE       | `ADD E, A`          | Add value in A to E                      | Add | 8-bit | NONE |
| 4F | `0100-1111` | NONE       | `ADD E, B`          | Add value in B to E                      | Add | 8-bit | NONE |
| 50 | `0101-0000` | NONE       | `ADD E, C`          | Add value in C to E                      | Add | 8-bit | NONE |
| 51 | `0101-0001` | NONE       | `ADD E, D`          | Add value in D to E                      | Add | 8-bit | NONE |
| 52 | `0101-0010` | NONE       | `ADD E, L`          | Add value in L to E                      | Add | 8-bit | NONE |
| 53 | `0101-0011` | NONE       | `ADD E, H`          | Add value in H to E                      | Add | 8-bit | NONE |
| 54 | `0101-0100` | NONE       | `ADD L, A`          | Add value in A to L                      | Add | 8-bit | NONE |
| 55 | `0101-0101` | NONE       | `ADD L, B`          | Add value in B to L                      | Add | 8-bit | NONE |
| 56 | `0101-0110` | NONE       | `ADD L, C`          | Add value in C to L                      | Add | 8-bit | NONE |
| 57 | `0101-0111` | NONE       | `ADD L, D`          | Add value in D to L                      | Add | 8-bit | NONE |
| 58 | `0101-1000` | NONE       | `ADD L, E`          | Add value in E to L                      | Add | 8-bit | NONE |
| 59 | `0101-1001` | NONE       | `ADD L, H`          | Add value in H to L                      | Add | 8-bit | NONE |
| 5A | `0101-1010` | NONE       | `ADD H, A`          | Add value in A to H                      | Add | 8-bit | NONE |
| 5B | `0101-1011` | NONE       | `ADD H, B`          | Add value in B to H                      | Add | 8-bit | NONE |
| 5C | `0101-1100` | NONE       | `ADD H, C`          | Add value in C to H                      | Add | 8-bit | NONE |
| 5D | `0101-1101` | NONE       | `ADD H, D`          | Add value in D to H                      | Add | 8-bit | NONE |
| 5E | `0101-1110` | NONE       | `ADD H, E`          | Add value in E to H                      | Add | 8-bit | NONE |
| 5F | `0101-1111` | NONE       | `ADD H, L`          | Add value in L to H                      | Add | 8-bit | NONE |
| 60 | `0110-0000` | NONE       | `SUB A, B`          | Subtract value in B from A                | Subtract | 8-bit | NONE |
| 61 | `0110-0001` | NONE       | `SUB A, C`          | Subtract value in C from A                | Subtract | 8-bit | NONE |
| 62 | `0110-0010` | NONE       | `SUB A, D`          | Subtract value in D from A                | Subtract | 8-bit | NONE |
| 63 | `0110-0011` | NONE       | `SUB A, E`          | Subtract value in E from A                | Subtract | 8-bit | NONE |
| 64 | `0110-0100` | NONE       | `SUB A, L`          | Subtract value in L from A                | Subtract | 8-bit | NONE |
| 65 | `0110-0101` | NONE       | `SUB A, H`          | Subtract value in H from A                | Subtract | 8-bit | NONE |
| 66 | `0110-0110` | NONE       | `SUB B, A`          | Subtract value in A from B                | Subtract | 8-bit | NONE |
| 67 | `0110-0111` | NONE       | `SUB B, C`          | Subtract value in C from B                | Subtract | 8-bit | NONE |
| 68 | `0110-1000` | NONE       | `SUB B, D`          | Subtract value in D from B                | Subtract | 8-bit | NONE |
| 69 | `0110-1001` | NONE       | `SUB B, E`          | Subtract value in E from B                | Subtract | 8-bit | NONE |
| 6A | `0110-1010` | NONE       | `SUB B, L`          | Subtract value in L from B                | Subtract | 8-bit | NONE |
| 6B | `0110-1011` | NONE       | `SUB B, H`          | Subtract value in H from B                | Subtract | 8-bit | NONE |
| 6C | `0110-1100` | NONE       | `SUB C, A`          | Subtract value in A from C                | Subtract | 8-bit | NONE |
| 6D | `0110-1101` | NONE       | `SUB C, B`          | Subtract value in B from C                | Subtract | 8-bit | NONE |
| 6E | `0110-1110` | NONE       | `SUB C, D`          | Subtract value in D from C                | Subtract | 8-bit | NONE |
| 6F | `0110-1111` | NONE       | `SUB C, E`          | Subtract value in E from C                | Subtract | 8-bit | NONE |
| 70 | `0111-0000` | NONE       | `SUB C, L`          | Subtract value in L from C                | Subtract | 8-bit | NONE |
| 71 | `0111-0001` | NONE       | `SUB C, H`          | Subtract value in H from C                | Subtract | 8-bit | NONE |
| 72 | `0111-0010` | NONE       | `SUB D, A`          | Subtract value in A from D                | Subtract | 8-bit | NONE |
| 73 | `0111-0011` | NONE       | `SUB D, B`          | Subtract value in B from D                | Subtract | 8-bit | NONE |
| 74 | `0111-0100` | NONE       | `SUB D, C`          | Subtract value in C from D                | Subtract | 8-bit | NONE |
| 75 | `0111-0101` | NONE       | `SUB D, E`          | Subtract value in E from D                | Subtract | 8-bit | NONE |
| 76 | `0111-0110` | NONE       | `SUB D, L`          | Subtract value in L from D                | Subtract | 8-bit | NONE |
| 77 | `0111-0111` | NONE       | `SUB D, H`          | Subtract value in H from D                | Subtract | 8-bit | NONE |
| 78 | `0111-1000` | NONE       | `SUB E, A`          | Subtract value in A from E                | Subtract | 8-bit | NONE |
| 79 | `0111-1001` | NONE       | `SUB E, B`          | Subtract value in B from E                | Subtract | 8-bit | NONE |
| 7A | `0111-1010` | NONE       | `SUB E, C`          | Subtract value in C from E                | Subtract | 8-bit | NONE |
| 7B | `0111-1011` | NONE       | `SUB E, D`          | Subtract value in D from E                | Subtract | 8-bit | NONE |
| 7C | `0111-1100` | NONE       | `SUB E, L`          | Subtract value in L from E                | Subtract | 8-bit | NONE |
| 7D | `0111-1101` | NONE       | `SUB E, H`          | Subtract value in H from E                | Subtract | 8-bit | NONE |
| 7E | `0111-1110` | NONE       | `SUB L, A`          | Subtract value in A from L                | Subtract | 8-bit | NONE |
| 7F | `0111-1111` | NONE       | `SUB L, B`          | Subtract value in B from L                | Subtract | 8-bit | NONE |
| 80 | `1000-0000` | NONE       | `SUB L, C`          | Subtract value in C from L                | Subtract | 8-bit | NONE |
| 81 | `1000-0001` | NONE       | `SUB L, D`          | Subtract value in D from L                | Subtract | 8-bit | NONE |
| 82 | `1000-0010` | NONE       | `SUB L, E`          | Subtract value in E from L                | Subtract | 8-bit | NONE |
| 83 | `1000-0011` | NONE       | `SUB L, H`          | Subtract value in H from L                | Subtract | 8-bit | NONE |
| 84 | `1000-0100` | NONE       | `SUB H, A`          | Subtract value in A from H                | Subtract | 8-bit | NONE |
| 85 | `1000-0101` | NONE       | `SUB H, B`          | Subtract value in B from H                | Subtract | 8-bit | NONE |
| 86 | `1000-0110` | NONE       | `SUB H, C`          | Subtract value in C from H                | Subtract | 8-bit | NONE |
| 87 | `1000-0111` | NONE       | `SUB H, D`          | Subtract value in D from H                | Subtract | 8-bit | NONE |
| 88 | `1000-1000` | NONE       | `SUB H, E`          | Subtract value in E from H                | Subtract | 8-bit | NONE |
| 89 | `1000-1001` | NONE       | `SUB H, L`          | Subtract value in L from H                | Subtract | 8-bit | NONE |
| 8A | `1000-1010` | IIII-IIII       | `ADI A, Imm`        | Add immediate value to A                | Add Immediate A | 16-bit | 8-bit |
| 8B | `1000-1011` | IIII-IIII       | `ADI B, Imm`        | Add immediate value to B                | Add Immediate B | 16-bit | 8-bit |
| 8C | `1000-1100` | IIII-IIII       | `ADI C, Imm`        | Add immediate value to C                | Add Immediate C | 16-bit | 8-bit |
| 8D | `1000-1101` | IIII-IIII       | `ADI D, Imm`        | Add immediate value to D                | Add Immediate D | 16-bit | 8-bit |
| 8E | `1000-1110` | IIII-IIII       | `ADI E, Imm`        | Add immediate value to E                | Add Immediate E | 16-bit | 8-bit |
| 8F | `1000-1111` | IIII-IIII       | `ADI L, Imm`        | Add immediate value to L                | Add Immediate L | 16-bit | 8-bit |
| 90 | `1001-0000` | IIII-IIII       | `ADI H, Imm`        | Add immediate value to H                | Add Immediate H | 16-bit | 8-bit |
| 91 | `1001-0001` | IIII-IIII       | `SBI A, Imm`        | Subtract immediate value from A           | Subtract Immediate A | 16-bit | 8-bit |
| 92 | `1001-0010` | IIII-IIII       | `SBI B, Imm`        | Subtract immediate value from B           | Subtract Immediate B | 16-bit | 8-bit |
| 93 | `1001-0011` | IIII-IIII       | `SBI C, Imm`        | Subtract immediate value from C           | Subtract Immediate C | 16-bit | 8-bit |
| 94 | `1001-0100` | IIII-IIII       | `SBI D, Imm`        | Subtract immediate value from D           | Subtract Immediate D | 16-bit | 8-bit |
| 95 | `1001-0101` | IIII-IIII       | `SBI E, Imm`        | Subtract immediate value from E           | Subtract Immediate E | 16-bit | 8-bit |
| 96 | `1001-0110` | IIII-IIII       | `SBI L, Imm`        | Subtract immediate value from L           | Subtract Immediate L | 16-bit | 8-bit |
| 97 | `1001-0111` | IIII-IIII       | `SBI H, Imm`        | Subtract immediate value from H           | Subtract Immediate H | 16-bit | 8-bit |
| 98 | `1001-1000` | NONE       | `INC A`             | Increment value in A                        | Increment A | 8-bit | NONE |
| 99 | `1001-1001` | NONE       | `INC B`             | Increment value in B                        | Increment B | 8-bit | NONE |
| 9A | `1001-1010` | NONE       | `INC C`             | Increment value in C                        | Increment C | 8-bit | NONE |
| 9B | `1001-1011` | NONE       | `INC D`             | Increment value in D                        | Increment D | 8-bit | NONE |
| 9C | `1001-1100` | NONE       | `INC E`             | Increment value in E                        | Increment E | 8-bit | NONE |
| 9D | `1001-1101` | NONE       | `INC L`             | Increment value in L                        | Increment L | 8-bit | NONE |
| 9E | `1001-1110` | NONE       | `INC H`             | Increment value in H                        | Increment H | 8-bit | NONE |
| 9F | `1001-1111` | NONE       | `DEC A`             | Decrement value in A                        | Decrement A | 8-bit | NONE |
| A0 | `1010-0000` | NONE       | `DEC B`             | Decrement value in B                        | Decrement B | 8-bit | NONE |
| A1 | `1010-0001` | NONE       | `DEC C`             | Decrement value in C                        | Decrement C | 8-bit | NONE |
| A2 | `1010-0010` | NONE       | `DEC D`             | Decrement value in D                        | Decrement D | 8-bit | NONE |
| A3 | `1010-0011` | NONE       | `DEC E`             | Decrement value in E                        | Decrement E | 8-bit | NONE |
| A4 | `1010-0100` | NONE       | `DEC L`             | Decrement value in L                        | Decrement L | 8-bit | NONE |
| A5 | `1010-0101` | NONE       | `DEC H`             | Decrement value in H                        | Decrement H | 8-bit | NONE |
| A6 | `1010-0110` | NONE       | `CMP A, B`         | Compare value in A with B                  | Compare | 8-bit | NONE |
| A7 | `1010-0111` | NONE       | `CMP A, C`         | Compare value in A with C                  | Compare | 8-bit | NONE |
| A8 | `1010-1000` | NONE       | `CMP A, D`         | Compare value in A with D                  | Compare | 8-bit | NONE |
| A9 | `1010-1001` | NONE       | `CMP A, E`         | Compare value in A with E                  | Compare | 8-bit | NONE |
| AA | `1010-1010` | NONE       | `CMP A, L`         | Compare value in A with L                  | Compare | 8-bit | NONE |
| AB | `1010-1011` | NONE       | `CMP A, H`         | Compare value in A with H                  | Compare | 8-bit | NONE |
| AC | `1010-1100` | NONE       | `CMP B, A`         | Compare value in B with A                  | Compare | 8-bit | NONE |
| AD | `1010-1101` | NONE       | `CMP B, C`         | Compare value in B with C                  | Compare | 8-bit | NONE |
| AE | `1010-1110` | NONE       | `CMP B, D`         | Compare value in B with D                  | Compare | 8-bit | NONE |
| AF | `1010-1111` | NONE       | `CMP B, E`         | Compare value in B with E                  | Compare | 8-bit | NONE |
| B0 | `1011-0000` | NONE       | `CMP B, L`         | Compare value in B with L                  | Compare | 8-bit | NONE |
| B1 | `1011-0001` | NONE       | `CMP B, H`         | Compare value in B with H                  | Compare | 8-bit | NONE |
| B2 | `1011-0010` | NONE       | `CMP C, A`         | Compare value in C with A                  | Compare | 8-bit | NONE |
| B3 | `1011-0011` | NONE       | `CMP C, B`         | Compare value in C with B                  | Compare | 8-bit | NONE |
| B4 | `1011-0100` | NONE       | `CMP C, D`         | Compare value in C with D                  | Compare | 8-bit | NONE |
| B5 | `1011-0101` | NONE       | `CMP C, E`         | Compare value in C with E                  | Compare | 8-bit | NONE |
| B6 | `1011-0110` | NONE       | `CMP C, L`         | Compare value in C with L                  | Compare | 8-bit | NONE |
| B7 | `1011-0111` | NONE       | `CMP C, H`         | Compare value in C with H                  | Compare | 8-bit | NONE |
| B8 | `1011-1000` | NONE       | `CMP D, A`         | Compare value in D with A                  | Compare | 8-bit | NONE |
| B9 | `1011-1001` | NONE       | `CMP D, B`         | Compare value in D with B                  | Compare | 8-bit | NONE |
| BA | `1011-1010` | NONE       | `CMP D, C`         | Compare value in D with C                  | Compare | 8-bit | NONE |
| BB | `1011-1011` | NONE       | `CMP D, E`         | Compare value in D with E                  | Compare | 8-bit | NONE |
| BC | `1011-1100` | NONE       | `CMP D, L`         | Compare value in D with L                  | Compare | 8-bit | NONE |
| BD | `1011-1101` | NONE       | `CMP D, H`         | Compare value in D with H                  | Compare | 8-bit | NONE |
| BE | `1011-1110` | NONE       | `CMP E, A`         | Compare value in E with A                  | Compare | 8-bit | NONE |
| BF | `1011-1111` | NONE       | `CMP E, B`         | Compare value in E with B                  | Compare | 8-bit | NONE |
| C0 | `1100-0000` | NONE       | `CMP E, C`         | Compare value in E with C                  | Compare | 8-bit | NONE |
| C1 | `1100-0001` | NONE       | `CMP E, D`         | Compare value in E with D                  | Compare | 8-bit | NONE |
| C2 | `1100-0010` | NONE       | `CMP E, L`         | Compare value in E with L                  | Compare | 8-bit | NONE |
| C3 | `1100-0011` | NONE       | `CMP E, H`         | Compare value in E with H                  | Compare | 8-bit | NONE |
| C4 | `1100-0100` | NONE       | `CMP L, A`         | Compare value in L with A                  | Compare | 8-bit | NONE |
| C5 | `1100-0101` | NONE       | `CMP L, B`         | Compare value in L with B                  | Compare | 8-bit | NONE |
| C6 | `1100-0110` | NONE       | `CMP L, C`         | Compare value in L with C                  | Compare | 8-bit | NONE |
| C7 | `1100-0111` | NONE       | `CMP L, D`         | Compare value in L with D                  | Compare | 8-bit | NONE |
| C8 | `1100-1000` | NONE       | `CMP L, E`         | Compare value in L with E                  | Compare | 8-bit | NONE |
| C9 | `1100-1001` | NONE       | `CMP L, H`         | Compare value in L with H                  | Compare | 8-bit | NONE |
| CA | `1100-1010` | NONE       | `CMP H, A`         | Compare value in H with A                  | Compare | 8-bit | NONE |
| CB | `1100-1011` | NONE       | `CMP H, B`         | Compare value in H with B                  | Compare | 8-bit | NONE |
| CC | `1100-1100` | NONE       | `CMP H, C`         | Compare value in H with C                  | Compare | 8-bit | NONE |
| CD | `1100-1101` | NONE       | `CMP H, D`         | Compare value in H with D                  | Compare | 8-bit | NONE |
| CE | `1100-1110` | NONE       | `CMP H, E`         | Compare value in H with E                  | Compare | 8-bit | NONE |
| CF | `1100-1111` | NONE       | `CMP H, L`         | Compare value in H with L                  | Compare | 8-bit | NONE |
| D0 | `1101-0000` | IIII-IIII  | `CPI A, Imm`        | Compare immediate value with A             | Compare Immediate A | 16-bit | 8-bit |
| D1 | `1101-0001` | IIII-IIII  | `CPI B, Imm`        | Compare immediate value with B             | Compare Immediate B | 16-bit | 8-bit |
| D2 | `1101-0010` | IIII-IIII  | `CPI C, Imm`        | Compare immediate value with C             | Compare Immediate C | 16-bit | 8-bit |
| D3 | `1101-0011` | IIII-IIII  | `CPI D, Imm`        | Compare immediate value with D             | Compare Immediate D | 16-bit | 8-bit |
| D4 | `1101-0100` | IIII-IIII  | `CPI E, Imm`        | Compare immediate value with E             | Compare Immediate E | 16-bit | 8-bit |
| D5 | `1101-0101` | IIII-IIII  | `CPI L, Imm`        | Compare immediate value with L             | Compare Immediate L | 16-bit | 8-bit |
| D6 | `1101-0110` | IIII-IIII  | `CPI H, Imm`        | Compare immediate value with H             | Compare Immediate H | 16-bit | 8-bit |
| D7 | `1101-0111` | IIII-IIII-IIII-IIII       | `JMP`        | Jump to address | Jump | 24-bit | 16-bit |
| D8 | `1101-1000` | IIII-IIII-IIII-IIII       | `JZ`         | Jump to address if zero flag is set | Jump Zero | 24-bit | 16-bit |
| D9 | `1101-1001` | IIII-IIII-IIII-IIII       | `JNZ`        | Jump to address if zero flag is not set | Jump Not Zero | 24-bit | 16-bit |
| DA | `1101-1010` | IIII-IIII-IIII-IIII       | `JC`         | Jump to address if carry flag is set | Jump Carry | 24-bit | 16-bit |
| DB | `1101-1011` | IIII-IIII-IIII-IIII       | `JNC`        | Jump to address if carry flag is not set | Jump Not Carry | 24-bit | 16-bit |
| DC | `1101-1100` | IIII-IIII-IIII-IIII       | `JZC`        | Jump to address if zero and carry flags are set | Jump Zero Carry | 24-bit | 16-bit |
| DD | `1101-1101` | IIII-IIII-IIII-IIII       | `CALL`             | Call subroutine at address                  | Call Subroutine | 24-bit | 16-bit |
| DE | `1101-1110` | NONE                      | `RET`              | Return from subroutine                      | Return Subroutine | 8-bit | NONE |
| DF | `1101-1111` | NONE                      | `JMM`              | Jump to address in M                        | Jump Using M | 8-bit | NONE |
| E0 | `1110-0000` | NONE                      | `JZM`             | Jump to address in M if zero flag is set   | Jump Using M Zero | 8-bit | NONE |
| E1 | `1110-0001` | NONE                      | `JNZM`            | Jump to address in M if zero flag is not set | Jump Using M Not Zero | 8-bit | NONE |
| E2 | `1110-0010` | NONE                      | `JCM`             | Jump to address in M if carry flag is set  | Jump Using M Carry | 8-bit | NONE |
| E3 | `1110-0011` | NONE                      | `JNCM`            | Jump to address in M if carry flag is not set | Jump Using M Not Carry | 8-bit | NONE |
| E4 | `1110-0100` | NONE                      | `CALM`            | Call subroutine at address in M            | Call Subroutine Using M | 8-bit | NONE |
| E5 | `1110-0101` | NONE                      | `AND A, B`         | Logical AND value in A with B              | Logical AND | 8-bit | NONE |
| E6 | `1110-0110` | NONE                      | `AND A, C`         | Logical AND value in A with C              | Logical AND | 8-bit | NONE |
| E7 | `1110-0111` | NONE                      | `AND A, D`         | Logical AND value in A with D              | Logical AND | 8-bit | NONE |
| E8 | `1110-1000` | NONE                      | `AND A, E`         | Logical AND value in A with E              | Logical AND | 8-bit | NONE |
| E9 | `1110-1001` | NONE                      | `AND A, L`         | Logical AND value in A with L              | Logical AND | 8-bit | NONE |
| EA | `1110-1010` | NONE                      | `AND A, H`         | Logical AND value in A with H              | Logical AND | 8-bit | NONE |
| EB | `1110-1011` | NONE                      | `OR A, B`          | Logical OR value in A with B               | Logical OR | 8-bit | NONE |
| EC | `1110-1100` | NONE                      | `OR A, C`          | Logical OR value in A with C               | Logical OR | 8-bit | NONE |
| ED | `1110-1101` | NONE                      | `OR A, D`          | Logical OR value in A with D               | Logical OR | 8-bit | NONE |
| EE | `1110-1110` | NONE                      | `OR A, E`          | Logical OR value in A with E               | Logical OR | 8-bit | NONE |
| EF | `1110-1111` | NONE                      | `OR A, L`          | Logical OR value in A with L               | Logical OR | 8-bit | NONE |
| F0 | `1111-0000` | NONE                      | `OR A, H`          | Logical OR value in A with H               | Logical OR | 8-bit | NONE |
| F1 | `1111-0001` | NONE                      | `XOR A, B`         | Logical XOR value in A with B              | Logical XOR | 8-bit | NONE |
| F2 | `1111-0010` | NONE                      | `XOR A, C`         | Logical XOR value in A with C              | Logical XOR | 8-bit | NONE |
| F3 | `1111-0011` | NONE                      | `XOR A, D`         | Logical XOR value in A with D              | Logical XOR | 8-bit | NONE |
| F4 | `1111-0100` | NONE                      | `XOR A, E`         | Logical XOR value in A with E              | Logical XOR | 8-bit | NONE |
| F5 | `1111-0101` | NONE                      | `XOR A, L`         | Logical XOR value in A with L              | Logical XOR | 8-bit | NONE |
| F6 | `1111-0110` | NONE                      | `XOR A, H`         | Logical XOR value in A with H              | Logical XOR | 8-bit | NONE |
| F7 | `1111-0111` | NONE                      | `NOT A`             | Logical NOT value in A                     | Logical NOT | 8-bit | NONE |
| F8 | `1111-1000` | NONE                      | `NOP`             | Do Nothing                        | No Operation | 8-bit | NONE |
| F9 | `1111-1001` | NONE                      | `SHL A`             | Shift value in A left by 1 bit            | Shift Left | 8-bit | NONE |
| FA | `1111-1010` | NONE                      | `SHR A`             | Shift value in A right by 1 bit           | Shift Right | 8-bit | NONE |
| FB | `1111-1011` | NONE                      | `ROL A`             | Rotate value in A left by 1 bit           | Rotate Left | 8-bit | NONE |
| FC | `1111-1100` | NONE                      | `ROR A`             | Rotate value in A right by 1 bit          | Rotate Right | 8-bit | NONE |
| FD | `1111-1101` | NONE                      | `IN 0`             | Input from port 0 into A                   | Input Port 0 | 8-bit | NONE |
| FE | `1111-1110` | NONE                      | `OUT 0`            | Output value in A to port 0               | Output Port 0 | 8-bit | NONE |
| FF | `1111-1111` | NONE                      | `EXT`             | Extended instruction set   (FOR LATER)           | Extended Instruction Set | 8-bit | NONE |