//
// Created by lhbdawn on 30-08-2025.
//

#ifndef TREEINTERNALS_H
#define TREEINTERNALS_H
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <string.h>
#include "../helpers/helper.h"
#ifdef DEBUG
#include <debug.h>
#endif

typedef struct Node {
    int data;
    struct Node * leftptr;
    struct Node * rightptr;
}Node;

void initialize(int data); //initialize a function, is called internally by addBSTNode()
void addBSTNode(int data); //add a node to the tree
int removeBSTNode(int valueToRemove);//remove the node from the tree by the value specified
int * getPreOrderTraversal(); //returns an array with preOrder values of tree
Node * GetBSTroot(); //to get the root of the tree
int SaveBSTreeToFile(); //to save the tree to a file
int LoadBSTreeFromFile();//to load a tree from the file
void deleteBSTree(); //to delete the entire tree





#endif //TREEINTERNALS_H
