#include "dict.h"
#include "split.h"
#include "push.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

dictionary_t singleInstruction;
dictionary_t multiInstruction;

void loadKeys()
{
    createDictionary(&singleInstruction);

    setDictionary(&singleInstruction, "HLT", 0x00);
    setDictionary(&singleInstruction, "MOV A, B", 0x01);
    setDictionary(&singleInstruction, "MOV A, C", 0x02);
    setDictionary(&singleInstruction, "MOV A, D", 0x03);
    setDictionary(&singleInstruction, "MOV A, E", 0x04);
    setDictionary(&singleInstruction, "MOV A, L", 0x05);
    setDictionary(&singleInstruction, "MOV A, H", 0x06);
    setDictionary(&singleInstruction, "MOV B, A", 0x07);
    setDictionary(&singleInstruction, "MOV B, C", 0x08);
    setDictionary(&singleInstruction, "MOV B, D", 0x09);
    setDictionary(&singleInstruction, "MOV B, E", 0x0A);
    setDictionary(&singleInstruction, "MOV B, L", 0x0B);
    setDictionary(&singleInstruction, "MOV B, H", 0x0C);
    setDictionary(&singleInstruction, "MOV C, A", 0x0D);
    setDictionary(&singleInstruction, "MOV C, B", 0x0E);
    setDictionary(&singleInstruction, "MOV C, D", 0x0F);
    setDictionary(&singleInstruction, "MOV C, E", 0x10);
    setDictionary(&singleInstruction, "MOV C, L", 0x11);
    setDictionary(&singleInstruction, "MOV C, H", 0x12);
    setDictionary(&singleInstruction, "MOV D, A", 0x13);
    setDictionary(&singleInstruction, "MOV D, B", 0x14);
    setDictionary(&singleInstruction, "MOV D, C", 0x15);
    setDictionary(&singleInstruction, "MOV D, E", 0x16);
    setDictionary(&singleInstruction, "MOV D, L", 0x17);
    setDictionary(&singleInstruction, "MOV D, H", 0x18);
    setDictionary(&singleInstruction, "MOV E, A", 0x19);
    setDictionary(&singleInstruction, "MOV E, B", 0x1A);
    setDictionary(&singleInstruction, "MOV E, C", 0x1B);
    setDictionary(&singleInstruction, "MOV E, D", 0x1C);
    setDictionary(&singleInstruction, "MOV E, L", 0x1D);
    setDictionary(&singleInstruction, "MOV E, H", 0x1E);
    setDictionary(&singleInstruction, "MOV L, A", 0x1F);
    setDictionary(&singleInstruction, "MOV L, B", 0x20);
    setDictionary(&singleInstruction, "MOV L, C", 0x21);
    setDictionary(&singleInstruction, "MOV L, D", 0x22);
    setDictionary(&singleInstruction, "MOV L, E", 0x23);
    setDictionary(&singleInstruction, "MOV L, H", 0x24);
    setDictionary(&singleInstruction, "MOV H, A", 0x25);
    setDictionary(&singleInstruction, "MOV H, B", 0x26);
    setDictionary(&singleInstruction, "MOV H, C", 0x27);
    setDictionary(&singleInstruction, "MOV H, D", 0x28);
    setDictionary(&singleInstruction, "MOV H, E", 0x29);
    setDictionary(&singleInstruction, "MOV H, L", 0x2A);
    setDictionary(&singleInstruction, "LUMA", 0x34);
    setDictionary(&singleInstruction, "SUMA", 0x35);
    setDictionary(&singleInstruction, "ADD A, B", 0x36);
    setDictionary(&singleInstruction, "ADD A, C", 0x37);
    setDictionary(&singleInstruction, "ADD A, D", 0x38);
    setDictionary(&singleInstruction, "ADD A, E", 0x39);
    setDictionary(&singleInstruction, "ADD A, L", 0x3A);
    setDictionary(&singleInstruction, "ADD A, H", 0x3B);
    setDictionary(&singleInstruction, "ADD B, A", 0x3C);
    setDictionary(&singleInstruction, "ADD B, C", 0x3D);
    setDictionary(&singleInstruction, "ADD B, D", 0x3E);
    setDictionary(&singleInstruction, "ADD B, E", 0x3F);
    setDictionary(&singleInstruction, "ADD B, L", 0x40);
    setDictionary(&singleInstruction, "ADD B, H", 0x41);
    setDictionary(&singleInstruction, "ADD C, A", 0x42);
    setDictionary(&singleInstruction, "ADD C, B", 0x43);
    setDictionary(&singleInstruction, "ADD C, D", 0x44);
    setDictionary(&singleInstruction, "ADD C, E", 0x45);
    setDictionary(&singleInstruction, "ADD C, L", 0x46);
    setDictionary(&singleInstruction, "ADD C, H", 0x47);
    setDictionary(&singleInstruction, "ADD D, A", 0x48);
    setDictionary(&singleInstruction, "ADD D, B", 0x49);
    setDictionary(&singleInstruction, "ADD D, C", 0x4A);
    setDictionary(&singleInstruction, "ADD D, E", 0x4B);
    setDictionary(&singleInstruction, "ADD D, L", 0x4C);
    setDictionary(&singleInstruction, "ADD D, H", 0x4D);
    setDictionary(&singleInstruction, "ADD E, A", 0x4E);
    setDictionary(&singleInstruction, "ADD E, B", 0x4F);
    setDictionary(&singleInstruction, "ADD E, C", 0x50);
    setDictionary(&singleInstruction, "ADD E, D", 0x51);
    setDictionary(&singleInstruction, "ADD E, L", 0x52);
    setDictionary(&singleInstruction, "ADD E, H", 0x53);
    setDictionary(&singleInstruction, "ADD L, A", 0x54);
    setDictionary(&singleInstruction, "ADD L, B", 0x55);
    setDictionary(&singleInstruction, "ADD L, C", 0x56);
    setDictionary(&singleInstruction, "ADD L, D", 0x57);
    setDictionary(&singleInstruction, "ADD L, E", 0x58);
    setDictionary(&singleInstruction, "ADD L, H", 0x59);
    setDictionary(&singleInstruction, "ADD H, A", 0x5A);
    setDictionary(&singleInstruction, "ADD H, B", 0x5B);
    setDictionary(&singleInstruction, "ADD H, C", 0x5C);
    setDictionary(&singleInstruction, "ADD H, D", 0x5D);
    setDictionary(&singleInstruction, "ADD H, E", 0x5E);
    setDictionary(&singleInstruction, "ADD H, L", 0x5F);
    setDictionary(&singleInstruction, "SUB A, B", 0x60);
    setDictionary(&singleInstruction, "SUB A, C", 0x61);
    setDictionary(&singleInstruction, "SUB A, D", 0x62);
    setDictionary(&singleInstruction, "SUB A, E", 0x63);
    setDictionary(&singleInstruction, "SUB A, L", 0x64);
    setDictionary(&singleInstruction, "SUB A, H", 0x65);
    setDictionary(&singleInstruction, "SUB B, A", 0x66);
    setDictionary(&singleInstruction, "SUB B, C", 0x67);
    setDictionary(&singleInstruction, "SUB B, D", 0x68);
    setDictionary(&singleInstruction, "SUB B, E", 0x69);
    setDictionary(&singleInstruction, "SUB B, L", 0x6A);
    setDictionary(&singleInstruction, "SUB B, H", 0x6B);
    setDictionary(&singleInstruction, "SUB C, A", 0x6C);
    setDictionary(&singleInstruction, "SUB C, B", 0x6D);
    setDictionary(&singleInstruction, "SUB C, D", 0x6E);
    setDictionary(&singleInstruction, "SUB C, E", 0x6F);
    setDictionary(&singleInstruction, "SUB C, L", 0x70);
    setDictionary(&singleInstruction, "SUB C, H", 0x71);
    setDictionary(&singleInstruction, "SUB D, A", 0x72);
    setDictionary(&singleInstruction, "SUB D, B", 0x73);
    setDictionary(&singleInstruction, "SUB D, C", 0x74);
    setDictionary(&singleInstruction, "SUB D, E", 0x75);
    setDictionary(&singleInstruction, "SUB D, L", 0x76);
    setDictionary(&singleInstruction, "SUB D, H", 0x77);
    setDictionary(&singleInstruction, "SUB E, A", 0x78);
    setDictionary(&singleInstruction, "SUB E, B", 0x79);
    setDictionary(&singleInstruction, "SUB E, C", 0x7A);
    setDictionary(&singleInstruction, "SUB E, D", 0x7B);
    setDictionary(&singleInstruction, "SUB E, L", 0x7C);
    setDictionary(&singleInstruction, "SUB E, H", 0x7D);
    setDictionary(&singleInstruction, "SUB L, A", 0x7E);
    setDictionary(&singleInstruction, "SUB L, B", 0x7F);
    setDictionary(&singleInstruction, "SUB L, C", 0x80);
    setDictionary(&singleInstruction, "SUB L, D", 0x81);
    setDictionary(&singleInstruction, "SUB L, E", 0x82);
    setDictionary(&singleInstruction, "SUB L, H", 0x83);
    setDictionary(&singleInstruction, "SUB H, A", 0x84);
    setDictionary(&singleInstruction, "SUB H, B", 0x85);
    setDictionary(&singleInstruction, "SUB H, C", 0x86);
    setDictionary(&singleInstruction, "SUB H, D", 0x87);
    setDictionary(&singleInstruction, "SUB H, E", 0x88);
    setDictionary(&singleInstruction, "SUB H, L", 0x89);
    setDictionary(&singleInstruction, "INC A", 0x98);
    setDictionary(&singleInstruction, "INC B", 0x99);
    setDictionary(&singleInstruction, "INC C", 0x9A);
    setDictionary(&singleInstruction, "INC D", 0x9B);
    setDictionary(&singleInstruction, "INC E", 0x9C);
    setDictionary(&singleInstruction, "INC L", 0x9D);
    setDictionary(&singleInstruction, "INC H", 0x9E);
    setDictionary(&singleInstruction, "DEC A", 0x9F);
    setDictionary(&singleInstruction, "DEC B", 0xA0);
    setDictionary(&singleInstruction, "DEC C", 0xA1);
    setDictionary(&singleInstruction, "DEC D", 0xA2);
    setDictionary(&singleInstruction, "DEC E", 0xA3);
    setDictionary(&singleInstruction, "DEC L", 0xA4);
    setDictionary(&singleInstruction, "DEC H", 0xA5);
    setDictionary(&singleInstruction, "CMP A, B", 0xA6);
    setDictionary(&singleInstruction, "CMP A, C", 0xA7);
    setDictionary(&singleInstruction, "CMP A, D", 0xA8);
    setDictionary(&singleInstruction, "CMP A, E", 0xA9);
    setDictionary(&singleInstruction, "CMP A, L", 0xAA);
    setDictionary(&singleInstruction, "CMP A, H", 0xAB);
    setDictionary(&singleInstruction, "CMP B, A", 0xAC);
    setDictionary(&singleInstruction, "CMP B, C", 0xAD);
    setDictionary(&singleInstruction, "CMP B, D", 0xAE);
    setDictionary(&singleInstruction, "CMP B, E", 0xAF);
    setDictionary(&singleInstruction, "CMP B, L", 0xB0);
    setDictionary(&singleInstruction, "CMP B, H", 0xB1);
    setDictionary(&singleInstruction, "CMP C, A", 0xB2);
    setDictionary(&singleInstruction, "CMP C, B", 0xB3);
    setDictionary(&singleInstruction, "CMP C, D", 0xB4);
    setDictionary(&singleInstruction, "CMP C, E", 0xB5);
    setDictionary(&singleInstruction, "CMP C, L", 0xB6);
    setDictionary(&singleInstruction, "CMP C, H", 0xB7);
    setDictionary(&singleInstruction, "CMP D, A", 0xB8);
    setDictionary(&singleInstruction, "CMP D, B", 0xB9);
    setDictionary(&singleInstruction, "CMP D, C", 0xBA);
    setDictionary(&singleInstruction, "CMP D, E", 0xBB);
    setDictionary(&singleInstruction, "CMP D, L", 0xBC);
    setDictionary(&singleInstruction, "CMP D, H", 0xBD);
    setDictionary(&singleInstruction, "CMP E, A", 0xBE);
    setDictionary(&singleInstruction, "CMP E, B", 0xBF);
    setDictionary(&singleInstruction, "CMP E, C", 0xC0);
    setDictionary(&singleInstruction, "CMP E, D", 0xC1);
    setDictionary(&singleInstruction, "CMP E, L", 0xC2);
    setDictionary(&singleInstruction, "CMP E, H", 0xC3);
    setDictionary(&singleInstruction, "CMP L, A", 0xC4);
    setDictionary(&singleInstruction, "CMP L, B", 0xC5);
    setDictionary(&singleInstruction, "CMP L, C", 0xC6);
    setDictionary(&singleInstruction, "CMP L, D", 0xC7);
    setDictionary(&singleInstruction, "CMP L, E", 0xC8);
    setDictionary(&singleInstruction, "CMP L, H", 0xC9);
    setDictionary(&singleInstruction, "CMP H, A", 0xCA);
    setDictionary(&singleInstruction, "CMP H, B", 0xCB);
    setDictionary(&singleInstruction, "CMP H, C", 0xCC);
    setDictionary(&singleInstruction, "CMP H, D", 0xCD);
    setDictionary(&singleInstruction, "CMP H, E", 0xCE);
    setDictionary(&singleInstruction, "CMP H, L", 0xCF);
    setDictionary(&singleInstruction, "RET", 0xDE);
    setDictionary(&singleInstruction, "JMM", 0xDF);
    setDictionary(&singleInstruction, "JZM", 0xE0);
    setDictionary(&singleInstruction, "JNZM", 0xE1);
    setDictionary(&singleInstruction, "JCM", 0xE2);
    setDictionary(&singleInstruction, "JNCM", 0xE3);
    setDictionary(&singleInstruction, "CALM", 0xE4);
    setDictionary(&singleInstruction, "AND A, B", 0xE5);
    setDictionary(&singleInstruction, "AND A, C", 0xE6);
    setDictionary(&singleInstruction, "AND A, D", 0xE7);
    setDictionary(&singleInstruction, "AND A, E", 0xE8);
    setDictionary(&singleInstruction, "AND A, L", 0xE9);
    setDictionary(&singleInstruction, "AND A, H", 0xEA);
    setDictionary(&singleInstruction, "OR A, B", 0xEB);
    setDictionary(&singleInstruction, "OR A, C", 0xEC);
    setDictionary(&singleInstruction, "OR A, D", 0xED);
    setDictionary(&singleInstruction, "OR A, E", 0xEE);
    setDictionary(&singleInstruction, "OR A, L", 0xEF);
    setDictionary(&singleInstruction, "OR A, H", 0xF0);
    setDictionary(&singleInstruction, "XOR A, B", 0xF1);
    setDictionary(&singleInstruction, "XOR A, C", 0xF2);
    setDictionary(&singleInstruction, "XOR A, D", 0xF3);
    setDictionary(&singleInstruction, "XOR A, E", 0xF4);
    setDictionary(&singleInstruction, "XOR A, L", 0xF5);
    setDictionary(&singleInstruction, "XOR A, H", 0xF6);
    setDictionary(&singleInstruction, "NOT A", 0xF7);
    setDictionary(&singleInstruction, "NOP", 0xF8);
    setDictionary(&singleInstruction, "SHL A", 0xF9);
    setDictionary(&singleInstruction, "SHR A", 0xFA);
    setDictionary(&singleInstruction, "ROL A", 0xFB);
    setDictionary(&singleInstruction, "ROR A", 0xFC);
    setDictionary(&singleInstruction, "IN", 0xFD);
    setDictionary(&singleInstruction, "OUT", 0xFE);

    createDictionary(&multiInstruction);

    setDictionary(&multiInstruction, "LAA", 0x2B);
    setDictionary(&multiInstruction, "SAA", 0x2C);
    setDictionary(&multiInstruction, "MVI", 0x2D); // STARTS AT 0x2D and GOES TO 0x33
    setDictionary(&multiInstruction, "ADI", 0x8A); // STARTS AT 0x8A and GOES TO 0x90
    setDictionary(&multiInstruction, "SBI", 0x91); // STARTS AT 0x91 and GOES TO 0x97
    setDictionary(&multiInstruction, "CPI", 0xD0); // STARTS AT 0xD0 and GOES TO 0xD6
    setDictionary(&multiInstruction, "JMP", 0xD7);
    setDictionary(&multiInstruction, "JZ", 0xD8);
    setDictionary(&multiInstruction, "JNZ", 0xD9);
    setDictionary(&multiInstruction, "JC", 0xDA);
    setDictionary(&multiInstruction, "JNC", 0xDB);
    setDictionary(&multiInstruction, "JZC", 0xDC);
    setDictionary(&multiInstruction, "CALL", 0xDD);
    setDictionary(&multiInstruction, "DB", 0x00); // assembler directive for defining bytes
    setDictionary(&multiInstruction, "DW", 0x00); // assembler directive for defining words

    printf("Loaded %zu keys\n", getDictionarySize(&singleInstruction) + getDictionarySize(&multiInstruction));
}

