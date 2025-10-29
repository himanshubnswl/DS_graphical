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

bool Search_Stack(Graph_Node ** stack, Graph_Node * key_node, int sp) {
    for (int i = 0; i <= sp; i++) {
        if (stack[i] == key_node) return true;
    }
    return false;
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
            if (visited_array_search(traversal, bufferNode->outgoing_edges[i].node) == false && Search_Stack(stack, bufferNode->outgoing_edges[i].node, sp) == false) {
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
/*generates unique id , keeps track of previoudly generated ids and makes sure that no previously used value is used */
//returns the generated unique id
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

//sets the unique ids for all Graph_Nodes in a array of graph_node
//keeps track of generated ids to make sure no values are repeated
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

/*saves the graph with a very particular format in save_file
 *any changes to the format are volatile and not recommended
 * 0 on success, 1 on failing
 */
int Save_Graph_To_File() {
    FILE * save_file = fopen("./save_file.txt", "w");
    if (save_file == NULL) {
        return 1;
    }

    Graph_Node ** node_list = Get_DFS_traversal();
    if (node_list[0] == nullptr) {
        fclose(save_file);
        return 1;
    }


    char * main_string = malloc(1024 * sizeof(char));
    char * buffer_string = malloc(1024 * sizeof(char));
    Set_Nodes_Unique_IDs(node_list);


    int k = 0;
    while (node_list[k] != nullptr) {
        Graph_Node * node_current = node_list[k];
        DEBUG_PRINTF(node_current->unique_id);
        DEBUG_PRINTF(node_current->data);
        main_string[0] = '\0';
        sprintf(buffer_string, "unique id:%d\n"
                               "data:%d\n"
                               "incoming edges:", node_current->unique_id,
                                                  node_current->data);
        strcat(main_string, buffer_string);
        for (int i = 0; i <= node_current->incoming_edges_index; i++) {
            sprintf(buffer_string, "%d:%d ",
                node_current->incoming_edges[i].node->unique_id,
                node_current->incoming_edges[i].weight);
            strcat(main_string, buffer_string);
        }
        sprintf(buffer_string, "\noutgoing edges:");
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

/*get integer value from a substring start <= bounds < end
 * return the integer value from the string
 */
int Get_Value_From_Substring(char * string, unsigned int start, unsigned int end) {
    char sub_string[20];
    int sub_string_size = 0;

    for (int i = start; i < end; i++) {
        sub_string[sub_string_size] = string[i];
        sub_string_size++;
    }

    sub_string[sub_string_size] = '\0';
    return chars_to_int(sub_string);
}

/*takes a formatted string and makes a list of edge_link containing
 *individual links for a particular node
 * the returned list needs to be free
 * and the elements inside the list need to individually freed as well
 */
edge_link ** Add_Edge_From_String(char * string) {
    edge_link ** edge_list = calloc(MAX_ELEMENTS_NUM, sizeof(edge_link*));
    if (string == nullptr) return edge_list;

    int edge_list_size = -1;
    unsigned int start = 0;
    unsigned int end = 0;
    bool set_start = false;
    bool set_weight_flag = false;
    bool value_is_valid;

    int i = 0;
    while (string[i] != '\0') {
        value_is_valid = false;

        if (string[i] <= '9' && string[i] >= '0') {
            value_is_valid = true;
            if (set_start == false) {
                start = i;
                set_start = true;
            }
        }
        else if (string[i] == ':') {
            value_is_valid = true;
            edge_link * new_link = malloc(sizeof(edge_link));
            edge_list[++edge_list_size] = new_link;
            end = i;
            printf("\nend is: %d, start is: %d", end, start);
            edge_list[edge_list_size]->unique_id = Get_Value_From_Substring(string, start, end);
            printf("\nedge_list_unique_id: %lu", edge_list[edge_list_size]->unique_id);
            set_weight_flag = true;
            set_start = false;
        }
        else if (string[i] == ' ') {
            value_is_valid = true;
            if (set_weight_flag == true) {
                end = i;
                printf("\nend is: %d, start is: %d", end, start);
                edge_list[edge_list_size]->weight = Get_Value_From_Substring(string, start, end);
                printf("\nedge_list_weight: %lu", edge_list[edge_list_size]->weight);
                set_weight_flag = false;
                set_start = false;
            }
        }
        if (value_is_valid == false) {
            Free_Edge_Link_List(edge_list);
            return nullptr;
        }
        i++;
    }
    return edge_list;
}

//searches for a node in a list of graph_nodes
//returns the node if found or retuns nullptr if fails
Graph_Node * Search_And_Return_Node(Graph_Node ** list, int unique_key) {
    int i = 0;
    while (list[i] != nullptr) {
        if (list[i]->unique_id == unique_key) {
            return list[i];
        }
        i++;
    }
    return nullptr;
}

//takes in a node and attaches the adjacent nodes to the parent node by using their unique ids
//searches the unique id in the list and then returns the associated node which links to the parent
//return 0 on success
int Attach_Links_To_Node(Graph_Node * node, edge_link ** incoming_links, edge_link ** outgoing_links, Graph_Node ** list) {
    node->outgoing_edges_index = -1;
    node->incoming_edges_index = -1;

    int i = 0;
    while (incoming_links[i] != nullptr) {
        node->incoming_edges[++(node->incoming_edges_index)].node = Search_And_Return_Node(list , incoming_links[i]->unique_id);
        node->incoming_edges[node->incoming_edges_index].weight = incoming_links[i]->weight;
        i++;
    }
    i = 0;
    while (outgoing_links[i] != nullptr) {
        node->outgoing_edges[++(node->outgoing_edges_index)].node = Search_And_Return_Node(list , outgoing_links[i]->unique_id);
        node->outgoing_edges[node->outgoing_edges_index].weight = outgoing_links[i]->weight;
        i++;
    }
    return 0;
}

//frees the edge link, freeing the list and the elements of the list
void Free_Edge_Link_List(edge_link ** list) {
    int i = 0;
    while (list[i] != nullptr) {
        free(list[i]);
        i++;
    }
    free(list);
}

/*gracefully fails the Load_Graph function by freeing up all allocated resources so no memory is leaked */
void Fail_Load_OP(Graph_Node ** list, edge_link *** incoming_link_list, edge_link *** outgoing_link_list, char * string_buffer, FILE * file) {
    int i = 0;
    while (list[i] != nullptr) {
        free(list[i]);
        i++;
    }
    free(list);

    i = 0;
    while (incoming_link_list[i] != nullptr) {
        Free_Edge_Link_List(incoming_link_list[i]);
        i++;
    }
    free(incoming_link_list);

    i = 0;
    while (outgoing_link_list[i] != nullptr) {
        Free_Edge_Link_List(outgoing_link_list[i]);
        i++;
    }
    free(outgoing_link_list);

    free(string_buffer);
    fclose(file);
}

/*loads the graph from the saved file, returns nullptr if operation fails
 *else return a list to newly created graph_nodes
 * the list needs to freed by the caller
 * uses hasing of strings for better performance
 * has hashes of few strings stored as defines, again for performance*/
Graph_Node ** Load_Graph_From_File() {
    FILE * load_from_file = fopen("./save_file.txt", "r");
    if (load_from_file == NULL) return nullptr;

    char * string_buffer = malloc(sizeof(char) *  1024);

    Graph_Node ** list = calloc(MAX_ELEMENTS_NUM, sizeof(Graph_Node *));
    int list_size = -1;
    edge_link *** incoming_link_list = calloc(MAX_ELEMENTS_NUM, sizeof(edge_link**));
    edge_link *** outgoing_link_list = calloc(MAX_ELEMENTS_NUM, sizeof(edge_link**));


    while (fgets(string_buffer, 1024, load_from_file) != nullptr) {
        char * key = strtok(string_buffer, ":");
        printf("\n%s", key);
        uint32_t hashed_string = Hash_String_FNV(key);
        printf("\nhashed string value : %lu", hashed_string);
        char * value;

        switch (hashed_string) {
            case UNIQUE_ID:
                value = strtok(nullptr, "\n");
                printf("\n uniqe vlaue: %s", value);
                Graph_Node * newNode = malloc(sizeof(Graph_Node));
                if (root == nullptr) root = newNode;
                newNode->unique_id = chars_to_int(value);
                DEBUG_PRINTF(newNode->unique_id);
                list[++list_size] = newNode;
                break;

            case DATA:
                value = strtok(nullptr, "\n");
                printf("\n data vlaue: %s", value);
                newNode->data = chars_to_int(value);
                DEBUG_PRINTF(newNode->data);
                printf("\ndata hit");
                break;

            case INCOMING_EDGES:
                value = strtok(nullptr, "\n");
                printf("\n incoming edge vlaue: %s", value);
                incoming_link_list[list_size] = Add_Edge_From_String(value);
                if (incoming_link_list[list_size] == nullptr) {
                    Fail_Load_OP(list, incoming_link_list, outgoing_link_list, string_buffer, load_from_file);
                    return nullptr;
                }
                printf("\nhit on incoming edges");
                break;

            case OUTGOING_EDGES:
                value = strtok(NULL, "\n");
                printf("\n outoign edge vlaue: %s", value);
                outgoing_link_list[list_size] = Add_Edge_From_String(value);
                if (outgoing_link_list[list_size] == nullptr) {
                    Fail_Load_OP(list, incoming_link_list, outgoing_link_list, string_buffer, load_from_file);
                    return nullptr;
                }
                printf("\nhit on outgoing edges");
                break;

            default:
                printf("\nno hit");
                break;
        }
    }
    DEBUG_PRINTF("line 383 made it across");
    for (int i = 0; i <= list_size; i++) {
        Attach_Links_To_Node(list[i], incoming_link_list[i], outgoing_link_list[i], list);
        Free_Edge_Link_List(incoming_link_list[i]);
        Free_Edge_Link_List(outgoing_link_list[i]);
        DEBUG_PRINTF("do we return?");
    }

    free(incoming_link_list);
    free(outgoing_link_list);
    free(string_buffer);
    fclose(load_from_file);
    return list;
}