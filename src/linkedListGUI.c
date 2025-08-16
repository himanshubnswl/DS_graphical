#define RAYGUI_IMPLEMENTATION

#include <raylib.h>
#include <raygui.h>
#include <helper.h>
#include <linkedListInternals.h>



#define GAP_X 50
#define WIDTH_ELE 100
#define HEIGHT_ELE 75
#define GAP_Y 25
#define TEXT_TO_ELE_GAP_X 25
#define TEXT_TO_ELE_GAP_Y 25

bool selectElementStatus(Rectangle shape) {
    if ((GetMousePosition().x >= shape.x &&
        GetMousePosition().x <= (shape.x + shape.width)) &&
        (GetMousePosition().y >= shape.y) &&
        (GetMousePosition().y <= (shape.y + shape.height))) {
            return true;
    }
    else {
        return false;
    }
}

void drawLinkedList() {
    __NODE * iterateNode = getHead();
    int i = 0;
    int y = 1;
    Color color;
    while (iterateNode != NULL) {
        color = WHITE;
        Rectangle shape = {
            .x = (GAP_X + ((GAP_X + WIDTH_ELE)* i)),
            .y = (GAP_Y + ((GAP_Y + HEIGHT_ELE) * y)),
            .width = WIDTH_ELE,
            .height = HEIGHT_ELE
        };

        Vector2 startpos = {
        .x = shape.x - GAP_X,
        .y = shape.y + (HEIGHT_ELE/2)};

        Vector2 endpos = {
        .x = shape.x,
        .y = shape.y + (HEIGHT_ELE/2)};

        if ((shape.x + shape.width) > GetScreenWidth()) {
            i  = 0;
            y++;
            shape.x = (GAP_X + ((GAP_X + WIDTH_ELE)* i));
            shape.y = (GAP_Y + ((GAP_Y + HEIGHT_ELE) * y));
            //gibberish to draw lines when element is at the end, draws from point to point
            DrawLineEx(endpos, (Vector2){(endpos.x) , (endpos.y + 50)}, 3, BLACK);
            int pos = (GetScreenWidth()) - (GetScreenWidth()- (2 * sqrt(GetScreenWidth())));
            DrawLineEx((Vector2){(endpos.x) , (endpos.y + 50)}, (Vector2){(pos), (endpos.y + 50)}, 3, BLACK);
            DrawLineEx((Vector2){(pos), (endpos.y + 50)}, (Vector2){(pos), (endpos.y + 100)}, 3, BLACK);
            DrawLineEx((Vector2){(pos), (endpos.y + 100)}, (Vector2){(shape.x), (endpos.y + 100)}, 3, BLACK);
        }
        if (selectElementStatus(shape)) {
            color = GREEN;
        }
        DrawRectangleRec(shape, color);
        DrawRectangleLinesEx(shape, 3, BLACK);
        DrawText(int_to_chars(iterateNode->data),(shape.x + TEXT_TO_ELE_GAP_X), (shape.y + TEXT_TO_ELE_GAP_Y), 18, RED);
        DrawLineEx(startpos, endpos, 3, BLACK);
        i++;
        iterateNode = iterateNode->nextptr;
    }
}

int getInput(char * input) {
    int i = 0;
    int value_to_input = 0;
    while (input[i] != '\0') {
        if ((input[i] < '0') || (input[i] >'9')) {
            return -1;
        }
        else {
            value_to_input = (value_to_input * 10) + (input[i] - '0');
            i++;
        }
    }
    addNode(value_to_input);
    return 1;
}

void addElementHandler(bool * button_status, char * inputText) {
    Rectangle addBox = {(GetScreenWidth() - 150), (GetScreenHeight() - 75), 125, 50};
    Rectangle addInputBox = {(GetScreenWidth() - 300), (GetScreenHeight() - 220), 250, 125};

    if (GuiButton(addBox, "Add Element")) {
        *button_status = true;
    }
    if (*button_status) {
        int inputState = GuiTextInputBox(addInputBox, nullptr, nullptr, "add", inputText, 6, nullptr);
        switch (inputState) {
            case 0: *button_status = false;
                    break;

            case 1: getInput(inputText);
                    break;

            default:
                break;
        }
    }
}

void removeElementHandler() {
    Rectangle removeButton = {
        .x = (GetScreenWidth() - 300),
        .y = (GetScreenHeight() - 75),
        .width = 125,
        .height = 50
    };

    if (GuiButton(removeButton, "Remove Element")) {
        removeNodeLast();
    }
}

int main() {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);

        int initializeWidth = 1700;
        int initializeHeight = 900;

        InitWindow(initializeWidth, initializeHeight, "LinkedListGUI");

        bool button_status = false;
        char * inputText = (char *)malloc(6 * sizeof(char));
        *inputText = 0;
        while (!WindowShouldClose()) {
            BeginDrawing();

            ClearBackground(DARKGRAY);
            addElementHandler(&button_status, inputText);
            removeElementHandler();
            drawLinkedList();
            EndDrawing();
        }
    }