void destroyKeys()
{
    destroyDictionary(&singleInstruction);
    destroyDictionary(&multiInstruction);
    printf("Destroyed keys\n");
}

uint8_t strToU8(char* str)
{
    // The string could be in decimal, hex or binary format, negative, or octal
    // Check if the string starts with 0x or 0b or 0o or -
    if (str[0] == '0' && str[1] == 'x') // Hexadecimal
    {
        return (uint8_t)strtol(str + 2, NULL, 16);
    }
    else if (str[0] == '0' && str[1] == 'b') // Binary
    {
        return (uint8_t)strtol(str + 2, NULL, 2);
    }
    else if (str[0] == '0' && str[1] == 'o') // Octal
    {
        return (uint8_t)strtol(str + 2, NULL, 8);
    }
    else if (str[0] == '-') // Negative number
    {
        return (uint8_t)-atoi(str + 1);
    }
    else if (str[0] == '\'')
    {
        return (uint8_t)str[1];
    }
    else // Decimal
    {
        return (uint8_t)atoi(str);
    }
}

uint16_t strToNum(char* str)
{
    // The string could be in decimal, hex or binary format, negative, or octal
    // Check if the string starts with 0x or 0b or 0o or -
    if (str[0] == '0' && str[1] == 'x') // Hexadecimal
    {
        return (uint16_t)strtol(str + 2, NULL, 16);
    }
    else if (str[0] == '0' && str[1] == 'b') // Binary
    {
        return (uint16_t)strtol(str + 2, NULL, 2);
    }
    else if (str[0] == '0' && str[1] == 'o') // Octal
    {
        return (uint16_t)strtol(str + 2, NULL, 8);
    }
    else if (str[0] == '-') // Negative number
    {
        return (uint16_t)-atoi(str + 1);
    }
    else if (str[0] == '\'')
    {
        return (uint8_t)str[1];
    }
    else // Decimal
    {
        return (uint16_t)atoi(str);
    }
}

