//
// Created by lhbdawn on 29-09-2025.
//

#ifndef GRAPHINTERNALS_H
#define GRAPHINTERNALS_H
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../helpers/error.h"
#include "../helpers/helper.h"
#include <stdint.h>

#define MAX_ELEMENTS_NUM 50
#define MAX_DELETED_NODES 20
#define NON_VALID_NODE_VAL -10

#define UNIQUE_ID 244154495
#define DATA 3631407781
#define INCOMING_EDGES 1861136447
#define OUTGOING_EDGES 246838193

struct graphNode;
struct AdList;

typedef struct edgelink {
    int unique_id;
    int weight;
}edge_link;

struct AdListItem {
    struct graphNode * node;
    int weight;
};

typedef struct graphNode {
    int unique_id;
    int data;
    int incoming_edges_index;
    struct AdListItem incoming_edges[20];
    int outgoing_edges_index;
    struct AdListItem outgoing_edges[20];
}Graph_Node;

//bool visited_array_search(Graph_Node ** visited, Graph_Node * toBeSearched); //searches for toBeSearched in given array

//adds a node to the graph, makes root node if parent passed as nullptr
//accepts only positive values for weight
//returns nullptr if data || weight <= 0
//else return the newly created node
Graph_Node * Add_Graph_Node(int data, Graph_Node * parent, int weight);

//removes a passed in node by setting the node's value to NON_VALID_VALUE
//freeing of node on the user
//return 1 if node is null
//returns 0 on success
int Remove_Graph_Node(Graph_Node * node);

//returns the root if it's not nullptr
//if nullptr then return nullptr
Graph_Node * Get_Graph_Root();

//adds a Edge between parent and child with defined weight
//return 1 if weight is negative of parent is nullptr
//returns 2 if some edge already exists between parent and child
//returns 0 on success
int Add_Graph_Edge(Graph_Node * parent, Graph_Node * child, int weight);

//removes a edge between parent and child
//returns 1 if parent or child is nullptr
//returns 2 if no edge exists between parent and child
//return 0 on success
int Remove_Graph_Edge(Graph_Node * parent, Graph_Node * child);


int Save_Graph_To_File();

Graph_Node ** Load_Graph_From_File();
//void Free_Edge_Link_List(edge_link ** list);
Graph_Node ** Get_DFS_traversal();


#endif //GRAPHINTERNALS_H
