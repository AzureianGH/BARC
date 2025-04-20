#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char* key;
    uint8_t value;
} _dictionary_entry_t;

typedef struct {
    _dictionary_entry_t* entries;
    size_t size;
} dictionary_t;

void createDictionary(dictionary_t* dict);
void destroyDictionary(dictionary_t* dict);
bool keysEqual(const char* key1, const char* key2);
void setDictionary(dictionary_t* dict, const char* key, uint8_t value);
uint8_t* getDictionary(dictionary_t* dict, const char* key);
void removeDictionary(dictionary_t* dict, const char* key);
void clearDictionary(dictionary_t* dict);
const char* getDictionaryKey(dictionary_t* dict, size_t index);
size_t getDictionarySize(dictionary_t* dict);