uint8_t isNumber(char* str)
{
    // Check if the string is a valid number in decimal, hexadecimal, binary, or octal format
    if (str[0] == '0' && str[1] == 'x') // Hexadecimal
    {
        for (size_t i = 2; i < strlen(str); i++)
        {
            if (!isxdigit(str[i]))
            {
                return 0; // Not a valid hexadecimal number
            }
        }
        return 1; // Valid hexadecimal number
    }
    else if (str[0] == '0' && str[1] == 'b') // Binary
    {
        for (size_t i = 2; i < strlen(str); i++)
        {
            if (str[i] != '0' && str[i] != '1')
            {
                return 0; // Not a valid binary number
            }
        }
        return 1; // Valid binary number
    }
    else if (str[0] == '0' && str[1] == 'o') // Octal
    {
        for (size_t i = 2; i < strlen(str); i++)
        {
            if (str[i] < '0' || str[i] > '7')
            {
                return 0; // Not a valid octal number
            }
        }
        return 1; // Valid octal number
    }
    else if (str[0] == '-' || isdigit(str[0])) // Decimal or negative number
    {
        for (size_t i = (str[0] == '-' ? 1 : 0); i < strlen(str); i++)
        {
            if (!isdigit(str[i]))
            {
                return 0; // Not a valid decimal number
            }
        }
        return 1; // Valid decimal number
    }
    //if it starts with ' and ends with ' get the char in the center and convert via ascii
    else if (str[0] == '\'')
    {
        if (str[2] != '\'')
        {
            return 0; // Not a char
        }
        else
        {
            return 1; // valid char
        }
    }
    return 0; // Not a number
}

