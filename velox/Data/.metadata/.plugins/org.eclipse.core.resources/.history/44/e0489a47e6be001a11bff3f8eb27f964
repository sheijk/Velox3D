uniform sampler2D image;
//varying float depth;

void outline() {
	vec4 colorScale = vec4(depth, depth, depth, 1.0);
	
	vec2 pos = gl_TexCoord[0].st;
	vec4 color = texture2D(image, pos);
	gl_FragColor = color * colorScale;
	
//	float brightness = length(color.rgb) * 0.7;
//	gl_FragColor = vec4(brightness, brightness, brightness, 1.0) * colorScale;
}

void main(void) {
	outline();

//	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
