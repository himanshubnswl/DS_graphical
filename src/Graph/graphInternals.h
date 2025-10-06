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

#define MAX_ELEMENTS_NUM 50
#define MAX_DELETED_NODES 20

struct graphNode;
struct AdList;

struct AdListItem {
    struct graphNode * node;
    unsigned int weight;
};

typedef struct graphNode {
    int index;
    int data;
    int incoming_edges_index;
    struct AdListItem * incoming_edges[20];
    int outgoing_edges_index;
    struct AdListItem * outgoing_edges[20];
}Graph_Node;

bool visited_array_search(Graph_Node ** visited, Graph_Node * toBeSearched);
Graph_Node * Add_Graph_Node(int data, Graph_Node * parent, size_t weight);
int Remove_Graph_Node(Graph_Node * node);
Graph_Node * Get_Graph_Root();



#endif //GRAPHINTERNALS_H
