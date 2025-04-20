#include "split.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split(const char* str, const char* delim, size_t* count) {
    char* temp = strdup(str);
    char* token = strtok(temp, delim);
    char** result = NULL;
    size_t size = 0;

    while (token != NULL) {
        result = (char**)realloc(result, sizeof(char*) * (size + 1));
        result[size] = strdup(token);
        size++;
        token = strtok(NULL, delim);
    }

    free(temp);
    *count = size;
    return result;
}

void freeSplit(char** arr, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}

char** splitAnyNewline(const char* str, size_t* count) {
    //\n OR on windows \r\n
    char* temp = strdup(str);
    char* token = strtok(temp, "\n\r");
    char** result = NULL;
    size_t size = 0;

    while (token != NULL) {
        result = (char**)realloc(result, sizeof(char*) * (size + 1));
        result[size] = strdup(token);
        size++;
        token = strtok(NULL, "\n\r");
    }

    free(temp);
    *count = size;
    return result;
}