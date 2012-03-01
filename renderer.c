#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>
#include <stdio.h>
#include "renderer.h"


static void drawScene();
static void updateFps();
static long millitime();
/* Fps */
static int frameCount = 0;
long lastDisplayTime;

RendererDescriptor* renderer_init() {
    RendererDescriptor* renderer;
    SDL_Surface* screen;
    
    SDL_Init(SDL_INIT_VIDEO);
    
    screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);

    SDL_Flip(screen);
    renderer = malloc(sizeof(RendererDescriptor));
    
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);
    
    return renderer;
}

void renderer_run(RendererDescriptor* gui) {
    char running = 1;
    SDL_Event event;

    lastDisplayTime = millitime();

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = 0;
            }
        }
        drawScene();
        updateFps();
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

static void updateFps() {
    long currentTime;
    
    frameCount += 1;    
    currentTime = millitime();
    
    if(currentTime - lastDisplayTime > 5000) {
        /* Show fps*/
        int fps;
        
        fps = (1000*frameCount) / (currentTime -lastDisplayTime);
        printf("FPS: %i\n", fps);
        
        frameCount = 0;
        lastDisplayTime = currentTime;
    } 
}

static long millitime() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_sec*1000 + time.tv_nsec / 1000000;
}



