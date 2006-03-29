varying float depth;

void main(void) {
	gl_Position = ftransform();
	depth = gl_Position.z / 300.0;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
