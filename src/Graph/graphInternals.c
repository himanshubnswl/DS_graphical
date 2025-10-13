//
// Created by lhbdawn on 29-09-2025.
//
#include "graphInternals.h"

#include <string.h>

#include "../helpers/helper.h"

Graph_Node * root = nullptr;

Graph_Node * Add_Graph_Node(int data, Graph_Node * parent, int weight) {
    if (data <= 0 || weight <= 0) { //no -ve or 0 allowed
        return nullptr;
    }
    Graph_Node * newNode = malloc(sizeof(Graph_Node));

    //data which needs to be given in any case for a new node
    newNode->data = data;
    newNode->incoming_edges_index = -1;
    newNode->outgoing_edges_index = -1;

    if (parent == nullptr) {
        //if parent nullptr then make the root node
        root = newNode;
        return newNode;
    }
    else {
        //if newNode is not a root then make sure parent has a edge to newNode
        //and newNode also has a incoming edge to parent
        ( parent->outgoing_edges[++(parent->outgoing_edges_index)] ).node = newNode;
        ( parent->outgoing_edges[(parent->outgoing_edges_index)] ).weight = weight;
        ( newNode->incoming_edges[++(newNode->incoming_edges_index)] ).node = parent;
        ( newNode->incoming_edges[(newNode->incoming_edges_index)] ).weight = weight;
        return newNode;
    }
}

Graph_Node ** Get_DFS_traversal() {
    Graph_Node * stack[MAX_ELEMENTS_NUM] = {nullptr};
    int sp = -1;
    Graph_Node ** traversal = calloc(MAX_ELEMENTS_NUM, sizeof(Graph_Node *));
    int traversal_index = -1;
    if (root == nullptr) return traversal;

    stack[++sp] = root;
    while (sp != -1) {
        Graph_Node * bufferNode = stack[sp--];
        for (int i = bufferNode->outgoing_edges_index; i >= 0; i--) {
            if (visited_array_search(traversal, bufferNode->outgoing_edges[i].node) == false) {
                stack[++sp] = bufferNode->outgoing_edges[i].node;
            }
        }
        traversal[++traversal_index] = bufferNode;
    }
    return traversal;
}

bool visited_array_search(Graph_Node ** visited, Graph_Node * toBeSearched) {
    for (int i = 0; visited[i] != nullptr; i++ ) {
        if (visited[i] == toBeSearched) {
            return true;
        }
    }
    return false;
}

Graph_Node ** Get_Diff(Graph_Node ** first, Graph_Node ** second) {
    Graph_Node ** missingarr = calloc(MAX_ELEMENTS_NUM, sizeof(Graph_Node*));
    size_t i = 0;
    size_t m = 0;

    while (first[i] != nullptr) {
        if (visited_array_search(second, first[i]) == false) {
            missingarr[m++] = first[i];
        }
        i++;
    }

    return missingarr;
}
void printARR(char * id ,Graph_Node ** arr) {
    int i = 0;
    printf("\n %s is: ", id);
    while (arr[i] != nullptr) {
        printf(" %d ", arr[i]->data);
        i++;
    }
    printf("\n");
}

int Remove_Graph_Node(Graph_Node * node) {
    Graph_Node ** firstarr = Get_DFS_traversal();

    for (int i = 0; i <= node->incoming_edges_index; i++) {
        Graph_Node * parent = node->incoming_edges[i].node;
        for (int j = 0; j <= parent->outgoing_edges_index; j++) {
            if (parent->outgoing_edges[i].node == node) {
                for (int k = j; k < parent->outgoing_edges_index; k++) {
                    parent->outgoing_edges[k] = parent->outgoing_edges[k+1];
                }
                parent->outgoing_edges_index--;
            }
        }
    }
    if (node->incoming_edges_index < 0) {
        //node is determined to be the root
        root = nullptr;
    }

    Graph_Node ** secondarr = Get_DFS_traversal();
    Graph_Node ** missingnodes = Get_Diff(firstarr, secondarr);
    printARR("first" , firstarr);
    printARR("second" , secondarr);
    printARR("missingarr" , missingnodes);
    size_t i = 0;
    while (missingnodes[i] != nullptr) {
        missingnodes[i]->data = NON_VALID_NODE_VAL;
        i++;
    }
    free(firstarr);
    free(secondarr);
    free(missingnodes);
    DEBUG_PRINTF("exiting remove function");
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