#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define GL3_PROTOTYPES 1
#include "include/gl3.h"


#include "tools.h"
#include "shader.h"



static void createShaderProgram(Shader *shader);
static int createShader(char *path, int shaderType);
static char printShaderLogInfo(int shader, char* path);
static char printProgramLogInfo(int program);
static void shaderParam_destroy(ShaderParam *shaderParam);


static int uniform_inputRotation = 0;
static int uniform_resolution = 0;
static int uniform_time = 0;

void shader_init(Shader *shader) {
    shader->vertexShaderPath = NULL;    
    shader->geometryShaderPath = NULL;
    shader->fragmentShaderPath = NULL;
    
    shader->programId = 0;
    shader->vertexShaderId = 0;
    shader->geometryShaderId = 0;
    shader->fragmentShaderId = 0;
    
    shader->loaded = 0;

    shader->paramListSize = 0;
    shader->paramList = NULL;
}

void shader_load(Shader *shader, char* shaderDescriptionPath) {
    FILE* file = NULL;
    char lineBuffer[500];
    char *vertexShaderPathCode = "vertexShader.path=";
    char *geometryShaderPathCode = "geometryShader.path=";
    char *fragmentShaderPathCode = "fragmentShader.path=";
    char *basePath;
    printf("Loading shader description file: %s\n", shaderDescriptionPath);

    
    file = fopen(shaderDescriptionPath, "r");
    if(file == NULL) {
        printf("Fail to open shader description file: %s\n", shaderDescriptionPath);
        return ;
    }
    
    
    basePath = smalloc(sizeof(char) * (strlen(shaderDescriptionPath)+1));
    strcpy(basePath, shaderDescriptionPath);
    *(strrchr(basePath, '/')+1) = '\0';
    
    while(fgets(lineBuffer,500, file)) {
        int lineLength = strlen(lineBuffer);
        
        if(lineLength > 400) {
             printf("Warning, line longer than 500 characters are not supported. Current line size: %d\n", lineLength);
        }
        
        if(lineLength > 0 && lineBuffer[0] == '#') {
            /* Comment line*/
            continue;
        }
        
        /*remove lineEnd */
        if(lineBuffer[lineLength-1] == '\n') {
            lineBuffer[lineLength-1] = '\0';
            lineLength -= 1;
        }

        if(strncmp(lineBuffer, vertexShaderPathCode, strlen(vertexShaderPathCode)) == 0) {
            char * fileName = substr(lineBuffer, strlen(vertexShaderPathCode));
            shader->vertexShaderPath = string_cat(basePath, fileName);
            free(fileName);
        }
        
        if(strncmp(lineBuffer, geometryShaderPathCode, strlen(geometryShaderPathCode)) == 0) {
            char * fileName = substr(lineBuffer, strlen(geometryShaderPathCode));
            shader->geometryShaderPath = string_cat(basePath, fileName);
            free(fileName);
        }
        
        if(strncmp(lineBuffer, fragmentShaderPathCode, strlen(fragmentShaderPathCode)) == 0) {
            char *fileName = substr(lineBuffer, strlen(fragmentShaderPathCode));
            shader->fragmentShaderPath = string_cat(basePath, fileName);
            free(fileName);
        }
           
    }

    fclose(file);
    
    createShaderProgram(shader);
    
    if(shader->programId) {
        shader->loaded = 1;
    }
    
    free(basePath);
}

void shader_destroy(Shader *shader) {
    int i;

    free(shader->vertexShaderPath);    
    free(shader->geometryShaderPath);
    free(shader->fragmentShaderPath);
    
    glDeleteProgram(shader->programId);
    glDeleteShader(shader->vertexShaderId);
    glDeleteShader(shader->geometryShaderId);
    glDeleteShader(shader->fragmentShaderId);
    
    shader->loaded = 0;
    
    for(i = 0; i < shader->paramListSize; i++) {
        ShaderParam *param = shader->paramList[i];
        shaderParam_destroy(param);
        free(param);
    }

    shader->paramListSize = 0;
    free(shader->paramList);
    shader->paramList = NULL;
}

void shader_setUniforms(Shader *shader) {
    (void) shader;
    glUniform2f(uniform_resolution, 1024,768);
    glUniform1f(uniform_time, (float) millitime() /1000.0 );
}

static void createShaderProgram(Shader *shader) {
    printf("Load shaders\n");
    
    shader->programId = glCreateProgram();
    if(shader->programId != 0) {

        if(shader->vertexShaderPath) {
            shader->vertexShaderId = createShader(shader->vertexShaderPath, GL_VERTEX_SHADER);
        }
        
        if(shader->geometryShaderPath) {
            shader->geometryShaderId = createShader(shader->geometryShaderPath, GL_GEOMETRY_SHADER);
        }
        
        if(shader->fragmentShaderPath) {
            shader->fragmentShaderId = createShader(shader->fragmentShaderPath, GL_FRAGMENT_SHADER);
        }
        
        if(shader->vertexShaderId && shader->fragmentShaderId) {
            glAttachShader(shader->programId, shader->vertexShaderId);
            glAttachShader(shader->programId, shader->fragmentShaderId);
            
            if(shader->geometryShaderId) {
                glAttachShader(shader->programId, shader->geometryShaderId);
            }

            glLinkProgram(shader->programId);
            glValidateProgram(shader->programId);
            
            if(!printProgramLogInfo(shader->programId)) {
                glDeleteProgram(shader->programId);
                shader->programId = 0;
            }
            
            
            uniform_inputRotation = glGetUniformLocation(shader->programId, "inputRotation");
            uniform_resolution = glGetUniformLocation(shader->programId, "resolution");
            uniform_time = glGetUniformLocation(shader->programId, "time");
       
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

static void shaderParam_destroy(ShaderParam *shaderParam) {
    free(shaderParam->name);
}

