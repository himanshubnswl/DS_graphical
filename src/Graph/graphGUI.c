//
// Created by lhbdawn on 03-10-2025.
//

#include "graphGUI.h"

#include "../helpers/helper.h"
Vertex * vertexList[MAX_ELEMENTS_NUM] = {nullptr};

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
        DrawPointyLine(vertex->pos,  , 20, BLACK);
    }
}

int DrawGraph() {
    size_t i = 0;
    while (vertexList[i] != nullptr) {



        DrawCircleLinesV(vertexList[i]->pos, vertexList[i]->radius, vertexList[i]->color);
        DrawTextEx(GetFontDefault(), int_to_chars(vertexList[i]->node->data), vertexList[i]->pos, 20, 5, BLACK);
    }
}

int inputElementHandler () {
    static char * textIN = malloc(sizeof(char) * 20);
    static bool dialogue_stat = false;
    int result = -2; //magic number intended

    static Rectangle const inputBox = {
        .x = GetScreenWidth() - 129,
        .y = GetScreenHeight() - 106,
        .width = 100,
        .height = 75};


    static Rectangle const dialogueBox = {
        .x = GetScreenWidth() - 230,
        .y = GetScreenHeight() - 250,
        .width = 200,
        .height = 127};

    if (GuiButton(inputBox, "Add Vertex")) {
        dialogue_stat = true;
    }
    if (dialogue_stat) {
        result = GuiTextInputBox(dialogueBox, nullptr, nullptr, "ADD", textIN , 20, false);
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
            // Add_Graph_Node(chars_to_int(textIN), );
    }
}



int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "graphGUI");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {


    }
}
