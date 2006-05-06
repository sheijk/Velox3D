uniform vec4 color;
uniform sampler2D texture;

void main(void) {
	gl_FragColor = color;
//	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	
//	vec2 tc = gl_TexCoord[0].xy;
//	gl_FragColor = tex2D(texture, tc);
//	gl_FragColor = vec4(tc.x, tc.y, 1.0, 1.0);
}
