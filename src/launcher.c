//
// Created by lhbdawn on 06-12-2025.
//

#include "launcher.h"

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
        struct Rectangle array_button = {
            .x = (GetScreenWidth()/3) * 2,
            .y = (GetScreenHeight()/6) * 2,
            .width = GetScreenWidth()/3,
            .height = GetScreenHeight()/6};
        struct Rectangle ll_button = {
            .x = array_button.x,
            };
    }
}
