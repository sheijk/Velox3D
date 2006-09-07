/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

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

