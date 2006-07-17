uniform sampler2D image;
const vec2 step = vec2(0.0, 2.0) / 1024.0;
const int stepCount = 5;
const float glowAmount = 0.2;
const float stepFactor = 0.9;

vec4 contribution(vec4 imageColor) {
	float brightness = (imageColor.r + imageColor.g + imageColor.b) / 3.0;
	return imageColor * smoothstep(0.9, 1.0, brightness);
}

void main(void) {
	vec2 pos = gl_TexCoord[0].st;
	vec4 color = texture2D(image, pos);
//	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
	
	float factor = glowAmount;
	
	for(int i = 0; i < stepCount; ++i) {
		color += factor * contribution( texture2D(image, pos + i * step) );
		color += factor * contribution( texture2D(image, pos - i * step) );
		factor *= stepFactor;
	}

	color.w = 1.0;
	gl_FragColor = color;
}
