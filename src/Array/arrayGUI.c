#define RAYGUI_IMPLEMENTATION
#include "arrayGUI.h"


enum ERROR_HANDLER ERROR;

// gui_element gui_elements[MAX_NUM_ELEMENTS];


gui_element *init(int size) {
    gui_element *gui_elements = calloc(size, sizeof(gui_element));
    if (gui_elements == nullptr) {
        return nullptr;
    }
    return gui_elements;
}

int Get_Selected_Element(gui_element *gui_elements, size_t gui_elements_size) {
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
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        for (int i = 0; i < gui_elements_size; i++) {
            gui_elements[i].color = DEFAULT_ELE_COLOR;
            gui_elements[i].shape.width = DEFAULT_REC_ELE_WIDTH;
            gui_elements[i].shape.height = DEFAULT_REC_ELE_HEIGHT;
        }
        selected_index = SELECTION_INVALID;
    }
    return selected_index;
}

void Draw_Array(const gui_element *const gui_elements, size_t gui_elements_size) {
    for (int i = 0; i < gui_elements_size; i++) {
        DrawRectangleRec(gui_elements[i].shape, DEFAULT_ELE_COLOR);
        DrawRectangleLinesEx(gui_elements[i].shape, DEFAULT_REC_ELE_BORDER_LINE_THICKNESS, BLACK);
        DrawText(int_to_chars(gui_elements[i].data), gui_elements[i].shape.x + REC_TEXT_OFFSET_X,
                 gui_elements[i].shape.y + REC_TEXT_OFFSET_Y, 20, BLACK);
    }
}

void Print_Ele_Array(const gui_element *const gui_elements, size_t gui_elements_size) {
    printf("\n--------------------------------------------------------\n");

    for (int i = 0; i < gui_elements_size; i++) {
        printf("%d ", gui_elements[i].data);
    }

    printf("\n---------------------------------------------------------\n");
}

int Remove_Element(gui_element *gui_elements, size_t *gui_elements_size) {
    if (gui_elements_size == 0) return 1;

    int selected_ele = Get_Selected_Element(gui_elements, *gui_elements_size);
    if (selected_ele == SELECTION_INVALID) {
        (*gui_elements_size)--;
        Calculate_Shape(gui_elements, *gui_elements_size);
        return 0;
    } else {
        for (int i = selected_ele; i < (*gui_elements_size) - 1; i++) {
            gui_elements[i] = gui_elements[i + 1];
        }
        (*gui_elements_size)--;
        Calculate_Shape(gui_elements, *gui_elements_size);
        return 0;
    }
    return 0;
}

int Remove_Element_Handler(gui_element *gui_elements, size_t *gui_elements_size) {
    Rectangle const button = {
        .x = (GetScreenWidth() - 243),
        .y = (GetScreenHeight() - 106),
        .width = 100,
        .height = 75
    };

    if (GuiButton(button, "Remove")) {
        if (Remove_Element(gui_elements, gui_elements_size) != 0) return REMOVE_ERROR;
    }
    return SUCCESS;
}

void Calculate_Shape(gui_element *gui_elements, size_t gui_elements_size) {
    int row = 1;
    for (int i = 0; i < gui_elements_size; i++) {
        if (i == 0) {
            gui_elements[i].shape = (Rectangle){
                .x = STARTING_X,
                .y = STARTING_Y,
                .width = DEFAULT_REC_ELE_WIDTH,
                .height = DEFAULT_REC_ELE_HEIGHT
            };
        } else {
            gui_elements[i].shape = (Rectangle){
                .x = gui_elements[i - 1].shape.x + DEFAULT_REC_ELE_WIDTH,
                .y = gui_elements[i - 1].shape.y,
                .width = DEFAULT_REC_ELE_WIDTH,
                .height = DEFAULT_REC_ELE_HEIGHT
            };

            if (gui_elements[i].shape.x + DEFAULT_REC_ELE_WIDTH >= GetScreenWidth()) {
                row++;
                gui_elements[i].shape.x = STARTING_X;
                gui_elements[i].shape.y = (STARTING_Y * (row)) + (ROW_GAP * row);
            }
        }
    }
}

