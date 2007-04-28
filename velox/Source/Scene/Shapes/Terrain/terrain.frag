uniform sampler2D mask;

//uniform sampler2D ground;
//uniform vec2 groundOffset;
//uniform float groundScale;

uniform vec2 textureOffset;

uniform sampler2D colorTex;
uniform sampler2D normals;

varying vec4 color;
varying vec2 texCoord;
varying vec3 lightPos;

void main(void) {
	float cull = texture2D( mask, texCoord );
	
	if(	cull == 0.0 )
		discard;

	vec2 tc = texCoord + textureOffset;
/*	
	vec3 normal = texture2D(normals, tc).xyz;
	normal = (normal * 2.0) - vec3(1.0);
	normal = gl_NormalMatrix * normal;
	vec3 lightDir = normalize( lightPos );
	float brightness = max( 0.0, dot(normal, lightDir) );
*/
//	gl_FragColor = color * brightness;
	gl_FragColor = color * texture2D( colorTex, tc );

/*
	vec3 normal = normalize( normalMatrix * texture2D(normals, texCoord + groundOffset).xyz );
//	vec3 normal = normalize( texture2D(normals, texCoord + groundOffset).xyz );
	float brightness = max( 0.0, dot(normal, lightDir) );
//	gl_FragColor = vec4( (normal+vec3(1.0, 1.0, 1.0)) * 0.5, 1.0 );
	
	gl_FragColor = color * texture2D( ground, groundScale * (texCoord + groundOffset) ) * brightness;
//	gl_FragColor = vec4( groundOffset.x, groundOffset.y, 0.0, 1.0 );
//	gl_FragColor = color + vec4( groundOffset.x, groundOffset.y, 0.0, 0.0 );
*/
}

