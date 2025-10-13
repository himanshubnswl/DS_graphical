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
#define NON_VALID_NODE_VAL -10

struct graphNode;
struct AdList;

struct AdListItem {
    struct graphNode * node;
    int weight;
};

typedef struct graphNode {
    int index;
    int data;
    int incoming_edges_index;
    struct AdListItem incoming_edges[20];
    int outgoing_edges_index;
    struct AdListItem outgoing_edges[20];
}Graph_Node;

bool visited_array_search(Graph_Node ** visited, Graph_Node * toBeSearched); //searches for toBeSearched in given array
Graph_Node * Add_Graph_Node(int data, Graph_Node * parent, int weight);      //adds a graph node and return it, to set parent pass in nullptr to parent
int Remove_Graph_Node(Graph_Node * node);                                    //removes a node by setting the node->data to NON_VALID_NODE_VAL
Graph_Node * Get_Graph_Root();                                               //return the graph's root



#endif //GRAPHINTERNALS_H
