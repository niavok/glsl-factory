#version 120
uniform vec3 lightDir;
varying vec3 normal;

//vec3 baseColor = vec3(0.09,0.46,0.0);
//vec3 baseColor = vec3(0.53, 0.62, 0.66);

void main()
{
    vec3 baseColor = vec3(gl_Color);
	float intensity;
	vec4 color;
	vec3 n = normalize(normal);
	vec3 p = normalize(vec3(gl_LightSource[0].position));
	intensity = dot(p,n);

	if (intensity > 0.95)
		color = vec4(baseColor,0.5);
	else if (intensity > 0.5)
		color = vec4(baseColor/1.5,0.5);
	else if (intensity > 0.25)
		color = vec4(baseColor/2.0,0.5);
	else
		color = vec4(baseColor/3.0,0.5);

    //color = vec4(intensity,0.1,0.1,1.0);
	gl_FragColor = color;
	//gl_FragColor = vec4(baseColor, gl_Color.w);
    
    if (!gl_FrontFacing) {
        gl_FragColor = vec4(0.0,0.0,0.0,0.0);
    }    
    
}

