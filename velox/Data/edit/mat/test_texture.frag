uniform sampler2D image;

void main(void) {
	gl_FragColor = vec4(0.5, 0.0, 0.0, 1.0);
//	gl_FragColor = 
//		texture2D(image, gl_TexCoord[0].st)
//		+ vec4(0.0, 0.3, 0.0, 0.0);
}
