//
// Created by lhbdawn on 29-09-2025.
//
#include "graphInternals.h"

#include <string.h>

#include "../helpers/helper.h"

Graph_Node * root = nullptr;

int Add_Graph_Edge(Graph_Node * parent, Graph_Node * child, int weight) {
    if (weight <= 0 || parent == nullptr) return 1;
    for (int i = 0; i <= parent->outgoing_edges_index; i++) {
        if (parent->outgoing_edges[i].node == child) return 2;
    }
    parent->outgoing_edges[++(parent->outgoing_edges_index)].node = child;
    parent->outgoing_edges[(parent->outgoing_edges_index)].weight = weight;
    child->incoming_edges[++(child->incoming_edges_index)].node = parent;
    child->incoming_edges[child->incoming_edges_index].weight = weight;
    return 0;
}

int Remove_Graph_Edge(Graph_Node * parent, Graph_Node * child) {
    if (parent == nullptr || child == nullptr) {
        return 1;
    }
    if (child->incoming_edges_index == 0) {
        Remove_Graph_Node(child);
        return 0;
    }
    bool found = false;
    for (int i = 0; i <= parent->outgoing_edges_index; i++) {
        if (parent->outgoing_edges[i].node == child) {
            found = true;
            for (int j = i; j < parent->outgoing_edges_index; j++) {
                parent->outgoing_edges[j] = parent->outgoing_edges[j+1];
            }
            parent->outgoing_edges_index--;
        }
    }

    if (found == false) return 2;

    for (int i = 0; i <= child->incoming_edges_index; i++) {
        if (child->incoming_edges[i].node == parent) {
            for (int j = i; j < child->incoming_edges_index; j++) {
                child->incoming_edges[j] = child->incoming_edges[j+1];
            }
            child->incoming_edges_index--;
        }
    }
    return 0;
}

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
    if (node == nullptr) return 1;
    Graph_Node ** firstarr = Get_DFS_traversal();

    for (int i = 0; i <= node->incoming_edges_index; i++) {
        Graph_Node * parent = node->incoming_edges[i].node;
        for (int j = 0; j <= parent->outgoing_edges_index; j++) {
            if (parent->outgoing_edges[j].node == node) {
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
    return 0;
}

Graph_Node * Get_Graph_Root() {
    if (root != nullptr) {
        return root;
    }
    else {
        return nullptr;
    }
}

int Generate_Unique_ID(int * generated_ids, int size_arr) {
    int generated_number = rand();
    for (int i = 0; i <= size_arr ; i++) {
        if (generated_ids[i] == generated_number) {
            i = 0;
            generated_number = rand();
        }
    }
    return generated_number;
}

void Set_Nodes_Unique_IDs(Graph_Node ** list) {
    int i = 0;
    int * generated_ids =  malloc(MAX_ELEMENTS_NUM * sizeof(int));
    int generated_ids_size = -1;
    while (list[i] != nullptr) {
        list[i]->unique_id = Generate_Unique_ID(generated_ids, generated_ids_size);
        generated_ids_size++;
        i++;
    }
    free(generated_ids);
}

int Save_Graph_To_File() {
    FILE * save_file = fopen("./save_file.txt", "w");
    if (save_file == NULL) {
        return 1;
    }
    char * main_string = malloc(1024 * sizeof(char));
    char * buffer_string = malloc(1024 * sizeof(char));
    Graph_Node ** node_list = Get_DFS_traversal();
    Set_Nodes_Unique_IDs(node_list);

    int k = 0;
    while (node_list[k] != nullptr) {
        Graph_Node * node_current = node_list[k];
        main_string[0] = '\0';
        sprintf(buffer_string, "unique id: %d\n"
                               "data: %d\n"
                               "incoming edges: ", node_current->unique_id,
                                                   node_current->data);
        strcat(main_string, buffer_string);
        for (int i = 0; i <= node_current->incoming_edges_index; i++) {
            sprintf(buffer_string, "%d:%d ",
                node_current->incoming_edges[i].node->unique_id,
                node_current->incoming_edges[i].weight);
            strcat(main_string, buffer_string);
        }
        sprintf(buffer_string, "\noutgoing edges: ");
        strcat(main_string, buffer_string);
        for (int i = 0; i <= node_current->outgoing_edges_index; i++) {
            sprintf(buffer_string, "%d:%d ",
                node_current->outgoing_edges[i].node->unique_id,
                node_current->outgoing_edges[i].weight);
            strcat(main_string, buffer_string);
        }
        sprintf(buffer_string, "\n\n");
        strcat(main_string, buffer_string);
        fputs(main_string, save_file);
        k++;
    }
    free(main_string);
    free(buffer_string);
    free(node_list);
    fclose(save_file);
    return 0;
}

int Load_Graph_From_File() {
    FILE * load_from_file = fopen("./save_file.txt", "r");
    if (load_from_file == NULL) return 1;
    char * string_buffer = malloc(sizeof(char) *  1024);
    char * key = malloc(sizeof(char) * 256);
    char * value = malloc(sizeof(char) * 256);
    Graph_Node ** list = calloc(MAX_ELEMENTS_NUM, sizeof(Graph_Node *));
    int list_size = -1;
    while (fgets(string_buffer, 1024, load_from_file)) {
        key = strtok(string_buffer, ":");
        printf("\n%s", key);
        switch (key) {
            case "unique id":
                value = strtok(NULL, "\n");
                printf("\n%s", value);
                Graph_Node * new_node = malloc(sizeof(Graph_Node));
                new_node->unique_id = chars_to_int(value);
                break;

            case "data":
                value = strtok(NULL, "\n");
                printf("\n%s", value);
                new_node->data = chars_to_int(value);
                break;

            case "incoming edges":
                break;

            default:
                return 1;
        }
    }
    return 0;
}