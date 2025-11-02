#include "array_internals.h"

int * arr = nullptr;
int size = 0;

int Array_Initialize() {
    arr = malloc(MAX_NUM_ELEMENTS * sizeof(int));
    if (arr == nullptr) return 1;

    size = 0;
    return 0;
}

int Array_Add_Ele(int data, int position) {
    if (position >= MAX_NUM_ELEMENTS - 1) return 1;
    for (int i = size - 1 ; i > position ; i--) {
        arr[i + 1] = arr[i];
    }
    arr[position] = data;
    size++;
    return 0;
}

int Array_Remove_Ele(int position) {
    if (position >= size || position < 0) return 1;

    for (int i = position ; i < size ; i++) {
        arr[i] = arr[i+1];
    }
    size--;
    return 0;
}