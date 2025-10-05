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


#endif //GRAPHINTERNALS_H
