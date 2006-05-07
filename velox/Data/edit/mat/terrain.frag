uniform sampler2D mud;

const vec4 baseColor = vec4(1, 1, 1, 1);

varying vec3 normal;
varying vec3 lightDir;
varying vec2 texCoord;
varying vec3 eye;

vec4 normal2Color(vec3 n) {
	return vec4( (n + vec3(1, 1, 1)) / 2.0, 1.0);
}

void main(void) {
	float brightness = max(dot(normal, lightDir), 0.0);
	brightness = min(1, max(0, brightness));
	
	normal = normalize(normal);
	lightDir = normalize(lightDir);
	float specular = 0.0;
	
//	if( dot(normal, lightDir) > 0.0 )
	{
		vec3 half = normalize(eye + lightDir);
		specular = dot(
			normal, 
			half);
			//gl_LightSource[0].halfVector.xyz); 
		specular = min(1, max(0, specular));
		specular = pow(specular, 32);
	}
	
	vec4 surfaceColor = 
		baseColor * 
		texture2D(mud, texCoord);
		
	vec4 light = 
		gl_LightSource[0].ambient
		+ gl_LightSource[0].diffuse * brightness
		+ gl_LightSource[0].specular * specular;

	gl_FragColor = surfaceColor * light;
}
