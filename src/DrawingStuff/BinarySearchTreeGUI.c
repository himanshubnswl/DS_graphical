//
// Created by lhbdawn on 04-09-2025.
//

#include "BinarySearchTreeGUI.h"


#define SCREEN_HEIGHT 900
#define SCREEN_WIDTH  1700

int DrawBSTree() {

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
    }
}