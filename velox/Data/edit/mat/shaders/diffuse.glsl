// vertex shader
varying vec3 lightDir;
lightDir = normalize(gl_LightSource[0].position.xyz - (gl_ModelViewMatrix * gl_Vertex).xyz);

// fragment shader
varying vec3 normal;
varying vec3 lightDir;

vec4 diffuse() {
	return max(dot(normal, lightDir), 0.0) *
		gl_LightSource[0].diffuse;
}
