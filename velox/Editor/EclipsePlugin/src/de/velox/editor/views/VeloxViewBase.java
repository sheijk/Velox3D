/*
 * Created on Jul 14, 2005
 */
package de.velox.editor.views;

import org.eclipse.ui.part.ViewPart;

import de.velox.v3d;

/**
 * Abstract base class for all velox views. Assures that velox will be
 * properly initialized before any plugin is started
 * 
 * @author sheijk
 */
abstract class VeloxViewBase extends ViewPart {
	public VeloxViewBase() {
		super();
		
		try {
			v3d.Initialize();
		} catch (Exception e) {
			e.printStackTrace(System.err);
		}
	}
}
