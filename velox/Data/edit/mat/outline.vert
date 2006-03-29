//varying float depth;

void main(void) {
	gl_Position = ftransform();
//	depth = (1.0 + gl_Position.x) / 2.0;
//	depth = -gl_Position.z;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
