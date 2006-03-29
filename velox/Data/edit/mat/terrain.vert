varying vec3 normal;
varying vec3 lightDir;

void main(void) {
	gl_Position = ftransform();
	lightDir = normalize(gl_LightSource[0].position.xyz - (gl_ModelViewMatrix * gl_Vertex).xyz);
	normal = normalize(gl_NormalMatrix * gl_Normal);
}
