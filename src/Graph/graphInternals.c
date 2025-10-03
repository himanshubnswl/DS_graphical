//
// Created by lhbdawn on 29-09-2025.
//
#include "graphInternals.h"

Graph_Node ** adjacency_matrix = nullptr;

void initialize_graph() {
    adjacency_matrix = malloc(MAX_ROWS * sizeof(int *));
    adjacency_matrix[0] = malloc(MAX_ROWS * MAX_COLUMNS * sizeof(int));

    for (size_t i = 1; i < MAX_ROWS; i++) {
        adjacency_matrix[i] = adjacency_matrix[0] + i * MAX_COLUMNS;
    }
}

void free_adjacency_matrix() {
    if (adjacency_matrix == nullptr) {
        printf("\nmatrix hasn't been allocated!");
        return;
    }
    free(adjacency_matrix[0]);
    free(adjacency_matrix);
}

Graph_Node ** get_adjacencymatrix() {
    if (adjacency_matrix != nullptr) {
        return adjacency_matrix;
    }
    else {
        printf("\ntrying to return a null adjacency matrix!");
        return nullptr;
    }
}

int add_graph_node() {

}