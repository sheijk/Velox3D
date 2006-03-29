uniform sampler2D scenetex;

uniform vec2 movement;

void main()
{
//	vec2 movement = vec2(1, 0);
	
	int stepCount = 8;
	gl_FragColor = texture2D(scenetex, gl_TexCoord[0].st);

	float scale = .3;
	vec2 tc = gl_TexCoord[0].st;

	vec2 mvDelta = movement / 200;
//	vec2 mvDelta = (mousePos - vec2(256, 256)) / 512.0 / 100;

	for(int i = 1; i < stepCount; ++i) {
		tc += mvDelta;
		gl_FragColor += texture2D(scenetex, tc) * scale;
		scale *= .7;
	}
}

/*
uniform sampler2D scenetex;

void main()
{
	float pixelSize = 1.0 / 512.0;

	vec2 movement = vec2(.0, .02);
	float stepCount = 16;
	
	gl_FragColor = vec4(0, 0, 0, 1);
	
	float scale = 1.0;
	
	for(float i = 0; i < stepCount; i += 1.0)
	{
		vec2 pos = gl_TexCoord[0].st + (i / stepCount * movement);
		
		gl_FragColor += texture2D(scenetex, pos) * scale;
		scale /= 1.1;
	}
	
//	vec2 coord1 = gl_TexCoord[0].st;
//	vec2 coord2 = vec2(gl_TexCoord[0].s + .005, gl_TexCoord[0].t);
	
//	gl_FragColor = texture2D(scenetex, coord1) + texture2D(scenetex, coord2);// + vec4(.5, 0, 0, 1);
}
*/

