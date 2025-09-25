
#include "helper.h"

#include "raygui.h"



char * int_to_chars(int number)
{
    char * result = (char *)malloc(sizeof(char) * 6); //6 to accomodate the EOL char
    for (size_t i = 5; i >= 0 ; i--)
    {
        if ((number/(int)pow(10,i)))
        {
            int k = i;
            for (size_t j = 0; j <= i; j++) {
                const int inter_num = (number/(int)pow(10, k)) % 10;
                result[j] = inter_num + '0';
                result[j + 1] = '\0'; //adding a EOL char manually
                k--;
            }
            return result;
        }
    }
    return nullptr;
}

int chars_to_int(char * text) {
    size_t i = 0;
    int value = 0;
    while (text[i] != '\0') {
#ifdef DEBUG
        DEBUG_PRINTF(text);
#endif
        char ch = text[i];
        if ((ch <= '9') && (ch >= '0')) {
            value = (value * 10 ) + (ch - '0');
#ifdef DEBUG
            DEBUG_PRINTF(value);
#endif
        }
        else
            return NOT_INT;
        i++;
    }
    return value;
}

int removeElementHandler(int (*removeElementInDS)(int)) {
    static bool dialogue_box_status  = false;
    static char inputText[50];
    static enum ERROR_HANDLER error;


    Rectangle const removeButton = {
        .x = (GetScreenWidth() - 243),
        .y = (GetScreenHeight() - 106),
        .width = 100,
        .height = 75
    };

    Rectangle const dialogueBox = {
        .x = GetScreenWidth() - 230,
        .y = GetScreenHeight() - 250,
        .width = 200,
        .height = 127};

    int result = -2;

    if (GuiButton(removeButton, "remove\nelement")) {
        (dialogue_box_status) = true;
    }
    if (dialogue_box_status) {
        result = GuiTextInputBox(dialogueBox,nullptr, "enter element", "remove", inputText, 10, nullptr);
    }
    switch (result) {
        case -1:
            return error;
            break;
        case 0: (dialogue_box_status) = false;
            return SUCCESS;
            break;
        case 1:
            error = removeElementInDS(chars_to_int(inputText));
            return error;
            break;
        default:
            break;
    }
}



int inputElementHandler(char * input_text, getInput addElement) {
    static bool dialogue_box_status  = false;
    static enum ERROR_HANDLER error;

    Rectangle const addButton = {
        .x = GetScreenWidth() - 129,
        .y = GetScreenHeight() - 106,
        .width = 100,
        .height = 75};

    Rectangle const dialogueBox = {
        .x = GetScreenWidth() - 230,
        .y = GetScreenHeight() - 250,
        .width = 200,
        .height = 127};

    int result = -2;

    if (GuiButton(addButton, "add\nelement")) {
        (dialogue_box_status) = true;
    }
    if (dialogue_box_status) {
        result = GuiTextInputBox(dialogueBox,nullptr, "enter element", "add", input_text, 10, nullptr);
    }

    switch (result) {
        case -1:
            return error;
            break;
        case 0: (dialogue_box_status) = false;
            return SUCCESS;
            break;
        case 1:
            error = addElement(input_text);
            return error;
            break;
        default:
            break;
    }
}