uint8_t getRegisterOffset(char reg)
{
    switch (reg)
    {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        case 'L':
            return 5;
        case 'H':
            return 6;
        default:
            return -1; // Invalid register
    }
}

char* trimWhitespace(char* str)
{
    char* end;
    while (isspace((unsigned char)*str)) str++; // Trim leading whitespace
    if (*str == 0) return str; // All spaces
    end = str + strlen(str) - 1; // Trim trailing whitespace
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0'; // Null terminate the string
    return str;
}
char** savedLabels = NULL;
uint16_t* savedLabelsAddr = NULL;
size_t savedLabelsCount = 0;
typedef struct {
    char* label;
    size_t position;
    uint8_t isWord; // Flag to indicate if the unresolved label should be treated as a word
} UnresolvedLabel;

UnresolvedLabel* unresolvedLabels = NULL;
size_t unresolvedLabelsCount = 0;

int16_t getLabelAddress(char* label)
{
    for (size_t i = 0; i < savedLabelsCount; i++)
    {
        if (strcmp(savedLabels[i], label) == 0)
        {
            return savedLabelsAddr[i];
        }
    }
    return -1; // Not found
}

void resolveUnresolvedLabels()
{
    for (size_t i = 0; i < unresolvedLabelsCount; i++)
    {
        int16_t labelAddr = getLabelAddress(unresolvedLabels[i].label);
        if (labelAddr == -1)
        {
            printf("Unresolved label: %s\n", unresolvedLabels[i].label);
            exit(1); // Still unresolved
        }
        if (unresolvedLabels[i].isWord)
        {
            setBytestackWord(unresolvedLabels[i].position, (uint16_t)labelAddr);
        }
        else
        {
            setBytestackByte(unresolvedLabels[i].position, (uint8_t)(labelAddr & 0xFF));
        }
        printf("\033[0;32mResolved label: %s to address %04X\033[0m\n", unresolvedLabels[i].label, labelAddr);
        free(unresolvedLabels[i].label);
    }
    free(unresolvedLabels);
    unresolvedLabels = NULL;
    unresolvedLabelsCount = 0;
}

