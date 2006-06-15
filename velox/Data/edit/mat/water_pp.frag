uniform sampler2D image;

// texture size should be 512x512
const float step = 1.0 / 256.0;

void defaultColor() {
	vec2 pos = gl_TexCoord[0].st;
	vec4 color = texture2D(image, pos);
	gl_FragColor = color;
}

uniform float v3d_TimeFraction60;

void disturb() {
	float d = v3d_TimeFraction60 * 3.1415 * 2.0 * 15.0;
	vec2 pos = gl_TexCoord[0].st;
	vec2 dist = vec2(sin(pos.y * 31.0 + d), sin(pos.x * 31.0 + d));
	dist *= .3;
	vec4 color = mix(
			texture2D(image, pos + dist * .01),
			vec4(0.0, 0, 1.0, 1.0),
			0.0);
	
	gl_FragColor = color;
}

void main(void) {
//	defaultColor();
	disturb();

//	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
