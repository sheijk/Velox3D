varying float depth;

void main(void) {
//	float depth = gl_FragDepth;
//	depth = 0.01;
	if( depth != .0 )
		gl_FragColor = vec4(depth, 1.0, 0.0, depth);
	else
		gl_FragColor = vec4(.0, .0, 1.0, 1.0);
}
