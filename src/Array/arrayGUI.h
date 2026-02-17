#pragma once

#define ERROR_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <debug.h>
#include <raygui.h>
#include "../helpers/error.h"
#include "../helpers/helper.h"

// #define DEFAULT_REC_ELE_WIDTH 100
// #define DEFAULT_REC_ELE_HEIGHT 75
// #define DEFAULT_ELE_COLOR WHITE
// #define DEFAULT_REC_ELE_BORDER_LINE_THICKNESS 5
// #define REC_TEXT_OFFSET_X 35
// #define REC_TEXT_OFFSET_Y 25
// #define SELECTED_ELE_WIDTH 125
// #define SELECTED_ELE_HEIGHT 100
// #define SELECTED_ELE_COLOR GREEN
// #define SELECTION_INVALID -1
// #define INPUT_TEXT_MAX_SIZE 50
// #define MAX_NUM_ELEMENTS 50
// #define STARTING_X 50
// #define STARTING_Y 75
// #define ROW_GAP 50
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

//calculate shape for an array
void Calculate_Shape(gui_element* gui_elements, size_t gui_elements_size);
//selection logic for an element
int Get_Selected_Element(gui_element* gui_elements, size_t gui_elements_size);
//draws the final array
void Draw_Array(const gui_element* const gui_elements, size_t gui_elements_size);
// prints the array
void Print_Ele_Array(const gui_element* const gui_elements, size_t gui_elements_size);
//remove button and logic
int Remove_Element_Handler(gui_element* gui_elements, size_t* gui_elements_size);
//add button handler and logic
int Add_Element_Handler(gui_element* gui_elements, size_t* gui_elements_size);
void Debug_Mode(gui_element *gui_elements, size_t gui_elements_size);