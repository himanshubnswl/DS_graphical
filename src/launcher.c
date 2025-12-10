//
// Created by lhbdawn on 06-12-2025.
//
#define RAYGUI_IMPLEMENTATION
#include "launcher.h"

int DrawShapes() {
    const int margin_vertical = 100;
    const int margin_horizontal = 100;
    const int gap_bw_buttons = GetScreenHeight()/3;

    struct Rectangle array_button = {
        .x = margin_horizontal,
        .y = margin_vertical,
        .width = GetScreenWidth()/3,
        .height = GetScreenHeight()/6};
    struct Rectangle ll_button = {
        .x = array_button.x,
        .y = array_button.y + gap_bw_buttons,
        .width = array_button.width,
        .height = array_button.height};
    struct Rectangle BST_button = {
        .x = array_button.x,
        .y = ll_button.y + gap_bw_buttons,
        .width = array_button.width,
        .height = array_button.height};
    struct Rectangle graph_button = {
        .x = array_button.x,
        .y = BST_button.y + gap_bw_buttons,
        .width = array_button.width,
        .height = array_button.height};

    if (GuiButton(array_button, "ARRAY")) {
        if (!CreateProcessA("./bin/array.exe", nullptr,nullptr,nullptr,TRUE, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr, nullptr, nullptr)) {
            printf("\nprocess creation failed");
        }
    }
    if (GuiButton(ll_button, "LINKED LIST")) {

    }
    if (GuiButton(BST_button, "BINARY SEARCH TREE")) {

    }
    if (GuiButton(graph_button, "GRAPH")) {

    }
}

int main() {
    const char* save_dir_path = "./saves";
    if (CreateDirectory(save_dir_path, NULL)) {
        printf("\ndirectory creation successfull");
    }
    else {
        printf("\ndirectory creation failed");
    }
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "launcher.exe");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawShapes();
        EndDrawing();
    }
}
