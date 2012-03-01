/* GLSL Factory Main */
#include <stdio.h>
#include "gui.h"

int main(int argc, char *argv[]) {
    GuiDescriptor * descriptor;

    descriptor = gui_init(argc, argv);
    gui_run(descriptor);
    gui_destroy(descriptor);
    return 0;
}
