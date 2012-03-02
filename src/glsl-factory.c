/* GLSL Factory Main */
#include <stdio.h>
#include <stdlib.h>
#include "renderer.h"
#include "shader.h"

int main(int argc, char *argv[]) {
    Renderer renderer;
    Shader shader;
    char *shaderDescriptionPath;
   (void) argc;
   (void) argv;

    if(argc != 2) {
        printf("The program must take one and only one parameter.");
        exit(1);    
    }

    shaderDescriptionPath = argv[1];
    
    renderer_init(&renderer);

    shader_init(&shader);
    shader_load(&shader, shaderDescriptionPath);
    
    renderer_bindShader(&renderer, &shader);
    
    renderer_run(&renderer);
    
    shader_destroy(&shader);
    
    renderer_destroy(&renderer);
    
    return 0;
}
