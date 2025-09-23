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
    int spacing;
};

int DrawBSTree() {
    Node * root = GetBSTroot();
    if (root == nullptr) {
        return 0;
    }

    int screenHeight = GetScreenHeight();
    int screenwidth = GetScreenWidth();

    static struct Stack stack[30];
    unsigned int sp = -1;
    stack[++sp] = (struct Stack){.BSTNode = root, .column = 0, .row = 1, .spacing = 5};


    struct Stack iterate = {nullptr};
    Vector2 posParent = {0};
    Vector2 posChild = {0};

    while (sp != -1) {
        iterate = stack[sp--];

        posParent = (Vector2){
            .x = (screenwidth/30) * (15 + (iterate.column)),
            .y = (screenHeight/30) * (iterate.row * 4)};

        if (iterate.BSTNode->rightptr != nullptr) {
            stack[++sp] = (struct Stack){
                .BSTNode = iterate.BSTNode->rightptr,
                .column = iterate.column + (1 * iterate.spacing),
                .row = iterate.row + 1,
                .spacing = iterate.spacing - 1};

            posChild = (Vector2){
                .x = (screenwidth/30) * (15 + (stack[sp].column)),
                .y = (screenHeight/30) * (stack[sp].row * 4)};

            DrawLineEx(posParent, posChild, 10, BLACK);
        }
        if (iterate.BSTNode->leftptr != nullptr) {
            stack[++sp] = (struct Stack){
                .BSTNode = iterate.BSTNode->leftptr,
                .column = iterate.column - (1 * iterate.spacing),
                .row = iterate.row + 1,
                .spacing = iterate.spacing - 1};

            posChild = (Vector2){
                .x = (screenwidth/30) * (15 + (stack[sp].column)),
                .y = (screenHeight/30) * (stack[sp].row * 4)};

            DrawLineEx(posParent, posChild, 10, BLACK);
        }

        DrawCircleV(posParent, 30, WHITE);
        DrawTextEx(GetFontDefault(), int_to_chars(iterate.BSTNode->data), (Vector2){posParent.x -10, posParent.y - 10}, 20, 3, GREEN);
#ifdef DEBUG
        DEBUG_PRINTF(iterate.BSTNode->data);
        DEBUG_PRINTF(int_to_chars(iterate.BSTNode->data));
#endif
    }
    return NO_ERROR;
}

int addGuiNode(char * input) {
#ifdef DEBUG
    DEBUG_PRINTF(input);
#endif

    int value = chars_to_int(input);
    if (value == NOT_INT) {
        return ADD_ERROR;
    }
    else {
        addBSTNode(value);
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

void load_file() {
    Rectangle loadBox = {.x = GetScreenWidth()-600,
                                .y = GetScreenHeight() - 106,
                                .width = 100,
                                .height = 75};
    if (GuiButton(loadBox, "Load tree")) {
        LoadBSTreeFromFile();

#ifdef DEBUG
        DEBUG_PRINTF(value);
#endif
    }
}

void save_file() {
    Rectangle saveBox = {.x = GetScreenWidth()-443,
                                .y = GetScreenHeight() - 106,
                                .width = 100,
                                .height = 75};
    if (GuiButton(saveBox, "Save Tree")) {
        SaveBSTreeToFile();
    }
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BSTGUI");

    SetTargetFPS(60);

    bool dialogue_box_status;
    char inputText[10];
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        inputElementHandler(&dialogue_box_status, inputText, addGuiNode);
        DrawBSTree();
        removeNodeHandler();
#ifdef DEBUG
        getPreOrderTraversal();
#endif
        save_file();
        load_file();
        EndDrawing();
    }
}