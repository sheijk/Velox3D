package de.velox.editor.materials;

import de.velox.editor.wizards.TextWizardBase;

public class GLSLMaterialWizard extends TextWizardBase {
	public GLSLMaterialWizard() {
		super(source, "v3dmat");
	}

	private final static String source =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" + 
		"<effect version=\"1.0\">\n" + 
		"	<shaderPath>\n" + 
		"		<renderPass> \n" + 
		"			<state name=\"vertex-program\">\n" + 
		"				<iparam name=\"source\">\n" + 
		"varying float dir;\n" + 
		"\n" + 
		"void main(void) {\n" + 
		"	gl_Position = ftransform();	\n" + 
		"	dir = dot(gl_Normal, vec3(0, 1, 0));\n" + 
		"}\n" + 
		"				</iparam>\n" + 
		"			</state>\n" + 
		"			<state name=\"fragment-program\">\n" + 
		"				<iparam name=\"source\">\n" + 
		"varying float dir;\n" + 
		"\n" + 
		"void main(void) {\n" + 
		"	vec4 skyColor = vec4(0, 0, 0.5, 1);\n" + 
		"	vec4 groundColor = vec4(0, 0.5, 0, 1);\n" + 
		"	\n" + 
		"	gl_FragColor = mix(skyColor, groundColor, dir);\n" + 
		"}\n" + 
		"				</iparam>\n" + 
		"			</state>\n" + 
		"		</renderPass>\n" + 
		"	</shaderPath>\n" + 
		"</effect>\n"; 
		
}
