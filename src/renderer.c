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


static int createShader(char *path, int shaderType);
static char printShaderLogInfo(int shader, char* path);
static char printProgramLogInfo(int program);


/* Fps */
static int frameCount = 0;
long lastDisplayTime;
static void initShaders();


static int shaderId = 0;
static int vertShader = 0;
static int geoShader = 0;
static int fragShader = 0;
static int uniform_inputRotation = 0;
static int uniform_resolution = 0;
static int uniform_time = 0;


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

static void checkGLError(char* context) {
    GLenum errCode;
    const GLubyte *errString;
    
    if ((errCode = glGetError()) != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
       fprintf (stderr, "OpenGL Error at %s: %s\n", context, errString);
    }
}

static void drawScene() {

    glClear(GL_COLOR_BUFFER_BIT);
    /*checkGLError("glClear");*/
    glUseProgram(shaderId);
    /*checkGLError("glUseProgram");*/



    glUniform2f(uniform_resolution, 800,600);
    glUniform1f(uniform_time, (float) millitime() /1000.0 );


    glBegin(GL_TRIANGLES);
        glColor3ub(255,0,0);    glVertex2d(-0.75,-0.75);
        glColor3ub(0,255,0);    glVertex2d(0,0.75);
        glColor3ub(0,0,255);    glVertex2d(0.75,-0.75);
    glEnd();
    /*checkGLError("glEnd");*/
    glUseProgram(0);
    /*checkGLError("glUseProgram 0");    */
    glFlush();
    /*checkGLError("glFlush");
    checkGLError("glFlush");
    */
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

static void initShaders() {
    
    checkGLError("initShaders");
    
    printf("Init shaders\n");
    
    
    shaderId = glCreateProgram();
    checkGLError("glCreateProgram");
    
    if(shaderId != 0) {
        char* name = "sky";
        char* pathBase = "shaders/";
        char* extension = ".glsl";

        char* fullPath = smalloc(sizeof(char) * (strlen(name) + strlen(pathBase)  + strlen(extension)+ 2 + 1)); /* we have to add .v, .g or .f */
    
        
        strcpy(fullPath, pathBase);
        strcat(fullPath, name);
        strcat(fullPath, ".v");
        strcat(fullPath, extension);
        vertShader = createShader(fullPath, GL_VERTEX_SHADER);
        
        strcpy(fullPath, pathBase);
        strcat(fullPath, name);
        strcat(fullPath, ".g");
        strcat(fullPath, extension);
        geoShader = createShader(fullPath, GL_GEOMETRY_SHADER);

        strcpy(fullPath, pathBase);
        strcat(fullPath, name);
        strcat(fullPath, ".f");
        strcat(fullPath, extension);
        fragShader = createShader(fullPath, GL_FRAGMENT_SHADER);
        
        free(fullPath);
        
        printf("vertShader %d\n",vertShader);
        printf("fragShader %d\n",fragShader);      
        
        if(vertShader && fragShader) {
            glAttachShader(shaderId, vertShader);
            glAttachShader(shaderId, fragShader);
            
            if(geoShader) {
                glAttachShader(shaderId, geoShader);
            }
            
            glLinkProgram(shaderId);
            glValidateProgram(shaderId);
            
            if(!printProgramLogInfo(shaderId)) {
                glDeleteProgram(shaderId);
                shaderId = 0;
            }
            
            
            uniform_inputRotation = glGetUniformLocation(shaderId, "inputRotation");
            uniform_resolution = glGetUniformLocation(shaderId, "resolution");
            uniform_time = glGetUniformLocation(shaderId, "time");
         
            printf("Shaders loaded\n");   
        }
        
    
    } else {
        printf("Fail to create shader\n");
    }
    
    checkGLError("glCreateProgram end");

}

static int createShader(char *path, int shaderType) {
    int shader = 0;
    
    printf("Load shader: %s\n", path);

    shader = glCreateShader(shaderType);
    if (shader == 0) {
        printf("Fail to create shader: %s\n", path);
        return 0;
    } else {
        const char*sourceCodes[1];
        int sourceCodesLength[1];
        char* fileBuffer = NULL;
        fileBuffer = loadFile(path);
        if(!fileBuffer) {
            printf("Shader file not found: %s\n", path);
            return 0;
        }
        
        sourceCodes[0] = fileBuffer;
        sourceCodesLength[0] = strlen(sourceCodes[0]);
        
        glShaderSource(shader, 1, (const char**) sourceCodes , sourceCodesLength);
        glCompileShader(shader);
        
        free(fileBuffer);
        
        if(!printShaderLogInfo(shader, path)) {
            return 0;
        }
        printf("Shader %d successfully loaded: %s\n", shader, path);
        
        return shader;
    }
}

static char printShaderLogInfo(int shader, char* path) {
    int length = 0;
    
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    if (length > 1) {
        /* We have some info we need to output. */

        char* infoLog = smalloc(sizeof(char) * length);
        int infoLogLength = 0;
        
        glGetShaderInfoLog(shader, length, &infoLogLength, infoLog);

        printf("Compile log for shader %s: \n%s", path, infoLog);

        free(infoLog);
    } else {
        return 1;
    }
    return 0;
}

static char printProgramLogInfo(int program) {
    int length = 0;
    
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

    if (length > 1) {
        /* We have some info we need to output. */

        char* infoLog = smalloc(sizeof(char) * length);
        int infoLogLength = 0;
        
        glGetProgramInfoLog(program, length, &infoLogLength, infoLog);

        printf("Compile log for program: \n%s", infoLog);

        free(infoLog);
    } else {
        return 1;
    }
    return 0;
}



