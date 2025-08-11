#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include <stdbool.h>
#include <raygui.h>
#include <array_internals.h>
int checkCollisionMouse(Rectangle collision_box);
void collisionHandler(Rectangle collision_box);

void drawArray(void) 
{
    for (size_t i = 0; i <= getSize() - 1; i++) //last i.e. getelement return +1 the actual last
    {
        char * value_in_char = int_to_chars(getElement(i));
        if (getElement(i) == 0) {
            break;
        }
        if (i == 0)
        {
            DrawRectangle(50,50, 100, 50, WHITE); //to get the first one drawn
            DrawText(value_in_char, 90, 65, 16, BLACK);
            DrawRectangleLines(50, 50, 100, 50, BLACK);
        }
        else
        {
            DrawRectangle(((50 * (i + 1)) + (50 * i)), 50, 100, 50, WHITE); //logic to draw further values
            DrawText(value_in_char, (((50 * (i + 1)) + (50 * i)) + 40), 65, 16, BLACK);
            DrawRectangleLines(((50 * (i + 1)) + (50 * i)), 50, 100, 50, BLACK);
            collisionHandler((Rectangle) {((50 * (i + 1)) + (50 * i)), 50, 100, 50});
        }

        free(value_in_char);
    }
}

void addElementHandler(char * text, bool * valid_value, bool * state_input_element) {
    Rectangle add_element_input_box = {(GetScreenWidth() - 300), (GetScreenHeight() - 300), 250, 150};
    Rectangle add_button = {(GetScreenWidth() - 100), (GetScreenHeight() - 50), 75, 45};

        if(GuiButton(add_button, "add_element")) //a lot of logic to draw the add-element fucntions, needs to be broken into multiple functions /todo
        {
            *state_input_element = true; //draws the button, returns 1 or more on click action
        }
        if (*state_input_element == true) {
            bool * secretValue = nullptr;

            const int value = GuiTextInputBox(add_element_input_box, "add-element", "value here", "enter", text, 50, secretValue);
            if(value == 0)
            {
                *state_input_element = false;
            }

            else if (value == 1) {
                int i = 0;
                int value_to_be_inserted = 0;

                while(text[i] != '\0')
                {
                    printf("\n%s", text);
                    const char ch = text[i];
                    if (!((ch >= '0') && (ch <= '9')))
                    {
                        *valid_value = false;
                        break;
                    }
                    else
                    {
                        *valid_value = true;
                        value_to_be_inserted = (value_to_be_inserted * 10) + (text[i] - '0');
                    }
                    i++;
                }
                (*text) = '\0'; //to zero out the value
                if(*valid_value)
                {
                    if (value_to_be_inserted > 0 )
                        insertElement(value_to_be_inserted);
                }
            }
            if (!(*valid_value))
            {
                GuiSetFont((Font){.baseSize = 20});
                GuiDrawText("invalid value, only numbers are accepted", (Rectangle){(GetScreenWidth()/2 - 150), (GetScreenHeight()/2 - 150), 300,300},
                TEXT_ALIGN_CENTER, RED);
            }
        }
}

int checkCollisionMouse(Rectangle collision_box) { //return 1 if collide or 0 if not
    if ((GetMousePosition().x >= collision_box.x) &&
        (GetMousePosition().y >= collision_box.y) &&
        (GetMousePosition().x <= (collision_box.x + collision_box.width)) &&
        (GetMousePosition().y <= (collision_box.y + collision_box.height))
    ) {
        return 1;
    }
    else return 0;
}

void collisionHandler(Rectangle collision_box) {
    if (checkCollisionMouse(collision_box) > 0) {
        DrawRectangleLinesEx(collision_box, 5, BLUE);
    }
}

void removeButtonHandler(void) {
    int value = GuiButton((Rectangle){(GetScreenWidth() - 200), (GetScreenHeight() - 50), 75, 45 }, "remove last");

    if (value > 0) {
        removeElement();
    }
}

int main() {
    bool state_input_element = false;
    bool valid_value = true;
    char text[50] = {0};

    initialize(100);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    InitWindow(1700, 900, "array");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(GRAY);

        addElementHandler(text, &valid_value, &state_input_element);
        removeButtonHandler();
        drawArray();
        EndDrawing();
        
    }
}

