varying vec4 vertColor;
 
void main(){
     gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
     gl_FrontColor = gl_Color;
}
