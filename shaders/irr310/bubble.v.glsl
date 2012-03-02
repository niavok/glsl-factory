#version 120
#extension GL_EXT_gpu_shader4 : enable

varying vec4 verposIn;

void main(void)
{
   gl_Position =  ftransform();
   gl_Position =  ftransform();
   verposIn = gl_Vertex;
}