int Add_Element(int data, gui_element *gui_elements, size_t *gui_elements_size) {
    if ((*gui_elements_size) + 1 == MAX_NUM_ELEMENTS) return 1;

    int selected_ele = Get_Selected_Element(gui_elements, *gui_elements_size);
    if (selected_ele == SELECTION_INVALID) {
        gui_elements[*gui_elements_size].data = data;
        gui_elements[*gui_elements_size].shape = (Rectangle){
            .x = STARTING_X,
            .y = STARTING_Y,
            .width = DEFAULT_REC_ELE_WIDTH,
            .height = DEFAULT_REC_ELE_HEIGHT
        };
        gui_elements[*gui_elements_size].color = DEFAULT_ELE_COLOR;
        (*gui_elements_size)++;
        Calculate_Shape(gui_elements, *gui_elements_size);
        return 0;
    } else {
        for (int i = (*gui_elements_size) - 1; i >= selected_ele; i--) {
            gui_elements[i + 1].data = gui_elements[i].data;
        }

        gui_elements[selected_ele].data = data;
        (*gui_elements_size)++;
        Calculate_Shape(gui_elements, *gui_elements_size);
    }
    return 0;
}

int Add_Element_Handler(gui_element *gui_elements, size_t *gui_elements_size) {
    Rectangle button = {
        .x = GetScreenWidth() - 129,
        .y = GetScreenHeight() - 106,
        .width = 100,
        .height = 75
    };
    Rectangle input_dial_box = {
        .x = GetScreenWidth() - 230,
        .y = GetScreenHeight() - 250,
        .width = 200,
        .height = 127
    };

    static bool input_dial_show = false;
    static char text[50];

    if (GuiButton(button, "Add Element")) {
        input_dial_show = true;
    }
    if (input_dial_show) {
        int const result = GuiTextInputBox(input_dial_box, nullptr, nullptr, "Add", text, INPUT_TEXT_MAX_SIZE, nullptr);

        switch (result) {
            case 1:
                if (chars_to_int(text) == NOT_INT) return NOT_INT;
                else if (Add_Element(chars_to_int(text), gui_elements, gui_elements_size) != 0) return ADD_ERROR;
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

void Debug_Mode(gui_element *gui_elements, size_t gui_elements_size) {
    Rectangle box = {
        .x = 100,
        .y = GetScreenHeight() / 4,
        .width = 250,
        .height = 100
    };
    Rectangle box_2 = {
        .x = 100,
        .y = GetScreenHeight() / 2,
        .width = 250,
        .height = 100
    };

    int prevstyle = GuiGetStyle(DEFAULT, TEXT_SIZE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);

    if (Get_Selected_Element(gui_elements, gui_elements_size) == SELECTION_INVALID)
        GuiTextBox(box, "SELECTION INVALID", 20, false);

    GuiTextBox(box, int_to_chars(Get_Selected_Element(gui_elements, gui_elements_size)), 20, false);
    GuiTextBox(box_2, int_to_chars(gui_elements_size), 20, false);

    GuiSetStyle(DEFAULT, TEXT_SIZE, prevstyle);
}

int Save_Handler(const gui_element *const gui_elements, size_t gui_elements_size) {
    const Rectangle saveBox = {
        .x = GetScreenWidth() - 353,
        .y = GetScreenHeight() - 106,
        .width = 100,
        .height = 75
    };

    if (GuiButton(saveBox, "Save")) {
        FILE *file = fopen("saveArray.txt", "w");
        if (file == nullptr) {
            return SAVE_FAIL;
        } else {
            for (int i = 0; i < gui_elements_size; i++) {
                fprintf(file, "%d, ", (int) gui_elements[i].data);
            }
        }
        fclose(file);
        return SAVE_SUCCESS;
    }
}

int main() {
    gui_element *gui_elements = init(MAX_NUM_ELEMENTS);
    if (gui_elements == nullptr) exit(0);
    size_t gui_elements_size = 0;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1700, 900, "arrayGUI");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        Draw_Array(gui_elements, gui_elements_size);
        Debug_Mode(gui_elements, gui_elements_size);
        ERROR = Add_Element_Handler(gui_elements, &gui_elements_size);
        CheckAndDrawError(ERROR);
        ERROR = Remove_Element_Handler(gui_elements, &gui_elements_size);
        CheckAndDrawError(ERROR);
        // Print_Ele_Array();
        ERROR = Save_Handler(gui_elements, gui_elements_size);
        CheckAndDrawError(ERROR);
        Get_Selected_Element(gui_elements, gui_elements_size);

        EndDrawing();
    }
}
