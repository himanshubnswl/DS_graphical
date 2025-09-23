//
// Created by lhbdawn on 13-07-2025.
//
#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <raygui.h>
#include <raylib.h>
#include <debug.h>
#define RAYGUI_IMPLEMENTATION
typedef int (*getInput)(char *);

char * int_to_chars(int number);
int chars_to_int(char * text);
int inputElementHandler(char * input_text, getInput getvalue);
int removeElementHandler(int (*removeElementInDS)(int));



