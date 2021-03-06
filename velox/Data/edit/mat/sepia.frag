uniform sampler2D image;

// texture size should be 512x512
const float step = 1.0 / 256.0;

void blur() {
	vec2 pos = gl_TexCoord[0].st;
	vec4 c1 = texture2D(image, pos + vec2(step, 0.0));
	vec4 c2 = texture2D(image, pos);
	vec4 c3 = texture2D(image, pos + vec2(0.0, step));
	vec4 c4 = texture2D(image, pos + vec2(step, step));
	gl_FragColor = (c1 + c2 + c3 + c4) / 4.0;
}

void sepia() {
	vec4 colorScale = vec4(.9, .8, .4, 1.0);
	vec2 pos = gl_TexCoord[0].st;
	vec4 color = texture2D(image, pos);
	float brightness = length(color.rgb) * 0.7;
	gl_FragColor = vec4(brightness, brightness, brightness, 1.0) * colorScale;
}

void defaultColor() {
	vec2 pos = gl_TexCoord[0].st;
	vec4 color = texture2D(image, pos);
	gl_FragColor = color;
}

void diff() {
	vec2 pos = gl_TexCoord[0].st;
	vec4 color = texture2D(image, pos);
	vec4 cu = texture2D(image, pos + vec2(.0, step));
	
	float diff = (color.w - cu.w);
	diff = smoothstep(.0, .01, diff);
	
	gl_FragColor = vec4(diff, diff, diff, 1.0) +
		0.2 * color;
//	gl_FragColor = color * diff;
}

uniform float v3d_TimeFraction60;

void disturb() {
	float d = v3d_TimeFraction60 * 3.1415 * 2.0 * 15;
	vec2 pos = gl_TexCoord[0].st;
	vec2 dist = vec2(sin(pos.y * 31.0 + d), sin(pos.x * 31.0 + d));
	dist *= .3;
	vec4 color = mix(
			texture2D(image, pos + dist * .01),
			vec4(0, 0, .5, 1.0),
			0.1);
	
	gl_FragColor = color;
}

void main(void) {
//	blur();
	sepia();
//	defaultColor();
//	diff();
//	disturb();

//	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
