#pragma once


#define DEBUG_PRINTF(X) \
    _Generic((X), \
        int: printf("\nvalue of %s is: %d", #X, X), \
        char*: printf("\nstring inside %s is: %s", #X, X), \
        default: printf("\n type unkown") \
    )

#define DEBUG_CHECKPOINT(X) \
    _Generic((X), \
        int:printf("\nwe are at line: %d", X), \
        default: printf("type unkown") \
    )
