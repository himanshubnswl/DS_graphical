//
// Created by lhbdawn on 03-10-2025.
//

#ifndef GRAPHGUI_H
#define GRAPHGUI_H
#include <raylib.h>
#include <raygui.h>
#define RAYGUI_IMPLEMENTATION
#include "graphInternals.h"
#include <stdio.h>
#include "../helpers/error.h"
#include <stdlib.h>

#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 1700

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
