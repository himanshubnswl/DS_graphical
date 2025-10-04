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

typedef struct graphNode {
    int index;
    int data;
    int pos_x;
    int pos_y;
    Color color;
}Graph_Node;

typedef struct Vertex {
    Graph_Node * node;
    size_t weight;
};

void initialize_graph();
void free_adjacency_matrix();
Graph_Node ** get_adjacencymatrix();
int add_graph_node(int data);

#endif //GRAPHINTERNALS_H
