//
// Created by lhbdawn on 03-10-2025.
//

#include "graphGUI.h"

#include "../helpers/helper.h"
Vertex * vertexList[MAX_ELEMENTS_NUM] = {nullptr};
Graph_Node * selected_vertex = nullptr;


Vertex * L_Search_Node(Graph_Node * node) {
    size_t i = 0;
    while (vertexList[i] != nullptr) {
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
    for (size_t i = 0; i <= vertex->node->outgoing_edges_index; i++) {
        Vertex * dest = L_Search_Node(vertex->node->outgoing_edges[i]->node);
        DrawPointyLine(vertex->pos, dest->pos , DEFAULT_LINE_THICKNESS, DEFAULT_COLOR);
    }
    for (size_t i = 0; i <= vertex->node->incoming_edges_index; i++) {
        Vertex * dest = L_Search_Node(vertex->node->incoming_edges[i]->node);
        DrawPointyLine(vertex->pos, dest->pos , DEFAULT_LINE_THICKNESS, DEFAULT_COLOR);
    }
    return SUCCESS;
}

Graph_Node * Selection_Graph(Vertex * vertex) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        if (CheckCollisionPointCircle(GetMousePosition() , vertex->pos, vertex->radius)) {
            vertex->radius += 5;
            vertex->color = GREEN;
            return vertex->node;
        }
        else {
            vertex->color = DEFAULT_COLOR;
            vertex->radius = DEFAULT_RADIUS;
        }
    }
    return nullptr;
}

int Reposition_Vertex(Vertex * vertex) {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        if (CheckCollisionPointCircle(GetMousePosition(), vertex->pos, vertex->radius)) {
            vertex->pos = GetMousePosition();
            return SUCCESS;
        }
    }
}

int DrawGraph() {
    size_t i = 0;
    while (vertexList[i] != nullptr) {
        DrawEdges(vertexList[i]);
        DrawCircleV(vertexList[i]->pos, vertexList[i]->radius, vertexList[i]->color);
        DrawTextEx(GetFontDefault(), int_to_chars(vertexList[i]->node->data), vertexList[i]->pos, FONT_SIZE, FONT_SPACING, BLACK);
        selected_vertex = Selection_Graph(vertexList[i]);
        Reposition_Vertex(vertexList[i]);
    }
    return SUCCESS;
}

int Add_Vertex_Handler(Graph_Node * parent, size_t weight, int data) {
    if (parent == nullptr && vertexList[0] == nullptr) {
        return NO_SELECTION;
    }
    else {
        if (parent == nullptr) {
            Add_Graph_Node(data, nullptr, weight);
            return SUCCESS;
        }
        else {
            Add_Graph_Node(data, parent, weight);
            return SUCCESS;
        }
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

    static bool dialogue_stat = false;
    static int result = -2; //magic number intended

    Rectangle const inputBox = {
        .x = GetScreenWidth() - 129,
        .y = GetScreenHeight() - 106,
        .width = 100,
        .height = 75};


    Rectangle const dialogueBox = {
        .x = GetScreenWidth() - 230,
        .y = GetScreenHeight() - 250,
        .width = 200,
        .height = 127};

    if (GuiButton(inputBox, "Add Vertex")) {
        dialogue_stat = true;
    }

    if (dialogue_stat) {
        result = GuiTextInputBox(dialogueBox, nullptr, nullptr, "ADD", valueIN , TEXT_MAX_SIZE, false);
    }

    switch (result) {
        case -1:
            return ADD_ERROR;
            break;

        case 0:
            dialogue_stat = false;
            return SUCCESS;
            break;

        case 1:
            dialogue_stat = false;
            int WRresult = GuiTextInputBox(dialogueBox, nullptr, nullptr, "ENTER WEIGHT", weightch, TEXT_MAX_SIZE,false);
            if (WRresult == 1) {
                if (chars_to_int(weightch) == NOT_INT)  return NOT_INT;
                if (chars_to_int(valueIN) == NOT_INT) return NOT_INT;
                Add_Vertex_Handler(selected_vertex, chars_to_int(weightch), chars_to_int(valueIN));
            }
            else if (WRresult == 0) {
                result = -2;
            }
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
        EndDrawing();
    }
}
