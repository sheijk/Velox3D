varying vec2 screenpos;

varying vec3 lightDir;
varying vec3 normal;

void main(void) {
    gl_Position = ftransform();
    //    screenpos = (gl_ModelViewMatrix * gl_Vertex).xy;
    screenpos = gl_Position.xy / gl_Position.z;

    normal = gl_NormalMatrix * gl_Normal.xyz;

	vec4 vertPos = gl_ModelViewMatrix * gl_Vertex;
	vec4 lightPos = gl_LightSource[0].position;
	lightDir = (lightPos - vertPos).xyz;
}
