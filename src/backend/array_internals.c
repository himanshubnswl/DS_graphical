#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#pragma once
size_t SIZE;
size_t LAST = 0;
int * _INTEGER_ARRAY;

void initialize(int __size) {
    SIZE = __size;

    _INTEGER_ARRAY = (int *)malloc(SIZE * sizeof(int *));
}

bool isEmpty() {
  return  (LAST == 0) ? (true) :(false);
}

bool isFull(int __value) {
    if (LAST == SIZE - 1)
    {
        _INTEGER_ARRAY = realloc(_INTEGER_ARRAY, SIZE * 2);
        if (_INTEGER_ARRAY == NULL) {
            return false;
        }
        SIZE = SIZE * 2;
        _INTEGER_ARRAY[LAST++] = __value;
        printf("\n array extended");
        return true;
    }
    else return false;
}

void insertElement(int data)  {
    if (isFull(data))
    {
        return;
    }
    
    _INTEGER_ARRAY[LAST++] = data;
}

void removeElement() {
    if (isEmpty())
    {
        printf("\n array is empty!");
        return;
    }
    LAST--;
}

void printArray() {

    printf("\n [");
    for (size_t i = 0; i < LAST; i++)
    {
        printf(" %d,", _INTEGER_ARRAY[i]);
    }
    printf("]");
    
}

void deleteArray() {
    free(_INTEGER_ARRAY);
}

int getSize(void)
{
    return LAST;
}

int getElement(int i) //return actual last + 1
{
    if (LAST == 0) {
        return 0;
    }
    if (i <= LAST)
        return _INTEGER_ARRAY[i];

    else return 0;
}

// char * int_to_chars(int number)
// {
//     char * result = (char *)malloc(sizeof(char) * 6); //6 to accomodate the EOL char
//     for (size_t i = 5; i > 0 ; i--)
//     {
//         if ((number/(int)pow(10,i)))
//         {
//             int k = i;
//             for (size_t j = 0; j <= i; j++) {
//                 const int inter_num = (number/(int)pow(10, k)) % 10;
//                 result[j] = inter_num + '0';
//                 result[j + 1] = '\0'; //adding a EOL char manually
//                 k--;
//             }
//             return result;
//         }
//     }
//     return nullptr;
// }