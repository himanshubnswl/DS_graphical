//
// Created by lhbdawn on 30-08-2025.
//

#ifndef TREEINTERNALS_H
#define TREEINTERNALS_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * leftptr;
    struct Node * rightptr;
}Node;

#endif //TREEINTERNALS_H
