//
// Created by lhbdawn on 04-09-2025.
//

#ifndef BINARYSEARCHTREEGUI_H
#define BINARYSEARCHTREEGUI_H
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raygui.h>
#include "../helpers/helper.h"
#include "../helpers/error.h"
#include "TreeInternals.h"

#define INPUT_TEXT_MAX_SIZE 256

#ifdef DEBUG
#include <debug.h>
#endif

void DrawBSTree();
int addGuiNode(int input);
int load_file();
int save_file();


#endif //BINARYSEARCHTREEGUI_H
