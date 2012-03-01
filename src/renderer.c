#include <SDL/SDL.h>
#define GL3_PROTOTYPES 1
#include "include/gl3.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "renderer.h"
#include "tools.h"


static void drawScene();
static void updateFps();
static long millitime();
/* Fps */
static int frameCount = 0;
long lastDisplayTime;
static void initShaders();


static int shaderId = 0;
static int vertShader = 0;
static int geoShader = 0;
static int fragShader = 0;


RendererDescriptor* renderer_init() {
    RendererDescriptor* renderer;
    SDL_Surface* screen;
    
    SDL_Init(SDL_INIT_VIDEO);
    
    screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);

    SDL_Flip(screen);
    renderer = malloc(sizeof(RendererDescriptor));
    
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);
    
    initShaders();
    
    
    return renderer;
}

void renderer_run(RendererDescriptor* gui) {
    char running = 1;
    SDL_Event event;
    
    (void) gui;

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
    (void) gui;
    glDeleteProgram(shaderId);

    SDL_Quit();
}

static void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderId);

    glBegin(GL_TRIANGLES);
        glColor3ub(255,0,0);    glVertex2d(-0.75,-0.75);
        glColor3ub(0,255,0);    glVertex2d(0,0.75);
        glColor3ub(0,0,255);    glVertex2d(0.75,-0.75);
    glEnd();
    
    glUseProgram(0);
    
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


static int createVertShader(char *path);
static int createGeometryShader(char *path);
static int createFragShader(char *path);

static void initShaders() {
    shaderId = glCreateProgram();
    
  
    
    
    if(shaderId != 0) {
        char* name = "sky";
        char* pathBase = "shaders/";
        char* extension = ".glsl";

        char* fullPath = smalloc(sizeof(char) * (strlen(name) + strlen(pathBase)  + strlen(extension)+ 2 + 1)); /* we have to add .v, .g or .f */
    
        
        strcpy(fullPath, pathBase);
        strcat(fullPath, name);
        strcat(fullPath, ".v");
        strcat(fullPath, extension);
        vertShader = createVertShader(fullPath);
        
        strcpy(fullPath, pathBase);
        strcat(fullPath, name);
        strcat(fullPath, ".g");
        strcat(fullPath, extension);
        geoShader = createGeometryShader(fullPath);

        strcpy(fullPath, pathBase);
        strcat(fullPath, name);
        strcat(fullPath, ".f");
        strcat(fullPath, extension);
        fragShader = createFragShader(fullPath);
        
        
        free(fullPath);
    
    } else {
        printf("Fail to create shader");
    }

}

static int createVertShader(char *path) {
    (void) path;
    return 0;
}

static int createGeometryShader(char *path) {
    (void) path;
    return 0;
}

static int createFragShader(char *path) {
    (void) path;
    return 0;
}


    
 