void addUnresolvedLabel(char* label, size_t position, uint8_t isWord)
{
    printf("\033[0;31mOrphaned label: %s at position %zu\033[0m\n", label, position);
    unresolvedLabels = realloc(unresolvedLabels, sizeof(UnresolvedLabel) * (unresolvedLabelsCount + 1));
    if (unresolvedLabels == NULL)
    {
        printf("Memory allocation failed for unresolved labels\n");
        exit(1);
    }
    unresolvedLabels[unresolvedLabelsCount].label = strdup(label);
    if (unresolvedLabels[unresolvedLabelsCount].label == NULL)
    {
        printf("Memory allocation failed for label string\n");
        exit(1);
    }
    unresolvedLabels[unresolvedLabelsCount].position = position;
    unresolvedLabels[unresolvedLabelsCount].isWord = isWord;
    unresolvedLabelsCount++;
}

void getOpcode(char* possibleKey)
{
    if (strlen(trimWhitespace(possibleKey)) == 0)
    {
        return; // Skip empty lines
    }

    uint8_t* opcode = getDictionary(&singleInstruction, possibleKey);
    if (opcode != NULL)
    {
        pushByte(*opcode);
        return;
    }

    size_t splitcount = 0;
    char** splitWords = split(possibleKey, " ", &splitcount);

    if (!strcmp(splitWords[0], ";"))
    {
        freeSplit(splitWords, splitcount);
        return;
    }

    if (splitWords[0][strlen(splitWords[0]) - 1] == ':') // Label
    {
        savedLabels = realloc(savedLabels, sizeof(char*) * (savedLabelsCount + 1));
        savedLabelsAddr = realloc(savedLabelsAddr, sizeof(uint16_t) * (savedLabelsCount + 1));

        if (savedLabels == NULL || savedLabelsAddr == NULL)
        {
            printf("Memory allocation failed for labels\n");
            exit(1);
        }

        size_t labelLen = strlen(splitWords[0]) - 1;
        savedLabels[savedLabelsCount] = malloc(labelLen + 1);
        if (savedLabels[savedLabelsCount] == NULL)
        {
            printf("Memory allocation failed for label string\n");
            exit(1);
        }
        strncpy(savedLabels[savedLabelsCount], splitWords[0], labelLen);
        savedLabels[savedLabelsCount][labelLen] = '\0';

        savedLabelsAddr[savedLabelsCount] = (uint16_t)getBytestackSize();
        savedLabelsCount++;

        freeSplit(splitWords, splitcount);
        return;
    }

    opcode = getDictionary(&multiInstruction, splitWords[0]);
    if (opcode != NULL)
    {
        if (!strcmp(splitWords[0], "JMP") || !strcmp(splitWords[0], "JZ") || !strcmp(splitWords[0], "JNZ") ||
            !strcmp(splitWords[0], "JC") || !strcmp(splitWords[0], "JNC") || !strcmp(splitWords[0], "JZC") || 
            !strcmp(splitWords[0], "CALL") || !strcmp(splitWords[0], "SAA") || !strcmp(splitWords[0], "LAA"))
        {
            uint16_t nextnum;
            if (isNumber(splitWords[1]))
            {
                nextnum = strToNum(splitWords[1]);
            }
            else
            {
                int16_t labelAddr = getLabelAddress(splitWords[1]);
                if (labelAddr == -1)
                {
                    addUnresolvedLabel(splitWords[1], getBytestackSize() + 1, 1);
                    nextnum = 0; // Placeholder
                }
                else
                {
                    nextnum = (uint16_t)labelAddr;
                }
            }
            pushByte(*opcode);
            pushWord(nextnum);
        }
        else if (!strcmp(splitWords[0], "MVI") || !strcmp(splitWords[0], "ADI") || 
             !strcmp(splitWords[0], "SBI") || !strcmp(splitWords[0], "CPI"))
        {
            char reg = splitWords[1][0];
            uint8_t regOffset = getRegisterOffset(reg);
            if (regOffset == (uint8_t)-1)
            {
                freeSplit(splitWords, splitcount);
                printf("Invalid register: %s\n", splitWords[1]);
                exit(1);
            }

            uint8_t nextnum;
            if (isNumber(splitWords[2]))
            {
                nextnum = strToU8(splitWords[2]);
            }
            else
            {
                int16_t labelAddr = getLabelAddress(splitWords[2]);
                if (labelAddr == -1)
                {
                    addUnresolvedLabel(splitWords[2], getBytestackSize() + 1, 0);
                    nextnum = 0; // Placeholder
                }
                else
                {
                    nextnum = (uint8_t)(labelAddr & 0xFF); // Truncate to 8 bits
                }
            }

            pushByte(*opcode + regOffset);
            pushByte(nextnum);
        }
        else if (!strcmp(splitWords[0], "DB"))
        {
            for (size_t i = 1; i < splitcount; i++)
            {
                if (splitWords[i][0] == '\"')
                {
                    int insideString = 1;
                    size_t j = 1;
                    while (insideString && i < splitcount)
                    {
                        while (splitWords[i][j] != '\0')
                        {
                            if (splitWords[i][j] == '\"')
                            {
                                insideString = 0;
                                break;
                            }
                            pushByte((uint8_t)splitWords[i][j]);
                            j++;
                        }
                        if (insideString)
                        {
                            i++;
                            pushByte(' ');
                            j = 0;
                            if (i >= splitcount) break;
                        }
                    }
                }
                else
                {
                    uint8_t nextnum = strToU8(splitWords[i]);
                    pushByte(nextnum);
                }

                if (splitWords[i][strlen(splitWords[i]) - 1] != ',')
                {
                    break;
                }
            }
        }

        else if (!strcmp(splitWords[0], "DW"))
        {
            for (size_t i = 1; i < splitcount; i++)
            {
                uint16_t nextnum = strToNum(splitWords[i]);
                pushWord(nextnum);
                if (splitWords[i][strlen(splitWords[i]) - 1] != ',')
                {
                    break;
                }
            }
        }
        else
        {
            freeSplit(splitWords, splitcount);
            printf("Invalid instruction: %s\n", possibleKey);
            exit(1);
        }
    }
    else
    {
        printf("Invalid instruction: %s\n", possibleKey);
        freeSplit(splitWords, splitcount);
        exit(1);
    }

    freeSplit(splitWords, splitcount);
}


