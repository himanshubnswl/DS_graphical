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
void addBSTNode(const int data) {
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

int removeBSTNode(const int valueToRemove) {
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
            return SUCCESS;
        }
        else {
            parentNode->rightptr = nullptr;
            free(currentNode);
            return SUCCESS;
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
            return SUCCESS;
        }
        else {
            parentNode->rightptr = childNode;
            free(currentNode);
            return SUCCESS;
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
            return SUCCESS;
        }
        else {
            succesorParent->rightptr = succesorNode->rightptr;
            free(succesorNode);
            return SUCCESS;
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
    static int * preOrder = nullptr;
    if (preOrder == nullptr) {
        preOrder = (int *)malloc(50 * sizeof(int));
    }
    memset(preOrder, 0, sizeof(preOrder));

    Node *Stack[50];
    int stack_pointer = -1;
    int order_index = -1;

    if (root == nullptr) {
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
    return preOrder; //have to free this when used
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
    while (BSTpreOrder[i+1] != 0) {
        fputs(int_to_chars(BSTpreOrder[i]), save_file);
        fputs("," , save_file);
        i++;
    }
    fputs(int_to_chars(BSTpreOrder[i]), save_file);
    fclose(save_file);
    return NO_ERROR;
}

void deleteBSTree() {
    Node * iterateNode = GetBSTroot();
    if (iterateNode == nullptr) {
        return;
    }

    Node * stack[50];
    int stack_pointer = -1;
    stack[++stack_pointer] = iterateNode;
    while (stack_pointer != -1) {
        iterateNode = stack[stack_pointer--];
        if (iterateNode->rightptr != nullptr) {
            stack[++stack_pointer] = iterateNode->rightptr;
        }
        if (iterateNode->leftptr != nullptr) {
            stack[++stack_pointer] = iterateNode->leftptr;
        }
        free(iterateNode);
        root = nullptr;
    }
}

int LoadBSTreeFromFile() { //when i load three times the app crashes, need to look into it
    deleteBSTree();
    FILE * loadFrom = fopen("./savedfile/saveBSTree.txt", "r");
    if (loadFrom == NULL) {
        printf("\nCouldn't open the file, make sure you save the file first");
        fclose(loadFrom);
    }

    char * inputBuffer = (char *)malloc(sizeof(char) *  256);
    memset(inputBuffer, 255, sizeof(inputBuffer));
    fgets(inputBuffer, 256, loadFrom);
    int value = chars_to_int(strtok(inputBuffer, ","));
    printf("\nvalue taken from file is %d", value);
    while (1) {
        value = atoi(strtok(nullptr, ","));

        if (value == 0) {
            break;
        }
        printf("\nvalue taken from file is %d", value);
        addBSTNode(value);
    }
    free(inputBuffer);
    fclose(loadFrom);
    return NO_ERROR;
}