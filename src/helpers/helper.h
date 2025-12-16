//
// Created by lhbdawn on 13-07-2025.
//
#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <debug.h>
#include <stdint.h>


#define HASH_FNV_OFFSET 0x811c9dc5
#define FNV_PRIME 0x01000193
typedef int (*getInput)(char *);

char * int_to_chars(int number);
int chars_to_int(char * text);
uint32_t Hash_String_FNV(char const * string_to_hash);




