
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

typedef struct __NODE {
    int data;
    struct __NODE * nextptr;
}__NODE;


int size = 0;
__NODE *head;

__NODE * getHead() {
    if (head != NULL)
        return head;
    else return NULL;
}

int getSizeLL() {
    return size;
}

void initializeLinkedList(int data) { //never call directly
    head = (__NODE *)malloc(sizeof(__NODE));
    if (head == NULL) return;
    head->data = data;
    head->nextptr = NULL;
}

void addNode(int data) {
    if (size == 0) {
        initializeLinkedList(data);
        size++;
    }
    else {
        __NODE *newNode = (__NODE *)malloc(sizeof(__NODE));
        newNode->data = data;
        newNode->nextptr = NULL;
        __NODE * iterateNode = getHead();

        for (size_t i = 0; i < size - 1; i++ ) {
            iterateNode = iterateNode->nextptr;
        }
        iterateNode->nextptr = newNode;
        size++;
    }
}

__NODE * getNode(int index) {
    __NODE * iterateNode = head;
    for (size_t i = 0; i <= index; i++) {
        iterateNode = iterateNode->nextptr;
    }
    if (iterateNode == NULL) return NULL;
    else return iterateNode;
}

bool checkIndex(int index) {
    if (index <= size) {
        return true;
    }
    else return false;
}

void removeNode(int i) {
    // __NODE * bufferNode;
    // __NODE * iterateNode = getHead();
    // if (size == 0) return;
    // if (size == 1) {
    //     head =  NULL;
    //     free(iterateNode);
    //     size--;
    //     return;
    // }
    //
    // while (iterateNode->nextptr != NULL) {
    //     bufferNode = iterateNode;
    //     iterateNode = iterateNode->nextptr;
    // }
    // bufferNode->nextptr = NULL;
    // free(iterateNode);
    // size--;
    __NODE * bufferNode;
    __NODE * iterateNode = getHead();

    if (size == 0) return;

    printf("\n size is %d", size);
    printf("\n i is %d", i);

    switch (i) {
        case 1:
            head = iterateNode->nextptr;
            free(iterateNode);
            size--;
            break;

        default:
            if (i == size) {
                for (int count = 1; count <i; count++) {
                    bufferNode = iterateNode;
                    iterateNode = iterateNode->nextptr;
                }
                bufferNode->nextptr = NULL;
                free(iterateNode);
                size--;
                break;
            }
            printf("\nhere");
            for (int count = 1; count <=i; count++) {
                bufferNode = iterateNode;
                iterateNode = iterateNode->nextptr;
            }
            bufferNode->nextptr = iterateNode->nextptr;
            free(iterateNode);
            size--;
            break;
    }

}


