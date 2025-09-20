//
// Created by lhbdawn on 04-09-2025.
//
#define DEBUG

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
    if (root == nullptr) {
        return 0;
    }

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
        if (iterate.BSTNode->leftptr != nullptr) {
            stack[++sp] = (struct Stack){
                .BSTNode = iterate.BSTNode->leftptr,
                .column = iterate.column - 1,
                .row = iterate.row + 1};
        }
        pos = (Vector2){
            .x = (screenwidth/30) * (15 + (iterate.column)),
            .y = (screenHeight/30) * (iterate.row * 4)};
        DrawCircleV(pos, 30, WHITE);
        DrawTextEx(GetFontDefault(), int_to_chars(iterate.BSTNode->data), (Vector2){pos.x -10, pos.y - 10}, 20, 3, GREEN);
        DEBUG_PRINTF(iterate.BSTNode->data);
        DEBUG_PRINTF(int_to_chars(iterate.BSTNode->data));
    }
    return NO_ERROR;
}

int addGuiNode(char * input) {
    DEBUG_PRINTF(input);
    int value = chars_to_int(input);
    DEBUG_PRINTF(value);
    if (value == NOT_INT) {
        return ADD_ERROR;
    }
    else {
        addNode(value);
        printf("\nsomething is wrong here");
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
    return NO_ERROR;
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BSTGUI");

    SetTargetFPS(60);

    bool dialogue_box_status;
    char inputText[10];
    while (!WindowShouldClose()) {
        DEBUG_CHECKPOINT(93);
        BeginDrawing();
        ClearBackground(GRAY);
        inputElementHandler(&dialogue_box_status, inputText, addGuiNode);
        DrawBSTree();
        removeNodeHandler();
        getPreOrderTraversal();
        EndDrawing();
    }
}