//
// Created by lhbdawn on 30-08-2025.
//

#include <string.h>
#include <TreeInternals.h>

#include "error.h"
#include "helper.h"

Node * root = nullptr;


void initialize(int data) {
    root = (Node *)malloc(sizeof(Node));
    root->data = data;
    root->leftptr = nullptr;
    root->rightptr = nullptr;

}
void addNode(int data) {
    Node * iterateNode = root;
    Node * parentNode = nullptr;
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

int removeNode(int valueToRemove) {
    if (root == nullptr) {
        return REMOVE_ERROR;
    }
    Node * currentNode = root;
    Node * parentNode = nullptr;

    while (currentNode != nullptr && currentNode->data != valueToRemove) {
        parentNode = currentNode;
        if (valueToRemove < currentNode->data) {
            currentNode = currentNode->leftptr;
        }
        else {
            currentNode = currentNode->rightptr;
        }
    }
    if (currentNode == nullptr) {
        return 2;
    }

    if (currentNode->leftptr == nullptr && currentNode->rightptr == nullptr) {
        if (parentNode->leftptr == currentNode) {
            parentNode->leftptr = nullptr;
            free(currentNode);
        }
        else {
            parentNode->rightptr = nullptr;
            free(currentNode);
        }
    }

    else if (currentNode->rightptr == nullptr || currentNode->leftptr == nullptr) {
        Node * childNode;
        if (currentNode->rightptr != nullptr) {
            childNode = currentNode->rightptr;
        }
        else {
            childNode = currentNode->leftptr;
        }
        if (parentNode->leftptr == currentNode) {
            parentNode->leftptr = childNode;
            free(currentNode);
        }
        else {
            parentNode->rightptr = childNode;
            free(currentNode);
        }
    }

    else {
        Node * succesorNode = currentNode->rightptr;
        Node * succesorParent = currentNode;

        while (succesorNode->leftptr != nullptr) {
            succesorParent = succesorNode;
            succesorNode = succesorNode->leftptr;
        }

        currentNode->data = succesorNode->data;

        if (succesorParent->leftptr == succesorNode) {
            succesorParent->leftptr = succesorNode->rightptr;
            free(succesorNode);
        }
        else {
            succesorParent->rightptr = succesorNode->rightptr;
            free(succesorNode);
        }
    }
}

Node * GetBSTroot() {
    if (root == nullptr) {
        return nullptr;
    }
    else
        return root;
}

int * getPreOrderTraversal() {
    int * preOrder = (int *)malloc(sizeof(int) * 50);
    memset(preOrder, 0, sizeof(preOrder));

    Node ** Stack = (Node **)malloc(sizeof(Node *) * 50);
    int stack_pointer = -1;
    int order_index = -1;
    if (root == nullptr) {
        free(preOrder);
        free(Stack);
        return nullptr;
    }
    Stack[++stack_pointer] = root;
    Node * iterateNode = nullptr;
    while (stack_pointer != -1) {
        iterateNode = Stack[stack_pointer--];
        preOrder[++order_index] = iterateNode->data;

        if (iterateNode->rightptr != nullptr) {
            Stack[++stack_pointer] = iterateNode->rightptr;
        }
        if (iterateNode->leftptr != nullptr) {
            Stack[++stack_pointer] = iterateNode->leftptr;
        }
    }
    free(Stack);
    return preOrder;
}

int SaveBSTreeToFile() {
    int * BSTpreOrder = getPreOrderTraversal();
    if (BSTpreOrder == nullptr) {
        return 0;
    }
    if (_chdir("./savedfile") == -1) {
        _mkdir("./savedfile");
        _chdir("./savedfile");
    }
    _chdir("../");
    FILE * save_file = fopen("./savedfile/saveBSTree.txt", "w");
    unsigned int i = 0;
    while (BSTpreOrder[i] != 0) {
        fputs(int_to_chars(BSTpreOrder[i]), save_file);
        fputs(", " , save_file);
        i++;
    }
    fclose(save_file);
}

int LoadBSTreeFromFile() {

}