varying vec4 vertColor;
 
void main(){
    gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
    vertColor = vec4(0.6*gl_Position.y, 0.3*gl_Position.x, 0.4, 1.0);
}
