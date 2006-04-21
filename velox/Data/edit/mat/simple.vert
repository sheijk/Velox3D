
void main(void) {
	gl_Position = ftransform();
//	gl_Position.x += 0.1 * sin(gl_Position.y);
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
