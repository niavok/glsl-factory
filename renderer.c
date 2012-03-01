#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "renderer.h"


static void drawScene();

RendererDescriptor* renderer_init() {
    RendererDescriptor* renderer;
    SDL_Surface* screen;
    
    SDL_Init(SDL_INIT_VIDEO);
    
    screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);

    SDL_Flip(screen);
    renderer = malloc(sizeof(RendererDescriptor));
    
    return renderer;
}

void renderer_run(RendererDescriptor* gui) {
    char running = 1;
    SDL_Event event;

    while (running)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                running = 0;
        }
        
        drawScene();
    }

}

void renderer_destroy(RendererDescriptor* gui) {
    SDL_Quit();
}

static void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3ub(255,0,0);    glVertex2d(-0.75,-0.75);
        glColor3ub(0,255,0);    glVertex2d(0,0.75);
        glColor3ub(0,0,255);    glVertex2d(0.75,-0.75);
    glEnd();
    glFlush();
    SDL_GL_SwapBuffers();

}


