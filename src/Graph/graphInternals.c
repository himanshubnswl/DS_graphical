//
// Created by lhbdawn on 29-09-2025.
//
#include "graphInternals.h"

#include <string.h>

Graph_Node * root = nullptr;

int Add_Graph_Node(int data, Graph_Node * parent, size_t weight) {
    Graph_Node * newNode = malloc(sizeof(Graph_Node));

    if (newNode == nullptr) {
        return BAD_ALLOC;
    }

    newNode->data = data;
    newNode->outgoing_edges_index = -1;
    newNode->radius = DEFAULT_RADIUS;
    newNode->color = WHITE;

    if (parent == nullptr) {

        if (root != nullptr) {
            return ADD_ERROR;
        }

        root = newNode;
        newNode->pos_x = (GetScreenWidth()/50) * 1;
        newNode->pos_y = (GetScreenHeight()/50) * 25;
        newNode->parentNode = nullptr;
    }

    else {
        parent->outgoing_edges[++(parent->outgoing_edges_index)]->node = newNode;
        parent->outgoing_edges[(parent->outgoing_edges_index)]->weight = weight;
        newNode->pos_x = parent->pos_x + 50;
        newNode->pos_y = parent->pos_y * (parent->outgoing_edges_index + 1);
        newNode->parentNode = parent;
    }
    return SUCCESS;
}

int clear_node_adjacency(Graph_Node * node) {
    Graph_Node * stack[20] = {nullptr};
    int SP = -1;
    stack[++SP] = node;

    Graph_Node * bufferNode;
    while (SP != -1) {
        bufferNode = stack[SP--];

        for (size_t i = 0; i <= node->outgoing_edges_index; i++) {
            stack[++SP] = node->outgoing_edges[i]->node;
        }
    }
}

int Remove_Graph_Node(Graph_Node * node) {
    Graph_Node * parentNode = node->parentNode;


    if (parentNode == nullptr) { //case when node is the root
        free(node);
        return SUCCESS;
    }

    for (size_t i = 0; i <= parentNode->outgoing_edges_index; i++) {
        if (parentNode->outgoing_edges[i]->node == node) {
            if (i == parentNode->outgoing_edges_index) {
                parentNode->outgoing_edges_index--;
            }
            else {
                for (size_t j = i; j < parentNode->outgoing_edges_index; j++) {
                    parentNode->outgoing_edges[j] = parentNode->outgoing_edges[j+1];
                }
                parentNode->outgoing_edges_index--;
            }
        }
    }

        free(node);
        return SUCCESS;
}

Graph_Node * Get_Graph_Root() {
    if (root != nullptr) {
        return root;
    }
    else {
        return nullptr;
    }
}

Graph_Node * BST_Iterate_Graph(bool ResetFlag) { //func upon calling will return graph node, needs to called repeatedly
    static size_t func_called_num;
    if (ResetFlag == true) {
        func_called_num = 0;
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