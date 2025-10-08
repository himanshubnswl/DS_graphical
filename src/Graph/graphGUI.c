//
// Created by lhbdawn on 03-10-2025.
//

#include "graphGUI.h"

#include <string.h>

#include "../helpers/helper.h"
Vertex * vertexList[MAX_ELEMENTS_NUM] = {nullptr};
Graph_Node * selected_vertex = nullptr;
int V_List_Top = -1;

Vertex * L_Search_Node(Graph_Node * node) {
    size_t i = 0;
    while (i <= V_List_Top) {
        if (vertexList[i]->node == node) {
            return vertexList[i];
        }
        i++;
    }
    return nullptr;
}

void DrawPointyLine(Vector2 start, Vector2 end, float thick, Color color) {
    Vector2 p1 = {
        .x = end.x-10,
        .y = end.y-10};
    Vector2 p2 = {
        .x = end.x-10,
        .y = end.y+10};

    DrawLineEx(start, end, thick, color);
    DrawLineEx(end, p1, thick, color);
    DrawLineEx(end, p2, thick, color);
}

int DrawEdges(Vertex * vertex) {
    for (int i = 0; i <= vertex->node->outgoing_edges_index; i++) {
        Vertex * dest = L_Search_Node(vertex->node->outgoing_edges[i]->node);
        DrawPointyLine(vertex->pos, dest->pos , DEFAULT_LINE_THICKNESS, DEFAULT_COLOR);
    }
    for (int i = 0; i <= vertex->node->incoming_edges_index; i++) {
        Vertex * dest = L_Search_Node(vertex->node->incoming_edges[i]->node);
        DrawPointyLine(vertex->pos, dest->pos , DEFAULT_LINE_THICKNESS, DEFAULT_COLOR);
    }
    return SUCCESS;
}

void Selection_Graph(Vertex * vertex) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointCircle(GetMousePosition() , vertex->pos, vertex->radius)) {
            vertex->radius = SELECTED_VERT_RADIUS;
            vertex->color = SELECTED_VERT_COLOR;
            selected_vertex = vertex->node;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        selected_vertex = nullptr;
        vertex->color = DEFAULT_COLOR;
        vertex->radius = DEFAULT_RADIUS;
    }
}

void Reposition_Vertex(Vertex * vertex) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointCircle(GetMousePosition(), vertex->pos, vertex->radius)) {
            vertex->pos = GetMousePosition();
            return;
        }
    }
}

int DrawGraph() {
    int i = 0;
    while (i <= V_List_Top) {
        DrawEdges(vertexList[i]);
        DrawCircleV(vertexList[i]->pos, vertexList[i]->radius, vertexList[i]->color);
        DrawCircleLinesV(vertexList[i]->pos, vertexList[i]->radius, BLACK);
        DrawTextEx(GetFontDefault(), int_to_chars(vertexList[i]->node->data), vertexList[i]->pos, FONT_SIZE, FONT_SPACING, BLACK);
        Selection_Graph(vertexList[i]);
        Reposition_Vertex(vertexList[i]);
        i++;
    }
    return SUCCESS;
}

int Add_Vertex_Handler(Graph_Node * parent, size_t weight, int data) {
    if (parent == nullptr && vertexList[0] != nullptr) {
        return NO_SELECTION;
    }
    else {
        Vertex * new_vertex = malloc(sizeof(Vertex));

        if (parent == nullptr) {
            new_vertex->node = Add_Graph_Node(data, nullptr, weight);
            DEBUG_PRINTF("here at nullptr");
        }
        else {
            new_vertex->node = Add_Graph_Node(data, parent, weight);
        }
        new_vertex->radius = DEFAULT_RADIUS;
        new_vertex->color = DEFAULT_COLOR;
        new_vertex->pos = (Vector2){
            .x = GetRandomValue(10, WINDOW_WIDTH),
            .y = GetRandomValue(10, WINDOW_HEIGHT)};
        vertexList[++V_List_Top] = new_vertex;
        DEBUG_PRINTF(new_vertex->node->data);
        DEBUG_PRINTF(new_vertex->pos.x);
        DEBUG_PRINTF(new_vertex->pos.y);
        return SUCCESS;
    }
}

int inputElementHandlerGraph() {
    static char * valueIN  = nullptr;
    static char * weightch = nullptr;
    if (valueIN == nullptr) {
        valueIN = calloc(TEXT_MAX_SIZE, sizeof(char));
    }
    if (weightch == nullptr) {
        weightch = calloc(TEXT_MAX_SIZE, sizeof(char));
    }

    static bool dial_value_show = false;
    static int butt_value = -2; //magic number intended

    Rectangle const add_butt = {
        .x = GetScreenWidth() - 129,
        .y = GetScreenHeight() - 106,
        .width = 100,
        .height = 75};


    Rectangle const dial_value = {
        .x = GetScreenWidth() - 230,
        .y = GetScreenHeight() - 250,
        .width = 200,
        .height = 127};
    Rectangle const dial_weight = {
        .x = GetScreenWidth() - 230,
        .y = GetScreenHeight() - 450,
        .width = 200,
        .height = 127};

    if (GuiButton(add_butt, "Add Vertex")) {
        dial_value_show = true;
    }

    if (dial_value_show) {
        butt_value = GuiTextInputBox(dial_value, nullptr, nullptr, "ADD", valueIN , TEXT_MAX_SIZE, nullptr);
    }

    switch(butt_value) {
        case -1:
            return ADD_ERROR;
            break;

        case 0:
            dial_value_show = false;
            return SUCCESS;
            break;

        case 1:
            dial_value_show = false;
            int WRresult = GuiTextInputBox(dial_weight, nullptr, nullptr, "ENTER WEIGHT", weightch, TEXT_MAX_SIZE,nullptr);
            if (WRresult == 1) {
                if (chars_to_int(weightch) == NOT_INT)  return NOT_INT;
                if (chars_to_int(valueIN) == NOT_INT) return NOT_INT;
                DEBUG_PRINTF(chars_to_int(weightch));
                DEBUG_PRINTF(chars_to_int(valueIN));
                Add_Vertex_Handler(selected_vertex, chars_to_int(weightch), chars_to_int(valueIN));
            }
            else if (WRresult == 0) {
                butt_value = -2;
            }
        default:
            break;
    }
}

void debug_mode() {
    static char string[256];
    if (selected_vertex == nullptr) {
        DrawText("No Selection", 20, 20, 20 ,BLACK);
    }
    else {
        sprintf(string, "Selected Node is: %d", selected_vertex->data);
        DrawText(string, 10,10,20,BLACK);
    }
    if (int_to_chars(V_List_Top) == nullptr) {
        DrawText("Nullptr", 50, 50, 20, BLACK);
    }
    else {
        sprintf(string, "Value of V_List_Top is: %d", V_List_Top);
        DrawText(string, 10, 50, 20, BLACK);
    }
}


int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "graphGUI");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        inputElementHandlerGraph();
        DrawGraph();
        debug_mode();
        EndDrawing();
    }
}

