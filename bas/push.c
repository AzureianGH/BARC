#include "push.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t* stack = NULL;

size_t stackSize = 0;

void createBytestack()
{
    stack = malloc(0xFFFF);
    stackSize = 0;
}
void pushByte(uint8_t value)
{
    if (stackSize < 0xFFFF)
    {
        stack[stackSize++] = value;
    }
    else
    {
        printf("Stack Overflow\n");
        exit(1);
    }
}

void pushWord(uint16_t value)
{
    if (stackSize < 0xFFFF - 1)
    {
        stack[stackSize++] = value & 0xFF;
        stack[stackSize++] = (value >> 8) & 0xFF;
    }
    else
    {
        printf("Stack Overflow\n");
        exit(1);
    }
}

uint8_t popByte()
{
    if (stackSize > 0)
    {
        return stack[--stackSize];
    }
    else
    {
        printf("Stack Underflow\n");
        exit(1);
    }
}

uint16_t popWord()
{
    if (stackSize > 1)
    {
        uint16_t value = stack[--stackSize];
        value |= (stack[--stackSize] << 8);
        return value;
    }
    else
    {
        printf("Stack Underflow\n");
        exit(1);
    }
}

void destroyBytestack()
{
    free(stack);
    stack = NULL;
    stackSize = 0;
}


uint8_t* getBytestack()
{
    return stack;
}

size_t getBytestackSize()
{
    return stackSize;
}

void setBytestackWord(size_t index, uint16_t value)
{
    if (index < stackSize - 1)
    {
        stack[index] = value & 0xFF;
        stack[index + 1] = (value >> 8) & 0xFF;
    }
    else
    {
        printf("Index out of bounds\n");
        exit(1);
    }
}