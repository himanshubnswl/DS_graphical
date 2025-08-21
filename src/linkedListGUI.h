#pragma once

#define RAYGUI_IMPLEMENTATION

#include <raylib.h>
#include <raygui.h>
#include <helper.h>
#include <linkedListInternals.h>

enum error_messages {
    NOTHING = 0,
    REMOVE_ERROR = -2,
    ADD_ERROR = -1
};

#define GAP_X 50
#define WIDTH_ELE 100
#define HEIGHT_ELE 75
#define GAP_Y 25
#define TEXT_TO_ELE_GAP_X 25
#define TEXT_TO_ELE_GAP_Y 25

enum error_messages error_message;