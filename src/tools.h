#ifndef TOOLS_H
#define TOOLS_H

void *smalloc(int size);

/* Free the returned buffer*/
char *loadFile(char *path);

/* Free the returned buffer*/
char *substr(char *string, int from);

char *string_cat(char *first, char *second);

long millitime();

void checkGLError(char* context);

#endif
