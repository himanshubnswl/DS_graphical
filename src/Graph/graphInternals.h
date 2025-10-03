//
// Created by lhbdawn on 29-09-2025.
//

#ifndef GRAPHINTERNALS_H
#define GRAPHINTERNALS_H
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../helpers/error.h"

#define MAX_ROWS 50;
#define MAX_COLUMNS 50;
#define MAX_DELETED_NODES 20;
#define DEFAULT_RADIUS 20;

typedef struct graphNode {
    int index;
    int data;
    int pos_x;
    int pos_y;
    int radius;
    Color color;
    int adjacency_list_index;
    struct graphNode * adjacency_list[20];
}Graph_Node;

void initialize_graph();
void free_adjacency_matrix();
Graph_Node ** get_adjacencymatrix();
int add_graph_node(int data);

#endif //GRAPHINTERNALS_H
