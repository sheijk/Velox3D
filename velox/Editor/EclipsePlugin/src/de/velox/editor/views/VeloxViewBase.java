/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

/*
 * Created on Jul 14, 2005
 */
package de.velox.editor.views;

import org.eclipse.core.resources.IWorkspace;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.IPath;
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
		
//		try {
//			v3d.Initialize();
//		} catch (Exception e) {
//			e.printStackTrace(System.err);
//		}
	}
}

