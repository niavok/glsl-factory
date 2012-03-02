#ifndef SHADER_H
#define SHADER_H

typedef enum  {
    TIME_S,
    TIME_MS,
    RESOLUTION
} ShaderParamType;

typedef struct {
    char* name;
    ShaderParamType type;
} ShaderParam;


typedef struct {
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

} Shader;


void shader_init(Shader *shader);

void shader_load(Shader *shader, char* shaderDescriptionPath);

void shader_reload(Shader *shader);

void shader_setUniforms(Shader *shader);

void shader_destroy(Shader *shader);

#endif
