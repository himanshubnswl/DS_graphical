

#include "arrayGUI.h"

#include "../Graph/graphInternals.h"
#include "../helpers/helper.h"

typedef struct gui_element {
    int data;
    Rectangle shape;
    Color color;
}gui_element;


gui_element gui_elements[MAX_ELEMENTS_NUM];
size_t gui_elements_size = 0;

int Get_Selected_Element() {
    static int i = SELECTION_INVALID;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (i = 0; i < gui_elements_size; i++) {
            if (CheckCollisionPointRec(GetMousePosition(), gui_elements[i].shape)) {
                gui_elements[i].color = SELECTED_ELE_COLOR;
                gui_elements[i].shape.width = SELECTED_ELE_WIDTH;
                gui_elements[i].shape.height = SELECTED_ELE_HEIGHT;
                return i;
            }
        }
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        for (i = 0; i < gui_elements_size; i++) {
            gui_elements[i].color = DEFAULT_ELE_COLOR;
            gui_elements[i].shape.width = DEFAULT_REC_ELE_WIDTH;
            gui_elements[i].shape.height = DEFAULT_REC_ELE_HEIGHT;
        }
        i = SELECTION_INVALID;
    }
    return i;
}

int Draw_Array() {
    for (int i = 0; i < gui_elements_size; i++) {
        DrawRectangleRec(gui_elements[i].shape, DEFAULT_ELE_COLOR);
    }
    return 0;
}

int Remove_Element_Handler() {
    Rectangle const button = {
        .x = (GetScreenWidth() - 243),
        .y = (GetScreenHeight() - 106),
        .width = 100,
        .height = 75
    };

    if (GuiButton(button, "Remove")) {

    }
    return SUCCESS;
}

void Calculate_Shape() {
    for (size_t i = 0; i < gui_elements_size; i++) {
        size_t row = 1;
        if (i == 0) {
            gui_elements[i].shape = (Rectangle) {
                .x = STARTING_X,
                .y = STARTING_Y,
                .width = DEFAULT_REC_ELE_WIDTH,
                .height = DEFAULT_REC_ELE_HEIGHT
            };
        }
        else {
            gui_elements[i].shape = (Rectangle) {
                .x = gui_elements[i-1].shape.x + DEFAULT_REC_ELE_WIDTH,
                .y = gui_elements[i-1].shape.y,
                .width = DEFAULT_REC_ELE_WIDTH,
                .height = DEFAULT_REC_ELE_HEIGHT
            };

            if (gui_elements[i].shape.x + DEFAULT_REC_ELE_WIDTH >= GetScreenWidth()) {
                row++;
                gui_elements[i].shape.x = STARTING_X;
                gui_elements[i].shape.y = STARTING_Y * row;
            }
        }
    }
}
int Add_Element(int data) {
    if (gui_elements_size+1 == MAX_NUM_ELEMENTS) return ADD_ERROR;

    int selected_ele = Get_Selected_Element();
    if (selected_ele == SELECTION_INVALID) {
        gui_elements[gui_elements_size].data = data;
        gui_elements[gui_elements_size].shape = (Rectangle){
            .x = STARTING_X,
            .y = STARTING_Y,
            .width = DEFAULT_REC_ELE_WIDTH,
            .height = DEFAULT_REC_ELE_HEIGHT};
        gui_elements[gui_elements_size].color = DEFAULT_ELE_COLOR;
        gui_elements_size++;
    }
    else {
        for (int i = gui_elements_size - 1; i >= selected_ele; i++) {
            gui_elements[i + 1].data = gui_elements[i].data;
        }

        gui_elements[selected_ele].data = data;
        gui_elements_size++;
        Calculate_Shape();
    }
}

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
        int const result = GuiTextInputBox(input_dial_box, nullptr, nullptr, "Add", text , INPUT_TEXT_MAX_SIZE, nullptr);

        switch(result) {
            case 1:

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

int main() {
    InitWindow(1700, 900, "arrayGUI");
    Array_Initialize();

    while (!WindowShouldClose()) {
        BeginDrawing();

        EndDrawing();
    }
}
