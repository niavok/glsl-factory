#version 120
varying vec3 normal;

void main()
{
    gl_FrontColor = gl_Color;
	normal = gl_NormalMatrix * gl_Normal;
	gl_Position = ftransform();

}
