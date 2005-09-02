package de.velox.editors;

import org.eclipse.ui.part.EditorPart;

import de.velox.v3d;

public abstract class VeloxEditorBase extends EditorPart {
	public VeloxEditorBase() {
		super();
		
		try {
			v3d.Initialize();
		} catch (Exception e) {
			e.printStackTrace(System.err);
		}
	}
}
