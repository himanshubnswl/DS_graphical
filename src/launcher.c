//
// Created by lhbdawn on 06-12-2025.
//
#define RAYGUI_IMPLEMENTATION
#define WIN32_LEAN_AND_MEAN // Excludes most headers from windows.h
#define NOGDI               // Excludes GDI (Graphics Device Interface) macros, like Rectangle
#define NOUSER              // Excludes USER (User Interface) macros, like CloseWindow, ShowCursor, etc.

#include "launcher.h"
/* things to do
 * new cmake, current one is shite
 * compile and run for linux
 * animations (maybe not)
 */
int DrawShapes() {
    const int margin_vertical = 100;
    const int margin_horizontal = 100;
    const int gap_bw_buttons = GetScreenHeight()/5;

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    Rectangle array_button = {
        .x = margin_horizontal,
        .y = margin_vertical,
        .width = GetScreenWidth()/3,
        .height = GetScreenHeight()/6};
    Rectangle ll_button = {
        .x = array_button.x,
        .y = array_button.y + gap_bw_buttons,
        .width = array_button.width,
        .height = array_button.height};
    Rectangle BST_button = {
        .x = array_button.x,
        .y = ll_button.y + gap_bw_buttons,
        .width = array_button.width,
        .height = array_button.height};
    Rectangle graph_button = {
        .x = array_button.x,
        .y = BST_button.y + gap_bw_buttons,
        .width = array_button.width,
        .height = array_button.height};

    if (GuiButton(array_button, "ARRAY")) {
        printf("hello to myself");
        if (!CreateProcessA("array.exe", nullptr,nullptr,nullptr,TRUE, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr, &si, &pi)) {
            printf("\nprocess creation failed");
        }
        else {
            // Close process and thread handles
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            exit(0);
        }
    }
    if (GuiButton(ll_button, "LINKED LIST")) {
        if (!CreateProcessA("LinkedList.exe", nullptr, nullptr, nullptr,TRUE, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr, &si, &pi)) {
            printf("\nprocess creation failed!");
        }
        else {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            exit(0);
        }
    }
    if (GuiButton(BST_button, "BINARY SEARCH TREE")) {
        if (!CreateProcessA("tree.exe", nullptr, nullptr, nullptr, TRUE, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr, &si,&pi)) {
            printf("\nprocess creation failed");
        }
        else {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            exit(0);
        }
    }
    if (GuiButton(graph_button, "GRAPH")) {
        if (!CreateProcessA("graph.exe", nullptr, nullptr, nullptr, TRUE, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr, &si,&pi)) {
            printf("\nprocess creation failed");
        }
        else {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            exit(0);
        }
    }

    return 0;
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
