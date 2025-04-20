#include "barc.h"

#include <stdlib.h>

void emu_init()
{
    // Initialize the memory space and registers
    for (int i = 0; i < 0xFFFF; i++)
    {
        MemorySpace[i] = 0;
    }
    for (int i = 0; i < 7; i++)
    {
        Registers[i] = 0;
    }
    SP = 0;
    PC = 0;

    ClearFlag(ZERO);
    ClearFlag(CARRY);
    ClearFlag(SIGN);
    ClearFlag(PARITY);
    
    for (int i = 0; i < MAX_CALL_STACK_SIZE; i++)
    {
        CallStack[i] = 0;
    }
}

void execute_extended()
{
    uint8_t opcode = FetchByte();
    switch (opcode)
    {
        case 0x00: // MULT Rd, Rs
            Registers[FetchByte()] *= Registers[FetchByte()];
            break;
        case 0x01: // DIV Rd, Rs
            if (Registers[PeekByte()] == 0)
            {
                printf("Divide by zero error\n");
                DumpRegisters();
                exit(DIVIDE_BY_ZERO);
            }
            Registers[FetchByte()] /= Registers[FetchByte()];
            break;
        default:
            printf("Invalid Extended Opcode\n");
            DumpRegisters();
            exit(INVALID_OPCODE);
    }
}

