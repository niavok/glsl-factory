#include <stdlib.h>
#include <stdio.h>
#include "tools.h"

void *smalloc(int size) {
    void *ptr = malloc(size);
    if(ptr == NULL) {
        printf("Out of memory");
        exit(1);
    }
    return ptr;
}
