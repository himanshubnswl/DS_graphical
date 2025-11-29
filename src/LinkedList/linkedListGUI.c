

#include "linkedListGUI.h"

enum ERROR_HANDLER ERROR;
typedef struct gui_element {
    int data;
    Rectangle shape;
    Color color;
}gui_element;


gui_element gui_elements[MAX_NUM_ELEMENTS];
size_t gui_elements_size = 0;

int Get_Selected_Element() {
    static int selected_index = SELECTION_INVALID;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (int i = 0; i < gui_elements_size; i++) {
            if (CheckCollisionPointRec(GetMousePosition(), gui_elements[i].shape)) {
                gui_elements[i].color = SELECTED_ELE_COLOR;
                gui_elements[i].shape.width = SELECTED_ELE_WIDTH;
                gui_elements[i].shape.height = SELECTED_ELE_HEIGHT;
                selected_index = i;
            }
        }
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        for (int i = 0; i < gui_elements_size; i++) {
            gui_elements[i].color = DEFAULT_ELE_COLOR;
            gui_elements[i].shape.width = DEFAULT_REC_ELE_WIDTH;
            gui_elements[i].shape.height = DEFAULT_REC_ELE_HEIGHT;
        }
        selected_index = SELECTION_INVALID;
    }
    DEBUG_PRINTF(selected_index);
    return selected_index;
}

void Draw_Array() {
    for (int i = 0; i < gui_elements_size; i++) {
        DrawRectangleRec(gui_elements[i].shape, DEFAULT_ELE_COLOR);
        DrawRectangleLinesEx(gui_elements[i].shape, DEFAULT_REC_ELE_BORDER_LINE_THICKNESS, BLACK);
        DrawText(int_to_chars(gui_elements[i].data), gui_elements[i].shape.x + REC_TEXT_OFFSET_X, gui_elements[i].shape.y + REC_TEXT_OFFSET_Y, 20, BLACK);
    }
}

void Print_Ele_Array() {
    printf("\n--------------------------------------------------------\n");

    for (int i = 0; i < gui_elements_size; i++) {
        printf("%d ", gui_elements[i].data);
    }

    printf("\n---------------------------------------------------------\n");
}

int Remove_Element() {
    if (gui_elements_size == 0) return 1;

    int selected_ele = Get_Selected_Element();
    if (selected_ele == SELECTION_INVALID) {
        gui_elements_size--;
        Calculate_Shape();
        return 0;
    }
    else {
        for (int i = selected_ele; i < gui_elements_size - 1; i++) {
            gui_elements[i] = gui_elements[i+1];
        }
        gui_elements_size--;
        Calculate_Shape();
        return 0;
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
        if (Remove_Element() != 0) return REMOVE_ERROR;
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
                gui_elements[i].shape.y = (STARTING_Y * (row)) + ROW_GAP;
            }
        }
    }
}

int Add_Element(int data) {
    if (gui_elements_size + 1 == MAX_NUM_ELEMENTS) return 1;

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
        Calculate_Shape();
        return 0;
    }
    else {
        for (int i = gui_elements_size - 1; i >= selected_ele; i--) {
            gui_elements[i + 1].data = gui_elements[i].data;
        }

        gui_elements[selected_ele].data = data;
        gui_elements_size++;
        Calculate_Shape();
        return 0;
    }
    return 0;
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

    static bool input_dial_show = false;
    static char text[50];

    if (GuiButton(button, "Add Element")) {
        input_dial_show = true;
    }
    if (input_dial_show) {
        int const result = GuiTextInputBox(input_dial_box, nullptr, nullptr, "Add", text , INPUT_TEXT_MAX_SIZE, nullptr);

        switch(result) {
            case 1:
                if (chars_to_int(text) == NOT_INT) return NOT_INT;
                else if (Add_Element(chars_to_int(text)) != 0) return ADD_ERROR;
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

void Debug_Mode() {
    Rectangle box = {
        .x = 100,
        .y = GetScreenHeight()/4,
        .width = 250,
        .height = 100
    };
    Rectangle box_2 = {
        .x = 100,
        .y = GetScreenHeight()/2,
        .width = 250,
        .height = 100
    };

    int prevstyle = GuiGetStyle(DEFAULT, TEXT_SIZE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);

    if (Get_Selected_Element() == SELECTION_INVALID)
        GuiTextBox(box, "SELECTION INVALID", 20, false);

    GuiTextBox(box, int_to_chars(Get_Selected_Element()), 20, false);
    GuiTextBox(box_2, int_to_chars(gui_elements_size), 20, false);

    GuiSetStyle(DEFAULT, TEXT_SIZE, prevstyle);
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1700, 900, "arrayGUI");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        Draw_Array();
        Debug_Mode();
        ERROR = Add_Element_Handler();
        CheckAndDrawError(ERROR);
        DEBUG_PRINTF(ERROR);
        ERROR = Remove_Element_Handler();
        CheckAndDrawError(ERROR);
        DEBUG_PRINTF(ERROR);
        Print_Ele_Array();
        Get_Selected_Element();

        EndDrawing();
    }
}
