//
// Created by lhbdawn on 05-09-2025.
//
#ifndef  ERROR_H
#define ERROR_H

#include <debug.h>

enum ERROR_HANDLER {
    ADD_ERROR = -1,
    REMOVE_ERROR = -2,
    NOT_INT = -3,
    EMPTY_TREE = -4,
    SUCCESS = -5,
    ZERO_DATA = -6,
    NOTHING_TO_SAVE = -7 ,
    VALUE_NOT_FOUND = -8,
    FULL = -9,
    BAD_ALLOC = -10,
    NO_SELECTION = -11,
    ALREADY_EXISTS = -12,
    NO_EDGE = -13,
    SAVE_FAIL = -14,
    LOAD_FAIL = -15,
    SAVE_SUCCESS = -16,
    LOAD_SUCCESS = -17
};

#ifdef ERROR_IMPLEMENTATION
void CheckAndDrawError(enum ERROR_HANDLER error) {
    static char * message;
    switch (error) {
        case ADD_ERROR:
            message = "adding element not possible";
            break;

        case REMOVE_ERROR:
            message = "removing element not possible";
            break;

        case NOT_INT:
            message = "Only Integers are allowed";
            break;

        case EMPTY_TREE:
            message = "The tree is Empty";
            break;

        case ZERO_DATA:
            message = "Zeros are not allowed";
            break;

        case NOTHING_TO_SAVE:
            message = "Empty tree cannot be saved";
            break;

        case VALUE_NOT_FOUND:
            message = "value couldn't be found";
            break;

        case FULL:
            message = "Something is Full";
            break;

        case BAD_ALLOC:
            message = "allocation failed";
            break;

        case NO_SELECTION:
            message = "no element selected";
            break;

        case ALREADY_EXISTS:
            message = "field already exists";
            break;

        case NO_EDGE:
            message = "field doesn't exist";
            break;

        case LOAD_FAIL:
            message = "loading the file failed";
            break;

        case SAVE_FAIL:
            message = "saving the file failed";
            break;

        case SAVE_SUCCESS:
            message = "file saved!";
            break;

        case LOAD_SUCCESS:
            message = "file loaded!";
            break;

        default:
            message = nullptr;
    }

    static bool show_error = false;
    if (message != nullptr) {
        show_error = true;
    }
    if(show_error) {
        static char * V_error;
        if (message != nullptr) V_error = message;
#ifdef DEBUG
        DEBUG_PRINTF(V_error);
#endif
        Rectangle const errorBox = {
            .x = (GetScreenWidth()/100) * 2,
            .y = (GetScreenHeight()/100) * 80,
            .width = 600,
            .height = 100
        };
        Rectangle const remove_button = {
            .x = errorBox.x + (errorBox.width - 50),
            .y = errorBox.y + 10,
            .width = 25,
            .height = 25};
        int prev = GuiGetStyle(DEFAULT, TEXT_SIZE);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 45);
        GuiTextBox(errorBox, V_error, 256, false);
        GuiSetStyle(DEFAULT, TEXT_SIZE, prev);
        if(GuiButton(remove_button, "X")) show_error = false;
    }
}
#endif

#endif