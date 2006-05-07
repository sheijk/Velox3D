package de.velox.editor.materials;

import de.velox.editor.wizards.TextWizardBase;

public class GLSLVertexProgramWizard extends TextWizardBase {

	public GLSLVertexProgramWizard() {
		super(source, "vert");
	}
	
	private final static String source =
		"\n" +
		"void main(void) {\n" +
		"	gl_Position = ftransform();\n" +
		"}\n" +
		"\n";
}
