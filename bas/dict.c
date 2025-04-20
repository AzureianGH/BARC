#include "dict.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>



void createDictionary(dictionary_t* dict) {
    dict->entries = NULL;
    dict->size = 0;
}

void destroyDictionary(dictionary_t* dict) {
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
}

bool keysEqual(const char* key1, const char* key2) {
    return strcmp(key1, key2) == 0;
}

void setDictionary(dictionary_t* dict, const char* key, uint8_t value) {
    for (size_t i = 0; i < dict->size; i++) {
        if (keysEqual(dict->entries[i].key, key)) {
            dict->entries[i].value = value;
            return;
        }
    }

    dict->entries = realloc(dict->entries, sizeof(_dictionary_entry_t) * (dict->size + 1));
    dict->entries[dict->size].key = strdup(key);
    dict->entries[dict->size].value = value;
    dict->size++;
}

uint8_t* getDictionary(dictionary_t* dict, const char* key) {
    for (size_t i = 0; i < dict->size; i++) {
        if (keysEqual(dict->entries[i].key, key)) {
            return &dict->entries[i].value;
        }
    }
    return NULL;
}

void removeDictionary(dictionary_t* dict, const char* key) {
    for (size_t i = 0; i < dict->size; i++) {
        if (keysEqual(dict->entries[i].key, key)) {
            free(dict->entries[i].key);
            memmove(&dict->entries[i], &dict->entries[i + 1], sizeof(_dictionary_entry_t) * (dict->size - i - 1));
            dict->size--;
            dict->entries = realloc(dict->entries, sizeof(_dictionary_entry_t) * dict->size);
            return;
        }
    }
}

void clearDictionary(dictionary_t* dict) {
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
}

const char* getDictionaryKey(dictionary_t* dict, size_t index) {
    if (index < dict->size) {
        return dict->entries[index].key;
    }
    return NULL; // Return NULL if index is out of bounds
}

size_t getDictionarySize(dictionary_t* dict) {
    return dict->size;
}
