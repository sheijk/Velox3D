package de.velox.editor.materials;

import de.velox.editor.wizards.TextWizardBase;

public class GLSLFragmentProgramWizard extends TextWizardBase {

	public GLSLFragmentProgramWizard() {
		super(source, "frag");
	}
	
	private final static String source =
		"\n" +
		"void main(void) {\n" +
		"	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n" +
		"}\n" +
		"\n";
}
