void main(void) {
//	gl_FragColor = texture2D(image, gl_TexCoord[0].st);
//	gl_FragColor = vec4(1.0, 0.5, 0.0, 1.0);

	float depth = gl_FragDepth;
	gl_FragColor = vec4(1.0, depth, depth, 1.);
}
