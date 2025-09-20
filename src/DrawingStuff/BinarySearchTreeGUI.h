//
// Created by lhbdawn on 04-09-2025.
//

#ifndef BINARYSEARCHTREEGUI_H
#define BINARYSEARCHTREEGUI_H
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raygui.h>
#include <helper.h>
#include <error.h>
#include <TreeInternals.h>
#define RAYGUI_IMPLEMENTATION

#ifdef DEBUG \
        #define DEBUG_PRINTF(X) \
                _Generic((X), \
                int: printf("\nvalue of %s is: %d", #X, X), \
                char*: printf("\nstring inside %s is: %s", #X, X) \
                default: printf("\n type unkown") \
                ) \
#endif

#ifdef DEBUG \
        #define DEBUG_CHECKPOINT(X) \
                _Generic((X), \
                int:printf("\nwe are at line: %d", X), \
                default: printf("type unkown") \
                ) \
#endif

#endif //BINARYSEARCHTREEGUI_H
