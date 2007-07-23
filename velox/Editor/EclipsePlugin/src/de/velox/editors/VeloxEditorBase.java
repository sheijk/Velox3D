/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

package de.velox.editors;

import org.eclipse.ui.part.EditorPart;

import de.velox.v3d;

public abstract class VeloxEditorBase extends EditorPart {
	public VeloxEditorBase() {
		super();
		
//		try {
//			v3d.Initialize();
//		} catch (Exception e) {
//			e.printStackTrace(System.err);
//		}
	}
}

