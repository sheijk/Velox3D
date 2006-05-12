// vertex shader
varying float dir;
varying vec3 normal;

normal = normalize(gl_NormalMatrix * gl_Normal);
dir = 0.5 + normal.y/2;

// fragment shader
uniform vec4 groundColor;
uniform vec4 skyColor;

varying float dir;

vec4 sphericalAmbient() {
	return mix(groundColor, skyColor, dir);	
}
