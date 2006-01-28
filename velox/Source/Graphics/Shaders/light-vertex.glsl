varying vec4 normal;

void main()
{
	gl_Position = ftransform();
	normal = vec4(gl_NormalMatrix * gl_Normal, 1.0);
}
