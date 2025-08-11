
#include "helper.h"

char * int_to_chars(int number)
{
    char * result = (char *)malloc(sizeof(char) * 6); //6 to accomodate the EOL char
    for (size_t i = 5; i > 0 ; i--)
    {
        if ((number/(int)pow(10,i)))
        {
            int k = i;
            for (size_t j = 0; j <= i; j++) {
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
        char ch = text[i];
        if ((ch <= '9') && (ch >= '0')) {
            value = (value * 10 ) + (ch - '0');
        }
        else
            return 0;
    }
    return value;
}