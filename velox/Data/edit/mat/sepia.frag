uniform sampler2D image;

const float step = 1.0 / 512.0;

void blur() {
	vec2 pos = gl_TexCoord[0].st;
	pos.x = 1.0 - pos.x;
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

void disturb() {
	vec2 pos = gl_TexCoord[0].st;
//	vec2 dist = vec2(sin(pos.x), sin(pos.y));
	vec2 dist = vec2(sin(pos.y * 31), sin(pos.x * 31));
	vec4 color = texture2D(image, pos + dist * .01);
//	vec4 color = texture2D(image, pos) + vec4(dist.x, dist.y, .0, 1.0);
	
	gl_FragColor = color;
}

void main(void) {
//	blur();
//	sepia();
	defaultColor();
//	diff();
//	disturb();

//	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}