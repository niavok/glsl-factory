#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
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
 
/* Return buffer to free ! */
char *substr(char *string, int from) {
    char *out;
    out = smalloc(sizeof(char) * (strlen(string) - from +1));
    strncpy(out, string+from , strlen(string) - from);
    out[strlen(string) - from] = '\0';
    return out;
}

char *string_cat(char *first, char *second) {
    char *out;
    out = smalloc(sizeof(char) * (strlen(first) + strlen(second) +1));
    out[0] = '\0';
    strcat(out, first);
    strcat(out, second);
    return out;
}


long millitime() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_sec*1000 + time.tv_nsec / 1000000;
}

void checkGLError(char* context) {
    GLenum errCode;
    const GLubyte *errString;
    
    if ((errCode = glGetError()) != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
       fprintf (stderr, "OpenGL Error at %s: %s\n", context, errString);
    }
}
