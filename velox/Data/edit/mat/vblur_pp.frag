uniform sampler2D image;
const vec2 step = vec2(0.0, 2.0) / 1024.0;
const int stepCount = 16;
const float stepFactor = 1.0 / float(stepCount) / 2.0;

void main(void) {
	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
	vec2 pos = gl_TexCoord[0].st;
	
	float factor = 1.0;
	float totalBrightness = 0.;
	
	for(int i = 0; i < stepCount; ++i)	{
		color += factor * texture2D(image, pos + i * step);
		color += factor * texture2D(image, pos - i * step);
		totalBrightness += factor + factor;
		factor -= stepFactor;
	}

	color /= totalBrightness;
//	color -= texture2D(image, pos);
	color.w = 1.0;
	gl_FragColor = color;
}