uint8_t* assemble(char* source, size_t* size)
{
    // Load the keys and create the bytestack
    loadKeys();
    createBytestack();

    size_t count = 0;

    // Split the source code into lines
    char** lines = splitAnyNewline(source, &count);

    // Get the pointer to the bytestack (For later, we will use it to do a final runthrough of the assembled code)
    uint8_t* pstack = getBytestack();
    

    // Loop through each line and get the opcode
    for (size_t i = 0; i < count; i++)
    {
        // Get the opcode for the line
        getOpcode(trimWhitespace(lines[i]));
    }
    // Free the lines
    freeSplit(lines, count); // Free the split lines
    
    // Resolve any unresolved labels now that we've seen all labels
    resolveUnresolvedLabels();

    size_t pstackSize = getBytestackSize();
    uint8_t* assembledCode = malloc(pstackSize); // Allocate memory for the assembled code
    if (assembledCode == NULL) // Check if the memory allocation was successful
    {
        printf("Memory allocation failed\n");
        exit(1); // Exit the program
    }
    memcpy(assembledCode, pstack, pstackSize); // Copy the bytestack to the assembled code

    *size = pstackSize; // Set the size of the assembled code

    destroyBytestack();
    destroyKeys();

    return assembledCode; // Return the assembled code
}

