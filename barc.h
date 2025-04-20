#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CALL_STACK_SIZE 8

#define INPUT_FUNCTION 0
#define OUTPUT_FUNCTION 1

//function ptr for in: uint8_t name()
typedef uint8_t (*INFunction)(void);

typedef void (*OUTFunction)(uint8_t);

OUTFunction OFunc = NULL; // Function pointer for OUT function
INFunction IFunc = NULL; // Function pointer for IN function

typedef enum {
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4,
    L = 5,
    H = 6
} RegisterIndex;

typedef struct
{
    uint8_t Z : 1; // Zero flag
    uint8_t C : 1; // Carry flag
    uint8_t S : 1; // Sign flag
    uint8_t P : 1; // Parity flag
    uint8_t unused : 4; // Unused bits
} FFlags;

typedef enum
{
    ZERO = 0,
    CARRY = 1,
    SIGN = 2,
    PARITY = 3
} EFlags;

typedef enum
{
    NO_ERROR = 0,
    STACK_OVERFLOW = 1,
    STACK_UNDERFLOW = 2,
    INVALID_OPCODE = 3,
    DIVIDE_BY_ZERO = 4,
    MEMORY_ACCESS_VIOLATION = 5,
    INVALID_INSTRUCTION = 6,
    UNEXPECTED_END_OF_PROGRAM = 7
} ERRORTYPE;

uint8_t MemorySpace[0xFFFF]; // 64KB of memory

uint16_t CallStack[MAX_CALL_STACK_SIZE]; // Call stack for function calls

uint16_t PC = 0; // Program Counter
uint8_t SP = 0; // Stack Pointer

uint8_t Registers[7]; // General purpose registers
FFlags Flags = {0}; // Flags register

void LoadProgram(uint8_t* program, size_t size)
{
    if (size > sizeof(MemorySpace))
    {
        printf("Program size exceeds memory space\n");
        exit(MEMORY_ACCESS_VIOLATION);
    }
    for (size_t i = 0; i < size; i++)
    {
        MemorySpace[i] = program[i];
    }
}

void DumpRegisters()
{
    printf("Registers:\n");
    printf("A: %02X\n", Registers[A]);
    printf("B: %02X\n", Registers[B]);
    printf("C: %02X\n", Registers[C]);
    printf("D: %02X\n", Registers[D]);
    printf("E: %02X\n", Registers[E]);
    printf("L: %02X\n", Registers[L]);
    printf("H: %02X\n", Registers[H]);
    printf("Flags: Z=%d C=%d S=%d P=%d\n", Flags.Z, Flags.C, Flags.S, Flags.P);
    printf("PC: %04X\n", PC);
    printf("SP: %02X\n", SP);
    printf("Call Stack:\n");
    for (int i = 0; i < SP; i++)
    {
        printf("%04X ", CallStack[i]);
    }
    printf("\n");
}

uint8_t PeekByte()
{
    if (PC < 0xFFFF)
    {
        return MemorySpace[PC];
    }
    else
    {
        printf("Memory Access Violation\n");
        DumpRegisters();
        exit(MEMORY_ACCESS_VIOLATION);
    }
}

uint8_t FetchByte()
{
    if (PC < 0xFFFF)
    {
        return MemorySpace[PC++];
    }
    else
    {
        printf("Memory Access Violation\n");
        DumpRegisters();
        exit(MEMORY_ACCESS_VIOLATION);
    }
}

uint16_t FetchWord()
{
    if (PC < 0xFFFF - 1)
    {
        uint16_t word = MemorySpace[PC] | (MemorySpace[PC + 1] << 8);
        PC += 2;
        return word;
    }
    else
    {
        printf("Memory Access Violation\n");
        DumpRegisters();
        exit(MEMORY_ACCESS_VIOLATION);
    }
}



void PopCallStack()
{
    if (SP > 0)
    {
        SP--;
        PC = CallStack[SP];
    }
    else
    {
        printf("Stack Underflow\n");
        DumpRegisters();
        exit(STACK_UNDERFLOW);
    }
}

void PushCallStack(uint16_t value)
{
    if (SP < MAX_CALL_STACK_SIZE)
    {
        CallStack[SP++] = value;
    }

    else 
    {
        printf("Stack Overflow\n");
        DumpRegisters();
        exit(STACK_OVERFLOW);
    }
}

void SetFlag(EFlags flag)
{
    switch (flag)
    {
        case ZERO:
            Flags.Z = 1;
            break;
        case CARRY:
            Flags.C = 1;
            break;
        case SIGN:
            Flags.S = 1;
            break;
        case PARITY:
            Flags.P = 1;
            break;
        default:
            printf("Invalid flag\n");
            exit(INVALID_INSTRUCTION);
    }
}

void ClearFlag(EFlags flag)
{
    switch (flag)
    {
        case ZERO:
            Flags.Z = 0;
            break;
        case CARRY:
            Flags.C = 0;
            break;
        case SIGN:
            Flags.S = 0;
            break;
        case PARITY:
            Flags.P = 0;
            break;
        default:
            printf("Invalid flag\n");
            exit(INVALID_INSTRUCTION);
    }
}

void HandleOut()
{
    uint8_t value = Registers[A];

    // Call the OUT function with the value
    OFunc(value);
}

void HandleIn()
{
    // Call the IN function and store the result in register A
    Registers[A] = IFunc();
    if (Registers[A] == 0)
        SetFlag(ZERO);
    else
        ClearFlag(ZERO);
    if (Registers[A] & 0x80)
        SetFlag(SIGN);
    else
        ClearFlag(SIGN);
}

void SetINOutFunction(void* func, unsigned char isInput)
{
    if (isInput)
    {
        IFunc = (INFunction)func;
    }
    else
    {
        OFunc = (OUTFunction)func;
    }
}