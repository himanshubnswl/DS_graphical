//
// Created by lhbdawn on 30-08-2025.
//

#ifndef TREEINTERNALS_H
#define TREEINTERNALS_H
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

typedef struct Node {
    int data;
    struct Node * leftptr;
    struct Node * rightptr;
}Node;

void initialize(int data);
void addNode(int data);
int removeNode(int valueToRemove);
int * getPreOrderTraversal();
Node * GetBSTroot();
int SaveBSTreeToFile();
int LoadBSTreeFromFile();
void deleteBSTree();





#endif //TREEINTERNALS_H
