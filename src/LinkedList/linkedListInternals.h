#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

typedef struct __NODE {
    int data;
    struct __NODE * nextptr;
}__NODE;

void initializeLinkedList(int data);
void addNode(int data);
__NODE * getNode(int index) ;
bool checkIndex(int index);
void removeNode(int i);
__NODE * getHead();
int getSizeLL();