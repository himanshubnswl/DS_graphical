#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raygui.h>
#include "array_internals.h"
#include "../helpers/error.h"

#define DEFAULT_REC_ELE_WIDTH 100
#define DEFAULT_REC_ELE_HEIGHT 75
#define DEFAULT_ELE_COLOR WHITE
#define SELECTED_ELE_WIDTH 125
#define SELECTED_ELE_HEIGHT 100
#define SELECTED_ELE_COLOR GREEN
#define SELECTION_INVALID -1
#define INPUT_TEXT_MAX_SIZE 50
#define MAX_NUM_ELEMENTS 50
#define STARTING_X 50
#define STARTING_Y 75

void Calculate_Shape();
