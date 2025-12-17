//
// Created by lhbdawn on 04-09-2025.
//

#define ERROR_IMPLEMENTATION
#include "BinarySearchTreeGUI.h"
#define RAYGUI_IMPLEMENTATION
#define SCREEN_HEIGHT 900
#define SCREEN_WIDTH  1700

enum ERROR_HANDLER ERROR,ERROR1, ERROR2, ERROR3,ERROR4;

struct Stack {
    Node * BSTNode;
    int column;
    int row;
    int spacing;
};

void DrawBSTree() {
    static Node * root;
    root = GetBSTroot();
    if (root == nullptr) {
        return;
    }

    int screenHeight = GetScreenHeight();
    int screenwidth = GetScreenWidth();

    struct Stack static stack[30];
    static unsigned int sp = -1;

    stack[++sp] = (struct Stack){.BSTNode = root, .column = 0, .row = 1, .spacing = 5};


    static struct Stack iterate = {nullptr};
    static Vector2 posParent = {0};
    static Vector2 posChild = {0};

    while (sp != -1) {
#ifdef DEBUG
        DEBUG_PRINTF(sp);
#endif
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
}

int addGuiNode(int value) {
#ifdef DEBUG
    DEBUG_PRINTF(input);
#endif

#ifdef DEBUG
    DEBUG_CHECKPOINT(value);
#endif

    ERROR = addBSTNode(value);
    return ERROR;
}

int Add_Gui_Node_Handler() {
    Rectangle button = {
        .x = GetScreenWidth() - 129,
        .y = GetScreenHeight() - 106,
        .width = 100,
        .height = 75};
    Rectangle input_dial_box = {
        .x = GetScreenWidth() - 230,
        .y = GetScreenHeight() - 250,
        .width = 200,
        .height = 127};
    static bool input_dial_show = false;
    static char text[INPUT_TEXT_MAX_SIZE];

    if (GuiButton(button, "Add Element")) {
        input_dial_show = true;
    }
    if (input_dial_show) {
        int const result = GuiTextInputBox(input_dial_box, nullptr, nullptr, "Add", text , INPUT_TEXT_MAX_SIZE, nullptr);

        switch(result) {
            case 1:
                if (chars_to_int(text) != NOT_INT) {
                    return addGuiNode(text);    //propogate error from addGuiNode to the caller
                }
                else {
                    return NOT_INT; //handle the not integer case here
                }
                break;

            case 0:
                text[0] = '\0';
                input_dial_show = false;
                break;
            default:
                return SUCCESS;
        }
    }
    return SUCCESS;
}

int load_file() {
    Rectangle loadBox = {.x = GetScreenWidth()-600,
                                .y = GetScreenHeight() - 106,
                                .width = 100,
                                .height = 75};
    if (GuiButton(loadBox, "Load tree")) {
        ERROR = LoadBSTreeFromFile();
        return ERROR;
    }
    return ERROR;
}

int save_file() {
    Rectangle saveBox = {
        .x = GetScreenWidth()-443,
        .y = GetScreenHeight() - 106,
        .width = 100,
        .height = 75};

    if (GuiButton(saveBox, "Save Tree")) {
        ERROR = SaveBSTreeToFile();
        return ERROR;
    }
    return ERROR;
}

int Remove_Gui_Node_Handler() {
    Rectangle const button = {
        .x = (GetScreenWidth() - 243),
        .y = (GetScreenHeight() - 106),
        .width = 100,
        .height = 75
    };
    Rectangle input_dial_box = {
        .x = GetScreenWidth() - 230,
        .y = GetScreenHeight() - 250,
        .width = 200,
        .height = 127};
    static char text[INPUT_TEXT_MAX_SIZE];
    static bool input_dial_show = false;
    if (GuiButton(button, text)) {
        input_dial_show = true;
    }
    if (input_dial_show) {
        int result = GuiTextInputBox(input_dial_box, nullptr, nullptr, "add", text, INPUT_TEXT_MAX_SIZE, nullptr);
        switch (result) {
            case 0:
                text[0] = '\0';
                input_dial_show = false;
                break;

            case 1:
                if (chars_to_int(text) != NOT_INT) {
                    return removeBSTNode(chars_to_int(text)); //propogate error from function to caller
                }
                else {
                    return NOT_INT;
                }

            default:
                return SUCCESS;
        }
    }
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    GuiSetFont(LoadFont("Roboto-Italic-VariableFont_wdth,wght.ttf"));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BSTGUI");

    SetTargetFPS(60);

    char inputText[10];
    while (!WindowShouldClose()) {

        GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
        BeginDrawing();
        ClearBackground(GRAY);
        DrawBSTree();
        ERROR1 = inputElementHandler(inputText, addGuiNode);
        ERROR2 = removeElementHandler(removeBSTNode);

#ifdef DEBUG
        getPreOrderTraversal();
#endif

        ERROR3 = save_file();
        ERROR4 = load_file();
        EndDrawing();
        CheckAndDrawError(ERROR1);
        CheckAndDrawError(ERROR2);
        CheckAndDrawError(ERROR3);
        CheckAndDrawError(ERROR4);
    }
}