#define RAYGUI_IMPLEMENTATION
#include "helper.h"


char * int_to_chars(int number) {
    if (number < 0) {
        return nullptr;
    }
    if (number == 0) {
        return "0";
    }
    static char result[20]; //6 to accomodate the EOL char
    for (int i = 5; i >= 0 ; i--)
    {
        if ((number/(int)pow(10,i)))
        {
            int k = i;
            for (int j = 0; j <= i; j++) {
                const int inter_num = (number/(int)pow(10, k)) % 10;
                result[j] = inter_num + '0';
                result[j + 1] = '\0'; //adding a EOL char manually
                k--;
            }
            return result;
        }
    }
    return nullptr;
}

int chars_to_int(char * text) {
    size_t i = 0;
    int value = 0;
    while (text[i] != '\0') {
#ifdef DEBUG
        DEBUG_PRINTF(text);
#endif
        char ch = text[i];
        if ((ch <= '9') && (ch >= '0')) {
            value = (value * 10 ) + (ch - '0');
#ifdef DEBUG
            DEBUG_PRINTF(value);
#endif
        }
        else
            return NOT_INT;
        i++;
    }
    return value;
}

uint32_t Hash_String_FNV(char const * string_to_hash) {
    uint32_t hash = HASH_FNV_OFFSET;
    int i = 0;
    while (string_to_hash[i] != '\0') {
        hash = hash ^ string_to_hash[i];
        hash = hash * FNV_PRIME;
        i++;
    }
    return hash;
}

