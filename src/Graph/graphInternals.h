//
// Created by lhbdawn on 29-09-2025.
//

#ifndef GRAPHINTERNALS_H
#define GRAPHINTERNALS_H
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 50;
#define MAX_COLUMNS 50;

typedef struct graphNode {
    int data;
    int pos_x;
    int pos_y;
    Color color;
}Graph_Node;
#endif //GRAPHINTERNALS_H
