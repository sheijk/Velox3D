uniform mat4 cam;

varying vec4 texCoord;

void main()
{
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

//	texCoord = gl_Vertex;
//	texCoord = gl_MultiTexCoord0;
	texCoord = cam * gl_Vertex;
}

