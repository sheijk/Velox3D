uniform sampler2D mirrorTex;
uniform float time;

/*
struct Time {
	float value;
};
Time t;
*/

varying vec4 texCoord;

vec4 testTexture(vec4 pos)
{
	float r = .0f;
	float g = .0f;
	float b = .0f;
	
	if( pos.s < .1f || pos.s > .9f ||
		pos.t < .1f || pos.t > .9f )
	{
		r = 1.0f;
	}

	g = fract(pos.s);
	b = fract(pos.t);	
	
	return vec4(r, g, b, 1);
}

void main()
{
//	float time = t.value;
	
	texCoord /= texCoord.w *2;
	texCoord.x /= 4.0 / 3.0;
	texCoord += vec4(.5, .5, .5, 0);
	
	// add offset
	texCoord.x += .004 * sin(texCoord.y * 400 + time * 4);
	
	gl_FragColor = mix(texture2D(mirrorTex, texCoord.xy), vec4(0, 0, .4, 1), .2);
}
