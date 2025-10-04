//
// Created by lhbdawn on 29-09-2025.
//
#include "graphInternals.h"

#include <string.h>

Graph_Node * root = nullptr;

int Add_Graph_Node(int data, Graph_Node * parent, size_t weight) {
    Graph_Node * newNode = malloc(sizeof(Graph_Node));
    if (newNode == nullptr) {
        return ADD_ERROR;
    }

    newNode->data = data;
    newNode->incoming_edges_index = -1;
    newNode->outgoing_edges_index = -1;

    if (parent == nullptr) {
        return SUCCESS;
    }
    else {
        ( parent->outgoing_edges[++(parent->outgoing_edges_index)] )->node = newNode;
        ( parent->outgoing_edges[++(parent->outgoing_edges_index)] )->weight = weight;
        ( newNode->incoming_edges[++(newNode->incoming_edges_index)] )->node = parent;
        ( newNode->incoming_edges[++(newNode->incoming_edges_index)] )->weight = weight;
        return SUCCESS;
    }
}

int Remove_Graph_Node(Graph_Node * node) {

}

Graph_Node * Get_Graph_Root() {
    if (root != nullptr) {
        return root;
    }
    else {
        return nullptr;
    }
}




// Graph_Node ** adjacency_matrix = nullptr;
// int current_max_index = -1;
// size_t deleted_index_pointer = -1;
// static int * deleted_indices;
//
// void initialize_graph() {
//     adjacency_matrix = malloc(MAX_ROWS * sizeof(int *));
//     adjacency_matrix[0] = malloc(MAX_ROWS * MAX_COLUMNS * sizeof(int));
//     memset(adjacency_matrix[0], INT_MAX, MAX_ROWS * MAX_COLUMNS * sizeof(int));
//
//     deleted_indices = malloc(MAX_DELETED_NODES * sizeof(int));
//
//
//     for (size_t i = 1; i < MAX_ROWS; i++) {
//         adjacency_matrix[i] = adjacency_matrix[0] + i * MAX_COLUMNS;
//     }
// }
//
// void free_adjacency_matrix() {
//     if (adjacency_matrix == nullptr) {
//         printf("\nmatrix hasn't been allocated!");
//         return;
//     }
//     free(adjacency_matrix[0]);
//     free(adjacency_matrix);
// }
//
// Graph_Node ** get_adjacencymatrix() {
//     if (adjacency_matrix != nullptr) {
//         return adjacency_matrix;
//     }
//     else {
//         printf("\ntrying to return a null adjacency matrix!");
//         return nullptr;
//     }
// }
//
// int add_deleted_index(int index) {
//     if (deleted_index_pointer == MAX_DELETED_NODES) {
//         return FULL;
//     }
//     deleted_indices[++deleted_index_pointer] = index;
// }
//
// int get_available_index() {
//     if (deleted_index_pointer == -1) {
//         return ++current_max_index;
//     }
//     else {
//         return deleted_indices[deleted_index_pointer--];
//     }
// }
//
// int add_graph_node(int data, int parent_index) {
//     Graph_Node * parentNode; //a function to put here which will give selected parent
//     Graph_Node * newNode = malloc(sizeof(Graph_Node));
//     newNode->data = data;
//     newNode->index = get_available_index(); //function here to get a available index
//
//     adjacency_matrix[newNode->index][newNode->index] = 0;
//     adjacency_matrix[parentNode->index][newNode->index] = 1;
// }