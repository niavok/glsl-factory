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

/* Return buffer to free ! */
char* loadFile(char* path) {
    FILE* file = NULL;
    int size = 0;
    char* fileBuffer = NULL;
    
    file = fopen(path, "rb");
    if(file == NULL) {
        
        return NULL;
    }

    /* get size*/    
    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    rewind(file);
    
    fileBuffer = smalloc(sizeof(char) * size);
    fread(fileBuffer, sizeof(char), size, file);
    
    fclose(file);
    return fileBuffer;
    
}
 
