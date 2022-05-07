#pragma once
#include <stdint.h>
#include <stddef.h>

struct TwoStrings
{
    char a[128];
    char b[128];
};

const char* to_string(uint64_t value);
const char* to_string(int64_t value);
const char* to_hstring(uint64_t value);
const char* to_hstring(uint32_t value);
const char* to_hstring(uint16_t value);
const char* to_hstring(uint8_t value);
const char* to_string(double value, uint8_t decimalPlaces);
const char* to_string(double value);
int strlen(char* str);
bool strcmp(char* str1, char* str2);

TwoStrings strsplit(char *str, char split);