varying vec3 normal;
varying vec3 lightDir;
uniform vec4 sourceColor;

vec4 normal2Color(vec3 n)
{
	return vec4( (n + vec3(1, 1, 1)) / 2.0, 1.0);
}

float diffuse()
{
	return max(dot(normal, lightDir), 0.0);
}

void main(void)
{
	vec4 invSourceColor = vec4(1,1,1,1) - sourceColor;
	float brightness = diffuse();
	
	vec4 diffuseColor = gl_LightSource[0].diffuse;
	
	if( brightness > 1.0 )
		gl_FragColor = vec4(1, 0, 0, 1);
	else if( brightness < 0.0 )
		gl_FragColor = vec4(0, 0, 1, 1);
	else
		gl_FragColor = invSourceColor * diffuseColor * brightness;
}
