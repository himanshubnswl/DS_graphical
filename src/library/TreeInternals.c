//
// Created by lhbdawn on 30-08-2025.
//

#include "TreeInternals.h"

Node * root = nullptr;

void initialize(int data) {
    root = (Node *)malloc(sizeof(Node));
    root->data = data;
    root->leftptr = nullptr;
    root->rightptr = nullptr;

}
void addNode(int data) {
    Node * iterateNode = root;
    Node * parentNode;
    if (iterateNode == nullptr) {
        initialize(data);
        return;
    }
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->rightptr = nullptr;
    newNode->leftptr = nullptr;

    while (iterateNode != nullptr) {
        if (iterateNode->data == data) {
            free(newNode);
            return;
        }
        parentNode = iterateNode;

        if (data < iterateNode->data) {
            iterateNode = iterateNode->leftptr;
        }
        else {
            iterateNode = iterateNode->rightptr;
        }
    }
    if (data < parentNode->data) {
        parentNode->leftptr = newNode;
    }
    else {
        parentNode->rightptr = newNode;
    }

}