/* GLSL Factory Main */
#include <stdio.h>
#include "renderer.h"

int main(int argc, char *argv[]) {
   
    RendererDescriptor * descriptor;

    descriptor = renderer_init(argc, argv);
    renderer_run(descriptor);
    renderer_destroy(descriptor);
    
    return 0;
}
