#ifndef SHADER_H
#define SHADER_H

#include "renderer.h"

struct Renderer;

typedef struct Shader Shader;
typedef struct ShaderParam ShaderParam;

typedef enum  {
    TIME_S,
    TIME_MS,
    RESOLUTION
} ShaderParamType;

struct ShaderParam {
    char* name;
    ShaderParamType type;
};


struct Shader {
    char* vertexShaderPath;    
    char* geometryShaderPath;
    char* fragmentShaderPath;
    
    int programId;
    int vertexShaderId;
    int geometryShaderId;
    int fragmentShaderId;
    
    char loaded;

    int paramListSize;
    ShaderParam **paramList;
    struct Renderer * renderer;
} ;


void shader_init(Shader *shader);

void shader_load(Shader *shader, char* shaderDescriptionPath);

void shader_reload(Shader *shader);

void shader_setUniforms(Shader *shader);

void shader_destroy(Shader *shader);

#endif
