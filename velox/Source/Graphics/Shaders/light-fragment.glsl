varying vec4 normal;

void main()
{
	vec4 texColor = vec4(1, 1, 1, 1);
	vec4 lightCol = vec4(1, 1, 1, 1) * dot(vec4(normal, 1), vec4(0, 1, 0, 1));
	
	gl_FragColor = texColor * lightCol;
}

