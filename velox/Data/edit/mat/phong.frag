varying vec3 normal;
varying vec3 lightDir;

vec4 normal2Color(vec3 n) {
	return vec4( (n + vec3(1, 1, 1)) / 2.0, 1.0);
}

void main(void) {
//	gl_FragColor = normal2Color(lightDir);
//	gl_FragColor = normal2Color(normal);

	float brightness = max(dot(normal, lightDir), 0.0);
	
	vec4 baseColor = gl_LightSource[0].diffuse;
	
	if( brightness > 1.0 )
		gl_FragColor = vec4(1, 0, 0, 1);
	else if( brightness < 0.0 )
		gl_FragColor = vec4(0, 0, 1, 1);
	else
		gl_FragColor = baseColor * brightness;
/**/
}
