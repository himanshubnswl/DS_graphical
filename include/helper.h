//
// Created by lhbdawn on 13-07-2025.
//
#pragma once

#include <math.h>
#include <stdlib.h>
#include <error.h>

typedef int (*getInput)(char *);

char * int_to_chars(int number);
int chars_to_int(char * text);
int inputElementHandler(bool * dialogue_box_status, char * input_text, getInput getvalue);


