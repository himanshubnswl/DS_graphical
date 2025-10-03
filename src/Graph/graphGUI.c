//
// Created by lhbdawn on 03-10-2025.
//

#include "graphGUI.h"

#include "../helpers/helper.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "graphGUI");
    SetTargetFPS(60);
    initialize_graph();

    char * input_text = malloc(256*sizeof(char));
    while (!WindowShouldClose()) {
        inputElementHandler(input_text, add_graph_node);
    }
}
