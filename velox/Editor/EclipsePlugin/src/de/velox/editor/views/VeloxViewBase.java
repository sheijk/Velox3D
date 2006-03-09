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
		
		try {
			
			v3d.Initialize();
			
			// get the workspace directory
			IWorkspace workspace = ResourcesPlugin.getWorkspace();
			IPath workspaceDir = workspace.getRoot().getLocation();
			v3d.PrintLn("Workspace path = " + workspaceDir.toString());
			
			v3d.GetFileSystem().SetWorkingDir(workspaceDir.toString());
			
			IPath mountfile = workspaceDir.append("vfs.xml");
			if( mountfile.toFile().exists() ) {
				v3d.PrintLn("Found vfs.xml, mounting it");
				
				// look for vfs.xml and let the vfs load it if it exists
				v3d.GetFileSystem().MountFromXML(mountfile.toString());
			}
			else {
				v3d.PrintLn("No vfs.xml file found, nothing mounted");
			}
		} catch (Exception e) {
			e.printStackTrace(System.err);
		}
	}
}
