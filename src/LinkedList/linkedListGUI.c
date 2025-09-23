#include "../DrawingStuff/linkedListGUI.h"

void errorHandler() {
    switch (error_message) {
        case REMOVE_ERROR:
            DrawText("no element selected", (GetScreenWidth() - (GetScreenWidth()/2)), (GetScreenHeight() - 100), 20, RED);
            break;
        case ADD_ERROR:
            DrawText("only numbers are allowed", (GetScreenWidth() - (GetScreenWidth()/2)), (GetScreenHeight() - 100), 20, RED);
        default:
            break;

    }
}

int selectElementStatus(Rectangle shape) {
    Vector2 mousePosition = GetMousePosition();
    if ((mousePosition.x >= shape.x &&
        mousePosition.x <= (shape.x + shape.width)) &&
        (mousePosition.y >= shape.y) &&
        (mousePosition.y <= (shape.y + shape.height))) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // printf("\n event for selection of an element detected");
                return 1;
            }
    }
    else {
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            // printf("\n event for 0 detected");
            error_message = NO_ERROR;
            return -1;
        }
        return 0;
    }
    return 0;
}

void drawLinkedList(int * remove_ele_index) {
    __NODE * iterateNode = getHead();

    int max_elements_row = 0;
    int i = 0; // number of elements, in a row
    int y = 1; // can be thought as the number of rows
    Color color;

    while (iterateNode != NULL) {
        color = WHITE;

        Rectangle shape = { //initializing initial shape of an element
            .x = (GAP_X + ((GAP_X + WIDTH_ELE)* i)),
            .y = (GAP_Y + ((GAP_Y + HEIGHT_ELE) * y)),
            .width = WIDTH_ELE,
            .height = HEIGHT_ELE};

        Vector2 startpos = {    //for line drawing, point 1
        .x = shape.x - GAP_X,
        .y = shape.y + (HEIGHT_ELE/2)};

        Vector2 endpos = {
        .x = shape.x, //for line drawing, point 2
        .y = shape.y + (HEIGHT_ELE/2)};

        if ((shape.x + shape.width) >= GetScreenWidth()) {
            //for when the element crosses the window width
            //increase number of rows and the number of elements in that row to 0
            i  = 0;
            y++;
            shape.x = (GAP_X + ((GAP_X + WIDTH_ELE) * i));
            shape.y = (GAP_Y + ((GAP_Y + HEIGHT_ELE) * y));
            //gibberish to draw lines when element is at the end, draws from point to point
            DrawLineEx(endpos, (Vector2){(endpos.x) , (endpos.y + 50)}, 3, BLACK);
            int pos = (GetScreenWidth()) - (GetScreenWidth()- (2 * sqrt(GetScreenWidth())));
            DrawLineEx((Vector2){(endpos.x) , (endpos.y + 50)}, (Vector2){(pos), (endpos.y + 50)}, 3, BLACK);
            DrawLineEx((Vector2){(pos), (endpos.y + 50)}, (Vector2){(pos), (endpos.y + 100)}, 3, BLACK);
            DrawLineEx((Vector2){(pos), (endpos.y + 100)}, (Vector2){(shape.x), (endpos.y + 100)}, 3, BLACK);
        }

        if (max_elements_row < (i+1)) {
            max_elements_row = i+1;
        }
        int SEStatus = selectElementStatus(shape);
        if (SEStatus == 1) {
            (*remove_ele_index) = (i + 1) + (max_elements_row * (y-1));
        }
        else if (SEStatus == -1) {
            (*remove_ele_index) = 0;
        }
        if ((*remove_ele_index) == ((i + 1) + (max_elements_row * (y - 1)))) {
            color = GREEN;
        }
        //above code is for selecting a element and paiting it green, done by calculation max elsements
        //and then adding them with the next row elements to get the actual index of the element
        //can prolly be done in a better way
        DrawRectangleRec(shape, color);
        DrawRectangleLinesEx(shape, 3, BLACK);
        DrawText(int_to_chars(iterateNode->data),(shape.x + TEXT_TO_ELE_GAP_X), (shape.y + TEXT_TO_ELE_GAP_Y), 18, RED);
        DrawLineEx(startpos, endpos, 3, BLACK);
        //drawing the final rectangles and lines
        i++;
        iterateNode = iterateNode->nextptr;
    }
}

int getInputEle(char * input) {
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
    error_message = NO_ERROR;
    return 1;
}

// void addElementHandler(bool * button_status, char * inputText) {
//     Rectangle addBox = {(GetScreenWidth() - 150), (GetScreenHeight() - 75), 125, 50};
//     Rectangle addInputBox = {(GetScreenWidth() - 300), (GetScreenHeight() - 220), 250, 125};
//
//     if (GuiButton(addBox, "Add Element")) {
//         *button_status = true;
//     }
//     if (*button_status) {
//         int inputState = GuiTextInputBox(addInputBox, nullptr, nullptr, "add", inputText, 6, nullptr);
//         switch (inputState) {
//             case 0: *button_status = false;
//                     break;
//
//             case 1: if (getInput(inputText) == -1) {
//                     error_message = ADD_ERROR;
//                 }
//                     break;
//             default:
//                 break;
//         }
//     }
// }



void removeElementHandler(int * remove_ele_index) {
    Rectangle removeButton = {
        .x = (GetScreenWidth() - 243),
        .y = (GetScreenHeight() - 106),
        .width = 100,
        .height = 75
    };

    if (GuiButton(removeButton, "Remove Element")) {
        if ((*remove_ele_index) == 0) {
            error_message = REMOVE_ERROR;
            return;
        }
        removeNode(*remove_ele_index);
        (*remove_ele_index) = 0;
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
        int remove_ele_index = 0;
        SetTargetFPS(60);
        while (!WindowShouldClose()) {
            BeginDrawing();

            ClearBackground(DARKGRAY);
            // addElementHandler(&button_status, inputText);
            inputElementHandler(&button_status, inputText, getInputEle);
            removeElementHandler(&remove_ele_index);
            errorHandler();
            drawLinkedList(&remove_ele_index);
            EndDrawing();
        }
    }
