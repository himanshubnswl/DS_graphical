//
// Created by lhbdawn on 03-10-2025.
//

#ifndef GRAPHGUI_H
#define GRAPHGUI_H
#include <raylib.h>
#include <raygui.h>
#include "graphInternals.h"
#include <stdio.h>
#include "../helpers/error.h"
#include <stdlib.h>
#include <debug.h>

#define DEBUG
#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 1700
#define FONT_SIZE 18
#define FONT_SPACING 5
#define DEFAULT_COLOR WHITE
#define DEFAULT_RADIUS 40
#define DEFAULT_LINE_THICKNESS 10
#define TEXT_MAX_SIZE 20
#define SELECTED_VERT_COLOR GREEN
#define SELECTED_VERT_RADIUS 45

typedef struct Edge {
    Graph_Node * start;
    Graph_Node * end;
}Edge;

typedef struct Vertex {
    Vector2 pos;
    Graph_Node * node;
    Color color;
    int radius;
}Vertex;
#endif //GRAPHGUI_H
