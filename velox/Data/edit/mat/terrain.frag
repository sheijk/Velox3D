uniform sampler2D mud;
uniform vec4 mudColor;

const vec4 baseColor = vec4(1, 1, 1, 1);

varying vec3 normal;
varying vec3 lightDir;
varying vec2 texCoord;
varying vec3 eye;

vec4 normal2Color(vec3 n) {
	return vec4( (n + vec3(1, 1, 1)) / 2.0, 1.0);
}

void main(void) {
	float diffuse = max(dot(normal, lightDir), 0.0);
	diffuse = min(1.0, max(0.0, diffuse));
	
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
		specular = min(1.0, max(0.0, specular));
		specular = pow(specular, 32.0) * 0.4;
	}
	
	vec4 surfaceColor =
		0.9 * baseColor +
		0.1 * texture2D(mud, texCoord);
		
	vec4 light = 
		gl_LightSource[0].ambient
		+ gl_LightSource[0].diffuse * diffuse
		+ gl_LightSource[0].specular * specular;

	gl_FragColor = surfaceColor * light + mudColor;
}
