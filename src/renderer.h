#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"

typedef struct {
    Shader *shader;
} Renderer;

void renderer_init(Renderer *renderer);

void renderer_run(Renderer* renderer);

void renderer_bindShader(Renderer* renderer, Shader* shader);

void renderer_destroy(Renderer* renderer);


#endif
