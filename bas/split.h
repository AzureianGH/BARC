#pragma once

#include <stdint.h>

char** split(const char* str, const char* delim, size_t* count);

char** splitAnyNewline(const char* str, size_t* count);

void freeSplit(char** arr, size_t count);