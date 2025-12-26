#define RAYGUI_IMPLEMENTATION
#include "linkedListGUI.h"


enum ERROR_HANDLER ERROR;
typedef struct gui_element {
    int data;
    Rectangle shape;
    Color color;
}gui_element;

constexpr int DEFAULT_REC_ELE_WIDTH = 100;
constexpr int DEFAULT_REC_ELE_HEIGHT = 75;
constexpr Color DEFAULT_ELE_COLOR = WHITE;
constexpr int DEFAULT_REC_ELE_BORDER_LINE_THICKNESS = 5;
constexpr int REC_TEXT_OFFSET_X = 35;
constexpr int REC_TEXT_OFFSET_Y = 25;
constexpr int SELECTED_ELE_WIDTH = 125;
constexpr int SELECTED_ELE_HEIGHT = 100;
constexpr Color SELECTED_ELE_COLOR = GREEN;
constexpr int SELECTION_INVALID = -1;
constexpr int INPUT_TEXT_MAX_SIZE = 50;
constexpr int MAX_NUM_ELEMENTS = 50;
constexpr int STARTING_X = 50;
constexpr int STARTING_Y = 75;
constexpr int ROW_GAP = 50;
constexpr int INTER_ELEMENT_GAP = 25;
constexpr int LINES_THICKNESS = 10;
constexpr Color LINES_COLOR = RED;


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
    return selected_index;
}

void Draw_Lines() {
    for (int i = 1; i < gui_elements_size; i++) {
        if (gui_elements[i-1].shape.y != gui_elements[i].shape.y) {
            Vector2 line1_sp = {
                .x = gui_elements[i-1].shape.x,
                .y = gui_elements[i-1].shape.y + (gui_elements[i-1].shape.height/2)};
            Vector2 line1_ep = {
                .x = gui_elements[i-1].shape.x + ((GetScreenWidth()-(gui_elements[i-1].shape.x + gui_elements[i-1].shape.width))/2),
                .y = line1_sp.y};
            Vector2 line2_ep = {
                .x = line1_ep.x,
                .y = (gui_elements[i-1].shape.y + gui_elements[i-1].shape.height) + ((gui_elements[i].shape.y - (gui_elements[i-1].shape.y + gui_elements[i-1].shape.height))/2)};
            Vector2 line3_ep = {
                .x = gui_elements[i].shape.x/2,
                .y = line2_ep.y};
            Vector2 line4_ep = {
                .x = line3_ep.x,
                .y = gui_elements[i].shape.y + (gui_elements[i].shape.height/2)};
            Vector2 line5_ep = {
                .x = gui_elements[i].shape.x,
                .y = line4_ep.y};

            DrawLineEx(line1_sp, line1_ep, LINES_THICKNESS, LINES_COLOR);
            DrawLineEx(line1_ep, line2_ep, LINES_THICKNESS, LINES_COLOR);
            DrawLineEx(line2_ep, line3_ep, LINES_THICKNESS, LINES_COLOR);
            DrawLineEx(line3_ep, line4_ep, LINES_THICKNESS, LINES_COLOR);
            DrawLineEx(line4_ep, line5_ep, LINES_THICKNESS, LINES_COLOR);
        }
        else {
            Vector2 startpoint = {
                .x = gui_elements[i-1].shape.x + gui_elements[i-1].shape.width,
                .y = gui_elements[i-1].shape.y + (gui_elements[i-1].shape.height/2)};
            Vector2 endpoint = {
                .x = gui_elements[i].shape.x,
                .y = gui_elements[i].shape.y + (gui_elements[i].shape.height/2)};

            DrawLineEx(startpoint, endpoint, LINES_THICKNESS, LINES_COLOR);
        }
    }
}

void Draw_Array() {
    Draw_Lines();
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
    int row = 1;
    for (int i = 0; i < gui_elements_size; i++) {
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
                .x = gui_elements[i-1].shape.x + DEFAULT_REC_ELE_WIDTH + INTER_ELEMENT_GAP,
                .y = gui_elements[i-1].shape.y,
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
        ERROR = Remove_Element_Handler();
        CheckAndDrawError(ERROR);
        Get_Selected_Element();

        EndDrawing();
    }
}
