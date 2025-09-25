//
// Created by lhbdawn on 05-09-2025.
//
#ifndef  ERROR_H
#define ERROR_H


#include <raygui.h>
#include <raylib.h>
#include <debug.h>
#define DEBUG
enum ERROR_HANDLER {
    ADD_ERROR = -1,
    REMOVE_ERROR = -2,
    NOT_INT = -3,
    EMPTY_TREE = -4,
    SUCCESS = -5,
    ZERO_DATA = -6,
    NOTHING_TO_SAVE = -7 ,
    VALUE_NOT_FOUND = -8
};

#ifdef ERROR_IMPLEMENTATION
void CheckAndDrawError(enum ERROR_HANDLER error) {
    static char * message;
    switch (error) {
        case ADD_ERROR:
            message = "Check value, only Integers allowed";
            break;

        case REMOVE_ERROR:
            message = "Enter valid number to remove";
            break;

        case NOT_INT:
            message = "Only Integers are allowed";
            break;

        case EMPTY_TREE:
            message = "The tree is Empty";
            break;

        case SUCCESS:
            message = nullptr;
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

        default:
            message = nullptr;
    }


#ifdef DEBUG
    DEBUG_PRINTF(message);
#endif


    if (message != nullptr) {
        Rectangle errorBox = {
            .x = (GetScreenWidth()/100) * 2,
            .y = (GetScreenHeight()/100) * 80,
            .width = MeasureText(message, 35) + 100,
            .height = 100
        };
        GuiTextBox(errorBox, message, 35, false);
    }
}
#endif

#endif