uniform vec3 inputRotation;
uniform vec2 resolution;
//float time = 1.0;
uniform float time;

float PI = 3.14159265358979323846264;

vec3 genTex2( in vec2 p1 )
{
    vec2 p = mod(p1, PI * 2.0);
    float a = sin(p.x);
    float b = sin(p.y);
    vec3 c = vec3(1.0);
    
    c.x  = (sin(1.1*time + 20.5*a) * cos(1.5 * time + 19.7*b)) * 0.2 +1.0;
    c.y  = (cos(1.2*time + 8.4*a) * sin(1.3 * time + 8.6*b)) * 0.3 +1.0;
    c.z  = (sin(1.3*time +  6.45*a) * sin(1.45 * time + 5.64*b)) * 0.05 +0.85;
   
   
    vec3 c2 = vec3((c.x+c.y)/2.0, (c.x+c.y)/2.0, c.z);
    
    
    c2 -=  vec3(cos(3.0*a) * sin(5.0*b + 2.56) *0.5 + cos(2.5*a + 4.56) * sin(3.0*b) *0.5);
    
   
    //c = vec3(sin(3.0*a) * sin(5.0*b));
    
    return c2; 

}

void main(void)
{
    vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
    vec2 uv;

    float r = sqrt( dot(p,p) );
    float a = atan(p.y,p.x) + 0.5*sin(0.5*r-0.5*time);

    float s = 0.5 + 0.5*cos(7.0*a);
    s = smoothstep(0.0,1.0,s);
    s = smoothstep(0.0,1.0,s);
    s = smoothstep(0.0,1.0,s);
    s = smoothstep(0.0,1.0,s);

    uv.x = time + 1.0/( r + .2*s);
    uv.y = 3.0*a/3.1416;

    float w = (0.5 + 0.5*s)*r*r;

    vec3 col = genTex2(uv).xyz;

    float ao = 0.5 + 0.5*cos(7.0*a);
    ao = smoothstep(0.0,0.4,ao)-smoothstep(0.4,0.7,ao);
    ao = 1.0-0.5*ao*r;

    gl_FragColor = vec4(col*w*ao,1.0);
}

