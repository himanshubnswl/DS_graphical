

#include "arrayGUI.h"


int Add_Element_Handler() {
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

    bool input_dial_show = false;
    static char text[50];

    if (GuiButton(button, "Add Element")) {
        input_dial_show = true;
    }
    if (input_dial_show) {
        int result = GuiTextInputBox(input_dial_box, nullptr, nullptr, "Add", text , INPUT_TEXT_MAX_SIZE, nullptr);

        switch(result) {
            case 1:
                break;

            case 0:
                text[0] = '\0';
                input_dial_show = false;
                return SUCCESS;

            default:
                return SUCCESS;
        }
    }
    return SUCCESS;
}

int main() {
    InitWindow(1700, 900, "arrayGUI");
    Array_Initialize();

    while (!WindowShouldClose()) {
        BeginDrawing();

        EndDrawing();
    }
}
