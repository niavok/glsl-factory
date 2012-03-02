#include <SDL/SDL.h>
#define GL3_PROTOTYPES 1
#include "include/gl3.h"
#include <GL/gl.h>

#include <stdio.h>
#include <string.h>
#include "renderer.h"
#include "tools.h"


static void drawScene(Renderer *renderer);
static void updateFps();


/* Fps */
static int frameCount = 0;
long lastDisplayTime;


void renderer_init(Renderer * renderer) {
    SDL_Surface *screen;

    (void) renderer;
    
    SDL_Init(SDL_INIT_VIDEO);
    
    screen = SDL_SetVideoMode(1024, 768, 32, SDL_OPENGL);

    SDL_Flip(screen);
    
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);
}

void renderer_run(Renderer* renderer) {
    char running = 1;
    SDL_Event event;
    
    lastDisplayTime = millitime();

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: /* Quit */
                            running = 0;
                            break;
                        case SDLK_F5: /* Reload shader */
                            if(renderer->shader) {
                                shader_reload(renderer->shader);
                                renderer_bindShader(renderer, renderer->shader);
                            }
                            break;
                        default:
                        break;
                    }
                    break;
                default:
                    break;
            }
        }
        drawScene(renderer);
        updateFps();
    }
}

void renderer_destroy(Renderer* renderer) {
    (void) renderer;
   
    SDL_Quit();
}

void renderer_bindShader(Renderer* renderer, Shader* shader) {
    renderer->shader = shader;
}


static void drawScene(Renderer* renderer) {

    glClear(GL_COLOR_BUFFER_BIT);
    
    if(renderer->shader && renderer->shader->loaded) {
        glUseProgram(renderer->shader->programId);
        
        shader_setUniforms(renderer->shader);
    }

    glBegin(GL_QUADS);
        glColor3ub(255,0,0);    glVertex2d(-1.0,-1.0);
        glColor3ub(255,255,0);    glVertex2d(-1.0,1.0);
        glColor3ub(0,255,0);    glVertex2d(1.0,1.0);
        glColor3ub(0,0,255);    glVertex2d(1.0,-1.0);
    glEnd();
    
    if(renderer->shader && renderer->shader->loaded) {
        glUseProgram(0);
    }
    glFlush();
    /*checkGLError("glFlush");*/
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






