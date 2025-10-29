//
// Created by lhbdawn on 03-10-2025.
//

#ifndef GRAPHGUI_H
#define GRAPHGUI_H
#include <raylib.h>
#include <raygui.h>
#include <raymath.h>
#include <math.h>
#include "graphInternals.h"
#include <stdio.h>
#include "../helpers/error.h"
#include <stdlib.h>
#include <debug.h>

#define ARROW_LENGTH 25
#define DEBUG
#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 1700
#define TEXT_SIZE_GUI 18
#define TEXT_SPACING_GUI 5
#define DEFAULT_COLOR WHITE
#define DEFAULT_RADIUS 40
#define DEFAULT_LINE_THICKNESS 10
#define TEXT_MAX_LENGTH 20
#define SELECTED_VERT_COLOR GREEN
#define SELECTED_VERT_RADIUS 45
#define NOTIF_FONT_SIZE 25
#define EDGE_SELECTED_COLOR BLUE

#define POS_X_HASH 1314879241
#define POS_Y_HASH 1298101622
#define UNIQUE_ID_HASH 244154495

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
