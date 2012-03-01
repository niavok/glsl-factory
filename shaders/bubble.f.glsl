#version 120
#extension GL_EXT_gpu_shader4 : enable

noperspective varying vec3 dist;
varying float meshSize;
const vec4 WIRE_COL = vec4(0.7,0.7,0.8,1.0);
const vec4 FILL_COL = vec4(0.9,0.9,0.9,0.2);
varying vec4 verpos;
uniform float time;
float PI = 3.14159265358979323846264;

vec3 genTex2( in vec3 p1 )
{
    vec3 p = mod(p1, PI * 2.0);
    float a = sin(p.x);
    float b = sin(p.y);
    float c = sin(p.z);
    
    vec3 d = vec3(1.0);
    
    d.x  = (sin(1.9*time + 8.3*c) * sin(2.1*time + 0.5*a) * cos(2.5 * time + 19.7*b)) * 0.2 +1.0;
    d.y  = (sin(1.7*time + 9.3*c) * cos(1.2*time + 8.4*a) * sin(2.3 * time + 8.6*b)) * 0.3 +1.0;
    d.z  = (cos(1.8*time + 7.3*c) * sin(2.3*time +  6.45*a) * sin(2.45 * time + 5.64*b)) * 0.05 +0.85;
   
   //d.x = 0.0;
   //d.y = 0.0;
   //d.z = 1.0;
   
    vec3 d2 = vec3((d.x+d.y)/1.8, (d.x+d.y)/2.2, d.z);
    
    //vec3 d2 = d;
    
    d2 -=  vec3(cos(1.5*c - 3.04) * cos(3.0*a) * sin(5.0*b + 2.56) *0.5 +  sin(1.5*c) *  cos(2.5*a + 4.56) * sin(2.8*b) *0.5) +0.2;
    
   
    //c = vec3(sin(3.0*a) * sin(5.0*b));
    
    return d2; 

}

void main(void)
{
	float d = min(dist[0],min(dist[1],dist[2]));
	float dMax = max(dist[0],max(dist[1],dist[2]));
 	float I = exp2(-0.3*d*d);

    vec4 fill = FILL_COL;
    fill.x = verpos.x;
    fill.y = verpos.y;
    fill.z = verpos.z;
    
    fill = vec4(genTex2(verpos.xyz), 1.0);
    
 	gl_FragColor = I*WIRE_COL + (0.2 + 0.8 * ( 1 - I) )*fill;
 	
 	if (gl_FrontFacing) {
        gl_FragColor = vec4(0.0,0.0,0.0,0.0);
    }  
 	
}

