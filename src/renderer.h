#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"

struct Shader;
typedef struct Renderer Renderer;

struct Renderer{
    int XResolution;
    int YResolution;
    struct Shader *shader;
};

void renderer_init(Renderer *renderer);

void renderer_run(Renderer* renderer);

void renderer_bindShader(Renderer* renderer,struct Shader* shader);

void renderer_destroy(Renderer* renderer);


#endif
