#pragma once

#include <stdint.h>

void createBytestack();

void pushByte(uint8_t value);
void pushWord(uint16_t value);

uint8_t popByte();
uint16_t popWord();

void destroyBytestack();

uint8_t* getBytestack();
size_t getBytestackSize();

void setBytestackWord(size_t index, uint16_t value);