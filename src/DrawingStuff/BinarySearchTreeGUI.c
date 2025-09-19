//
// Created by lhbdawn on 04-09-2025.
//

#include "BinarySearchTreeGUI.h"


#define SCREEN_HEIGHT 900
#define SCREEN_WIDTH  1700

enum ERROR_HANDLER ERROR;

struct Stack {
    Node * BSTNode;
    int column;
    int row;
};

int DrawBSTree() {
    Node * root = GetBSTroot();

    int screenHeight = GetScreenHeight();
    int screenwidth = GetScreenWidth();
    struct Stack stack[30];
    unsigned int sp = -1;
    stack[++sp] = (struct Stack){.BSTNode = root, .column = 0, .row = 1};
    struct Stack iterate = {0};
    Vector2 pos = {0};
    while (sp != -1) {
        iterate = stack[sp--];
        if (iterate.BSTNode->rightptr != nullptr) {
            stack[++sp] = (struct Stack){
                .BSTNode = iterate.BSTNode->rightptr,
                .column = iterate.column + 1,
                .row = iterate.row + 1};
        }
        else if (iterate.BSTNode->leftptr != nullptr) {
            stack[++sp] = (struct Stack){
                .BSTNode = iterate.BSTNode->leftptr,
                .column = iterate.column - 1,
                .row = iterate.row + 1};
        }
        pos = (Vector2){
            .x = (screenwidth/50) * (25 + (iterate.column)),
            .y = (screenHeight/30) * (iterate.row * 2)};
        DrawCircleV(pos, 20, WHITE);
        DrawTextEx(GetFontDefault(), int_to_chars(iterate.BSTNode->data), pos, 15, 3, GREEN);
    }
}

int addGuiNode(char * input) {
    int value = chars_to_int(input);
    if (value == NOT_INT) {
        return ADD_ERROR;
    }
    else {
        addNode(value);
        return NO_ERROR;
    }
}

int removeNodeHandler() {
    Rectangle removeButton = {
        .x = (GetScreenWidth() - 243),
        .y = (GetScreenHeight() - 106),
        .width = 100,
        .height = 75
    };

    if (GuiButton(removeButton, "remove selected")) {

    }
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BSTGUI");

    SetTargetFPS(60);

    bool dialogue_box_status;
    char inputText[10];
    while (!WindowShouldClose()) {

        inputElementHandler(&dialogue_box_status, inputText, addGuiNode);
        DrawBSTree();
        removeNodeHandler();
    }
}