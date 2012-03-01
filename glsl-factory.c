/* GLSL Factory Main */
#include <stdio.h>
#include "gui.h"
#include "renderer.h"

int main(int argc, char *argv[]) {


    int pid;

    if ((pid = fork()) == 0) {
        /* Child */
        /*Editor window*/

        GuiDescriptor * descriptor;

        descriptor = gui_init(argc, argv);
        gui_run(descriptor);
        gui_destroy(descriptor);
        
    } else {
        /* Father */
        /*SDL/OpenGL window*/
        RendererDescriptor * descriptor;

        descriptor = renderer_init(argc, argv);
        renderer_run(descriptor);
        renderer_destroy(descriptor);
    }
    
    return 0;
}