//args
int main(int argc, char* argv[])
{
    
    if (argc < 4) // Check if the source code is provided as an argument
    {
        printf("Usage: %s <outfile> <infile> (/B OR /T)\n", argv[0]); // Print usage message
        printf("outfile: The name of the output file\n"); // Print the output file name
        printf("infile: The name of the input file\n"); // Print the input file name
        printf("/B: Binary output\n"); // Print the binary output option
        printf("/T: Text output\n"); // Print the text output option
        return 1; // Exit the program with an error code
    }

    uint8_t binary = 0; // Initialize the binary flag to 0
    if (strcmp(argv[3], "/B") == 0) // Check if the binary flag is set
    {
        binary = 1; // Set the binary flag to 1
    }
    else if (strcmp(argv[3], "/T") == 0) // Check if the text flag is set
    {
        binary = 0; // Set the binary flag to 0
    }
    else // Invalid argument
    {
        printf("Invalid argument: %s\n", argv[3]); // Print the invalid argument
        return 1; // Exit the program with an error code
    }

    FILE* infile = fopen(argv[2], "r"); // Open the input file for reading
    
    //read bytes into char* source
    fseek(infile, 0, SEEK_END); // Move the file pointer to the end of the file
    long fileSize = ftell(infile); // Get the size of the file
    fseek(infile, 0, SEEK_SET); // Move the file pointer back to the beginning of the file

    char* source = malloc(fileSize + 1); // Allocate memory for the source code
    if (source == NULL) // Check if the memory allocation was successful
    {
        printf("Memory allocation failed\n");
        fclose(infile); // Close the input file
        return 1; // Exit the program with an error code
    }

    //copy the file contents into source
    fread(source, 1, fileSize, infile); // Read the file contents into the source code
    
    size_t size = 0;

    uint8_t* assembledCode = assemble((char*)source, &size); // Assemble the source code

    printf("Assembled code size: %zu\n", size);

    //if binary, write raw, if text, write 0x
    if (binary) // Check if the binary flag is set
    {
        FILE* outfile = fopen(argv[1], "wb"); // Open the output file for writing in binary mode
        if (outfile == NULL) // Check if the file was opened successfully
        {
            printf("Error opening output file: %s\n", argv[1]); // Print the error message
            free(source); // Free the source code memory
            free(assembledCode); // Free the assembled code memory
            fclose(infile); // Close the input file
            return 1; // Exit the program with an error code
        }
        fwrite(assembledCode, 1, size, outfile); // Write the assembled code to the output file
        fclose(outfile); // Close the output file
    }
    else // Text output
    {
        FILE* outfile = fopen(argv[1], "w"); // Open the output file for writing in text mode
        if (outfile == NULL) // Check if the file was opened successfully
        {
            printf("Error opening output file: %s\n", argv[1]); // Print the error message
            free(source); // Free the source code memory
            free(assembledCode); // Free the assembled code memory
            fclose(infile); // Close the input file
            return 1; // Exit the program with an error code
        }
        for (size_t i = 0; i < size; i++) // Loop through each byte of the assembled code
        {
            fprintf(outfile, "0x%02X ", assembledCode[i]); // Write the byte to the output file in hex format
        }
        fclose(outfile); // Close the output file
    }
    free(source); // Free the source code memory
    free(assembledCode); // Free the assembled code memory

    printf("Assembled Successfully to %s\n", argv[1]); // Print success message
    return 0;
}