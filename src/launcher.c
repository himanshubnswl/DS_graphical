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

    }
}
