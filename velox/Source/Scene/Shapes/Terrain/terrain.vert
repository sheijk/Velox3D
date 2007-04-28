attribute vec2 height;
attribute vec2 xz;

//varying vec3 normal;
varying vec4 color;
varying vec2 texCoord;
varying vec3 lightPos;

//const float regionSize = 128.0;
uniform float maskTexScale;
uniform vec2 maskTexOffset;

uniform float vertexScale;

vec4 dir2color(vec4 dir) {
	return (dir + vec4(1.0)) * 0.5;
}

void main(void) {
//    texCoord = xz / regionSize;
    texCoord = (xz + maskTexOffset) * maskTexScale;

	xz *= vertexScale;
	
	float h = mix( height.y, height.x, 
		smoothstep(0.0, 0.1, texCoord.x) * smoothstep(1.0, 0.9, texCoord.x)
		* smoothstep(0.0, 0.1, texCoord.y) * smoothstep(1.0, 0.9, texCoord.y)
		);
    
    vec4 vertex = vec4(xz.x, h, xz.y, 1.0);
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vertex;

//*
    vec3 normal = normalize( gl_NormalMatrix * gl_Normal );
    vec3 lightDir = normalize( gl_LightSource[0].position.xyz );
    float brightness = max( 0.0, dot(normal, lightDir) );
    color = gl_Color * brightness;    
/*/
	color = gl_Color;
	lightPos = gl_LightSource[0].position.xyz;
/**/    
/*
	normalMatrix = gl_NormalMatrix;
//    normal = normalize( gl_NormalMatrix * gl_Normal );
//    vec3 lightDir = normalize( gl_LightSource[0].position.xyz );
	lightDir = normalize( gl_LightSource[0].position.xyz );
//    float brightness = max( 0.0, dot(normal, lightDir) );
//    color = gl_Color * brightness;    
	color = gl_Color;
*/
}