void execute_instruction()
{
    uint8_t opcode = FetchByte();
    switch (opcode)
    {
        case 0x00: // HLT
            printf("HLT\n");
            exit(0);
            break;
        case 0x01: // MOV A, B
            Registers[A] = Registers[B];
            break;
        case 0x02: // MOV A, C
            Registers[A] = Registers[C];
            break;
        case 0x03: // MOV A, D
            Registers[A] = Registers[D];
            break;
        case 0x04: // MOV A, E
            Registers[A] = Registers[E];
            break;
        case 0x05: // MOV A, L
            Registers[A] = Registers[L];
            break;
        case 0x06: // MOV A, H
            Registers[A] = Registers[H];
            break;
        case 0x07: // MOV B, A
            Registers[B] = Registers[A];
            break;
        case 0x08: // MOV B, C
            Registers[B] = Registers[C];
            break;
        case 0x09: // MOV B, D
            Registers[B] = Registers[D];
            break;
        case 0x0A: // MOV B, E
            Registers[B] = Registers[E];
            break;
        case 0x0B: // MOV B, L
            Registers[B] = Registers[L];
            break;
        case 0x0C: // MOV B, H
            Registers[B] = Registers[H];
            break;
        case 0x0D: // MOV C, A
            Registers[C] = Registers[A];
            break;
        case 0x0E: // MOV C, B
            Registers[C] = Registers[B];
            break;
        case 0x0F: // MOV C, D
            Registers[C] = Registers[D];
            break;
        case 0x10: // MOV C, E
            Registers[C] = Registers[E];
            break;
        case 0x11: // MOV C, L
            Registers[C] = Registers[L];
            break;
        case 0x12: // MOV C, H
            Registers[C] = Registers[H];
            break;
        case 0x13: // MOV D, A
            Registers[D] = Registers[A];
            break;
        case 0x14: // MOV D, B
            Registers[D] = Registers[B];
            break;
        case 0x15: // MOV D, C
            Registers[D] = Registers[C];
            break;
        case 0x16: // MOV D, E
            Registers[D] = Registers[E];
            break;
        case 0x17: // MOV D, L
            Registers[D] = Registers[L];
            break;
        case 0x18: // MOV D, H
            Registers[D] = Registers[H];
            break;
        case 0x19: // MOV E, A
            Registers[E] = Registers[A];
            break;
        case 0x1A: // MOV E, B
            Registers[E] = Registers[B];
            break;
        case 0x1B: // MOV E, C
            Registers[E] = Registers[C];
            break;
        case 0x1C: // MOV E, D
            Registers[E] = Registers[D];
            break;
        case 0x1D: // MOV E, L
            Registers[E] = Registers[L];
            break;
        case 0x1E: // MOV E, H
            Registers[E] = Registers[H];
            break;
        case 0x1F: // MOV L, A
            Registers[L] = Registers[A];
            break;
        case 0x20: // MOV L, B
            Registers[L] = Registers[B];
            break;
        case 0x21: // MOV L, C
            Registers[L] = Registers[C];
            break;
        case 0x22: // MOV L, D
            Registers[L] = Registers[D];
            break;
        case 0x23: // MOV L, E
            Registers[L] = Registers[E];
            break;
        case 0x24: // MOV L, H
            Registers[L] = Registers[H];
            break;
        case 0x25: // MOV H, A
            Registers[H] = Registers[A];
            break;
        case 0x26: // MOV H, B
            Registers[H] = Registers[B];
            break;
        case 0x27: // MOV H, C
            Registers[H] = Registers[C];
            break;
        case 0x28: // MOV H, D
            Registers[H] = Registers[D];
            break;
        case 0x29: // MOV H, E
            Registers[H] = Registers[E];
            break;
        case 0x2A: // MOV H, L
            Registers[H] = Registers[L];
            break;
        case 0x2B: // LAA
            Registers[A] = MemorySpace[FetchWord()];
            break;
        case 0x2C: // SAA
            MemorySpace[FetchWord()] = Registers[A];
            break;
        case 0x2D: // MVI A, Imm
            Registers[A] = FetchByte();
            break;
        case 0x2E: // MVI B, Imm
            Registers[B] = FetchByte();
            break;
        case 0x2F: // MVI C, Imm
            Registers[C] = FetchByte();
            break;
        case 0x30: // MVI D, Imm
            Registers[D] = FetchByte();
            break;
        case 0x31: // MVI E, Imm
            Registers[E] = FetchByte();
            break;
        case 0x32: // MVI L, Imm
            Registers[L] = FetchByte();
            break;
        case 0x33: // MVI H, Imm
            Registers[H] = FetchByte();
            break;
        case 0x34: // LUMA (Load value from address selected in M into A)
            Registers[A] = MemorySpace[(Registers[L] << 8) | Registers[H]];
            break;
        case 0x35: // SUMA (Store value from A into address selected in M)
            MemorySpace[(Registers[L] << 8) | Registers[H]] = Registers[A];
            break;
        case 0x36: // ADD A, B
            Registers[A] += Registers[B];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x37: // ADD A, C
            Registers[A] += Registers[C];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x38: // ADD A, D
            Registers[A] += Registers[D];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x39: // ADD A, E
            Registers[A] += Registers[E];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x3A: // ADD A, L
            Registers[A] += Registers[L];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x3B: // ADD A, H
            Registers[A] += Registers[H];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x3C: // ADD B, A
            Registers[B] += Registers[A];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x3D: // ADD B, C
            Registers[B] += Registers[C];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x3E: // ADD B, D
            Registers[B] += Registers[D];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x3F: // ADD B, E
            Registers[B] += Registers[E];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x40: // ADD B, L
            Registers[B] += Registers[L];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x41: // ADD B, H
            Registers[B] += Registers[H];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x42: // ADD C, A
            Registers[C] += Registers[A];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x43: // ADD C, B
            Registers[C] += Registers[B];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x44: // ADD C, D
            Registers[C] += Registers[D];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x45: // ADD C, E
            Registers[C] += Registers[E];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x46: // ADD C, L
            Registers[C] += Registers[L];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x47: // ADD C, H
            Registers[C] += Registers[H];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x48: // ADD D, A
            Registers[D] += Registers[A];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x49: // ADD D, B
            Registers[D] += Registers[B];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x4A: // ADD D, C
            Registers[D] += Registers[C];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x4B: // ADD D, E
            Registers[D] += Registers[E];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x4C: // ADD D, L
            Registers[D] += Registers[L];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x4D: // ADD D, H
            Registers[D] += Registers[H];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x4E: // ADD E, A
            Registers[E] += Registers[A];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x4F: // ADD E, B
            Registers[E] += Registers[B];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x50: // ADD E, C
            Registers[E] += Registers[C];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x51: // ADD E, D
            Registers[E] += Registers[D];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x52: // ADD E, L
            Registers[E] += Registers[L];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x53: // ADD E, H
            Registers[E] += Registers[H];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x54: // ADD L, A
            Registers[L] += Registers[A];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x55: // ADD L, B
            Registers[L] += Registers[B];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x56: // ADD L, C
            Registers[L] += Registers[C];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x57: // ADD L, D
            Registers[L] += Registers[D];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x58: // ADD L, E
            Registers[L] += Registers[E];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x59: // ADD L, H
            Registers[L] += Registers[H];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x5A: // ADD H, A
            Registers[H] += Registers[A];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x5B: // ADD H, B
            Registers[H] += Registers[B];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x5C: // ADD H, C
            Registers[H] += Registers[C];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x5D: // ADD H, D
            Registers[H] += Registers[D];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x5E: // ADD H, E
            Registers[H] += Registers[E];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x5F: // ADD H, L
            Registers[H] += Registers[L];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x60: // SUB A, B
            Registers[A] -= Registers[B];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x61: // SUB A, C
            Registers[A] -= Registers[C];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x62: // SUB A, D
            Registers[A] -= Registers[D];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x63: // SUB A, E
            Registers[A] -= Registers[E];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x64: // SUB A, L
            Registers[A] -= Registers[L];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x65: // SUB A, H
            Registers[A] -= Registers[H];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x66: // SUB B, A
            Registers[B] -= Registers[A];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x67: // SUB B, C
            Registers[B] -= Registers[C];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x68: // SUB B, D
            Registers[B] -= Registers[D];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x69: // SUB B, E
            Registers[B] -= Registers[E];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x6A: // SUB B, L
            Registers[B] -= Registers[L];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x6B: // SUB B, H
            Registers[B] -= Registers[H];
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x6C: // SUB C, A
            Registers[C] -= Registers[A];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x6D: // SUB C, B
            Registers[C] -= Registers[B];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x6E: // SUB C, D
            Registers[C] -= Registers[D];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x6F: // SUB C, E
            Registers[C] -= Registers[E];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x70: // SUB C, L
            Registers[C] -= Registers[L];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x71: // SUB C, H
            Registers[C] -= Registers[H];
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x72: // SUB D, A
            Registers[D] -= Registers[A];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x73: // SUB D, B
            Registers[D] -= Registers[B];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x74: // SUB D, C
            Registers[D] -= Registers[C];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x75: // SUB D, E
            Registers[D] -= Registers[E];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x76: // SUB D, L
            Registers[D] -= Registers[L];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x77: // SUB D, H
            Registers[D] -= Registers[H];
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x78: // SUB E, A
            Registers[E] -= Registers[A];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x79: // SUB E, B
            Registers[E] -= Registers[B];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x7A: // SUB E, C
            Registers[E] -= Registers[C];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x7B: // SUB E, D
            Registers[E] -= Registers[D];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x7C: // SUB E, L
            Registers[E] -= Registers[L];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x7D: // SUB E, H
            Registers[E] -= Registers[H];
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x7E: // SUB L, A
            Registers[L] -= Registers[A];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x7F: // SUB L, B
            Registers[L] -= Registers[B];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x80: // SUB L, C
            Registers[L] -= Registers[C];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x81: // SUB L, D
            Registers[L] -= Registers[D];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x82: // SUB L, E
            Registers[L] -= Registers[E];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x83: // SUB L, H
            Registers[L] -= Registers[H];
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x84: // SUB H, A
            Registers[H] -= Registers[A];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x85: // SUB H, B
            Registers[H] -= Registers[B];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x86: // SUB H, C
            Registers[H] -= Registers[C];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x87: // SUB H, D
            Registers[H] -= Registers[D];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x88: // SUB H, E
            Registers[H] -= Registers[E];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x89: // SUB H, L
            Registers[H] -= Registers[L];
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x8A: // ADD A, Imm
            Registers[A] += FetchByte();
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x8B: // ADD B, Imm
            Registers[B] += FetchByte();
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x8C: // ADD C, Imm
            Registers[C] += FetchByte();
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x8D: // ADD D, Imm
            Registers[D] += FetchByte();
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x8E: // ADD E, Imm
            Registers[E] += FetchByte();
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x8F: // ADD L, Imm
            Registers[L] += FetchByte();
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x90: // ADD H, Imm
            Registers[H] += FetchByte();
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x91: // SUB A, Imm
            Registers[A] -= FetchByte();
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x92: // SUB B, Imm
            Registers[B] -= FetchByte();
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x93: // SUB C, Imm
            Registers[C] -= FetchByte();
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x94: // SUB D, Imm
            Registers[D] -= FetchByte();
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x95: // SUB E, Imm
            Registers[E] -= FetchByte();
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x96: // SUB L, Imm
            Registers[L] -= FetchByte();
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x97: // SUB H, Imm
            Registers[H] -= FetchByte();
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x98: // INC A
            Registers[A]++;
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x99: // INC B
            Registers[B]++;
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x9A: // INC C
            Registers[C]++;
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x9B: // INC D
            Registers[D]++;
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x9C: // INC E
            Registers[E]++;
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x9D: // INC L
            Registers[L]++;
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x9E: // INC H
            Registers[H]++;
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0x9F: // DEC A
            Registers[A]--;
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xA0: // DEC B
            Registers[B]--;
            if (Registers[B] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xA1: // DEC C
            Registers[C]--;
            if (Registers[C] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xA2: // DEC D
            Registers[D]--;
            if (Registers[D] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xA3: // DEC E
            Registers[E]--;
            if (Registers[E] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xA4: // DEC L
            Registers[L]--;
            if (Registers[L] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xA5: // DEC H
            Registers[H]--;
            if (Registers[H] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xA6: // CMP A, B
            if (Registers[A] == Registers[B])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] < Registers[B])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[A] ^ Registers[B]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xA7: // CMP A, C
            if (Registers[A] == Registers[C])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] < Registers[C])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[A] ^ Registers[C]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xA8: // CMP A, D
            if (Registers[A] == Registers[D])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] < Registers[D])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[A] ^ Registers[D]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xA9: // CMP A, E
            if (Registers[A] == Registers[E])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] < Registers[E])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[A] ^ Registers[E]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xAA: // CMP A, L
            if (Registers[A] == Registers[L])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] < Registers[L])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[A] ^ Registers[L]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xAB: // CMP A, H
            if (Registers[A] == Registers[H])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] < Registers[H])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[A] ^ Registers[H]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xAC: // CMP B, A
            if (Registers[B] == Registers[A])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] < Registers[A])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[B] ^ Registers[A]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xAD: // CMP B, C
            if (Registers[B] == Registers[C])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] < Registers[C])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[B] ^ Registers[C]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xAE: // CMP B, D
            if (Registers[B] == Registers[D])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] < Registers[D])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[B] ^ Registers[D]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xAF: // CMP B, E
            if (Registers[B] == Registers[E])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] < Registers[E])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[B] ^ Registers[E]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xB0: // CMP B, L
            if (Registers[B] == Registers[L])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] < Registers[L])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[B] ^ Registers[L]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xB1: // CMP B, H
            if (Registers[B] == Registers[H])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] < Registers[H])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[B] ^ Registers[H]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xB2: // CMP C, A
            if (Registers[C] == Registers[A])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] < Registers[A])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[C] ^ Registers[A]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xB3: // CMP C, B
            if (Registers[C] == Registers[B])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] < Registers[B])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[C] ^ Registers[B]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xB4: // CMP C, D
            if (Registers[C] == Registers[D])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] < Registers[D])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[C] ^ Registers[D]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xB5: // CMP C, E
            if (Registers[C] == Registers[E])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] < Registers[E])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[C] ^ Registers[E]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xB6: // CMP C, L
            if (Registers[C] == Registers[L])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] < Registers[L])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[C] ^ Registers[L]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xB7: // CMP C, H
            if (Registers[C] == Registers[H])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] < Registers[H])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[C] ^ Registers[H]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xB8: // CMP D, A
            if (Registers[D] == Registers[A])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] < Registers[A])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[D] ^ Registers[A]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xB9: // CMP D, B
            if (Registers[D] == Registers[B])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] < Registers[B])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[D] ^ Registers[B]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xBA: // CMP D, C
            if (Registers[D] == Registers[C])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] < Registers[C])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[D] ^ Registers[C]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xBB: // CMP D, E
            if (Registers[D] == Registers[E])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] < Registers[E])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[D] ^ Registers[E]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xBC: // CMP D, L
            if (Registers[D] == Registers[L])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] < Registers[L])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[D] ^ Registers[L]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xBD: // CMP D, H
            if (Registers[D] == Registers[H])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] < Registers[H])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[D] ^ Registers[H]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xBE: // CMP E, A
            if (Registers[E] == Registers[A])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] < Registers[A])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[E] ^ Registers[A]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xBF: // CMP E, B
            if (Registers[E] == Registers[B])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] < Registers[B])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[E] ^ Registers[B]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xC0: // CMP E, C
            if (Registers[E] == Registers[C])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] < Registers[C])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[E] ^ Registers[C]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xC1: // CMP E, D
            if (Registers[E] == Registers[D])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] < Registers[D])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[E] ^ Registers[D]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xC2: // CMP E, L
            if (Registers[E] == Registers[L])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] < Registers[L])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[E] ^ Registers[L]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xC3: // CMP E, H
            if (Registers[E] == Registers[H])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] < Registers[H])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[E] ^ Registers[H]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xC4: // CMP L, A
            if (Registers[L] == Registers[A])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] < Registers[A])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[L] ^ Registers[A]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xC5: // CMP L, B
            if (Registers[L] == Registers[B])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] < Registers[B])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[L] ^ Registers[B]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xC6: // CMP L, C
            if (Registers[L] == Registers[C])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] < Registers[C])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[L] ^ Registers[C]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xC7: // CMP L, D
            if (Registers[L] == Registers[D])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] < Registers[D])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[L] ^ Registers[D]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xC8: // CMP L, E
            if (Registers[L] == Registers[E])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] < Registers[E])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[L] ^ Registers[E]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xC9: // CMP L, H
            if (Registers[L] == Registers[H])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] < Registers[H])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[L] ^ Registers[H]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xCA: // CMP H, A
            if (Registers[H] == Registers[A])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] < Registers[A])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[H] ^ Registers[A]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xCB: // CMP H, B
            if (Registers[H] == Registers[B])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] < Registers[B])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[H] ^ Registers[B]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xCC: // CMP H, C
            if (Registers[H] == Registers[C])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] < Registers[C])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[H] ^ Registers[C]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xCD: // CMP H, D
            if (Registers[H] == Registers[D])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] < Registers[D])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[H] ^ Registers[D]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xCE: // CMP H, E
            if (Registers[H] == Registers[E])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] < Registers[E])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[H] ^ Registers[E]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xCF: // CMP H, L
            if (Registers[H] == Registers[L])
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] < Registers[L])
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[H] ^ Registers[L]) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xD0: // CPI A, Imm
            if (Registers[A] == PeekByte())
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] < PeekByte())
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[A] ^ PeekByte()) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);

            FetchByte(); // Consume the immediate value
            break;
        case 0xD1: // CPI B, Imm
            if (Registers[B] == PeekByte())
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[B] < PeekByte())
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[B] ^ PeekByte()) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);

            FetchByte(); // Consume the immediate value
            break;
        case 0xD2: // CPI C, Imm
            if (Registers[C] == PeekByte())
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[C] < PeekByte())
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[C] ^ PeekByte()) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);

            FetchByte(); // Consume the immediate value
            break;
        case 0xD3: // CPI D, Imm
            if (Registers[D] == PeekByte())
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[D] < PeekByte())
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[D] ^ PeekByte()) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);

            FetchByte(); // Consume the immediate value
            break;
        case 0xD4: // CPI E, Imm
            if (Registers[E] == PeekByte())
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[E] < PeekByte())
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[E] ^ PeekByte()) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);

            FetchByte(); // Consume the immediate value
            break;
        case 0xD5: // CPI L, Imm
            if (Registers[L] == PeekByte())
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[L] < PeekByte())
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[L] ^ PeekByte()) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);

            FetchByte(); // Consume the immediate value
            break;
        case 0xD6: // CPI H, Imm
            if (Registers[H] == PeekByte())
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[H] < PeekByte())
                SetFlag(CARRY);
            else
                ClearFlag(CARRY);
            if ((Registers[H] ^ PeekByte()) & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);

            FetchByte(); // Consume the immediate value
            break;
        case 0xD7: // JMP Imm
            PC = FetchWord();
            break;
        case 0xD8: // JZ Imm
            if (Flags.Z)
                PC = FetchWord();
            else
                PC += 2;
            break;
        case 0xD9: // JNZ Imm
            if (!Flags.Z)
                PC = FetchWord();
            else
                PC += 2;
            break;
        case 0xDA: // JC Imm
            if (Flags.C)
                PC = FetchWord();
            else
                PC += 2;
            break;
        case 0xDB: // JNC Imm
            if (!Flags.C)
                PC = FetchWord();
            else
                PC += 2;
            break;
        case 0xDC: // JZC Imm
            if (Flags.Z && Flags.C)
                PC = FetchWord();
            else
                PC += 2;
            break;
        case 0xDD: // CALL Imm
            PushCallStack(PC + 2);
            PC = FetchWord();
            break;
        case 0xDE: // RET
            PopCallStack();
            break;
        case 0xDF: // JMM (Jump to address in M)
            PC = (Registers[L] << 8) | Registers[H];
            break;
        case 0xE0: // JZM (Jump to address in M if Z flag is set)
            if (Flags.Z)
                PC = (Registers[L] << 8) | Registers[H];
            else
                PC += 2;
            break;
        case 0xE1: // JNZM (Jump to address in M if Z flag is not set)
            if (!Flags.Z)
                PC = (Registers[L] << 8) | Registers[H];
            else
                PC += 2;
            break;
        case 0xE2: // JCM (Jump to address in M if C flag is set)
            if (Flags.C)
                PC = (Registers[L] << 8) | Registers[H];
            else
                PC += 2;
            break;
        case 0xE3: // JNCM (Jump to address in M if C flag is not set)
            if (!Flags.C)
                PC = (Registers[L] << 8) | Registers[H];
            else
                PC += 2;
            break;
        case 0xE4: // CALM (Call to address in M)
            PushCallStack(PC + 2);
            PC = (Registers[L] << 8) | Registers[H];
            break;
        case 0xE5: // AND A, B
            Registers[A] &= Registers[B];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xE6: // AND A, C
            Registers[A] &= Registers[C];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xE7: // AND A, D
            Registers[A] &= Registers[D];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xE8: // AND A, E
            Registers[A] &= Registers[E];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xE9: // AND A, L
            Registers[A] &= Registers[L];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xEA: // AND A, H
            Registers[A] &= Registers[H];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xEB: // OR A, B
            Registers[A] |= Registers[B];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xEC: // OR A, C
            Registers[A] |= Registers[C];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xED: // OR A, D
            Registers[A] |= Registers[D];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xEE: // OR A, E
            Registers[A] |= Registers[E];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xEF: // OR A, L
            Registers[A] |= Registers[L];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xF0: // OR A, H
            Registers[A] |= Registers[H];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xF1: // XOR A, B
            Registers[A] ^= Registers[B];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xF2: // XOR A, C
            Registers[A] ^= Registers[C];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xF3: // XOR A, D
            Registers[A] ^= Registers[D];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xF4: // XOR A, E
            Registers[A] ^= Registers[E];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xF5: // XOR A, L
            Registers[A] ^= Registers[L];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xF6: // XOR A, H
            Registers[A] ^= Registers[H];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xF7: // NOT A
            Registers[A] = ~Registers[A];
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xF8: // NOP
            break;
        case 0xF9: // SHL A
            Registers[A] <<= 1;
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xFA: // SHR A
            Registers[A] >>= 1;
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xFB: // ROL A
            Registers[A] = (Registers[A] << 1) | (Registers[A] >> 7);
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xFC: // ROR A
            Registers[A] = (Registers[A] >> 1) | (Registers[A] << 7);
            if (Registers[A] == 0)
                SetFlag(ZERO);
            else
                ClearFlag(ZERO);
            if (Registers[A] & 0x80)
                SetFlag(SIGN);
            else
                ClearFlag(SIGN);
            break;
        case 0xFD: // IN 0
            HandleIn();
            break;
        case 0xFE: // OUT 0
            HandleOut();
            break;
        case 0xFF: // EXTENDED INSTRUCTION
            execute_extended();
            break;

        
        default:
            printf("Invalid Opcode\n");
            exit(INVALID_OPCODE);
    }
}

uint8_t* LoadFromDisk(char* path, size_t* size)
{
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        printf("Error opening file: %s\n", path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);
    uint8_t* buffer = (uint8_t*)malloc(*size);
    if (!buffer)
    {
        printf("Error allocating memory\n");
        fclose(file);
        return NULL;
    }
    fread(buffer, 1, *size, file);
    fclose(file);
    return buffer;
}

int main()
{
    // Initialize registers and memory
    emu_init();

    size_t opcodes_size = 0;

    uint8_t* opcodes = LoadFromDisk("out.bin", &opcodes_size);

    LoadProgram(opcodes, opcodes_size);

    while (1)
    {
        printf("\033[H\033[J");
        DumpRegisters();
        execute_instruction();
        getchar();
    }

    return 0;
}