/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

package de.velox.editor;

import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.plugin.*;
import org.eclipse.core.resources.IWorkspace;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.IPath;
import org.eclipse.jface.resource.ImageDescriptor;
import org.osgi.framework.BundleContext;

import de.velox.VRenderFrameAction;
import de.velox.VView;
import de.velox.v3d;
import de.velox.editor.views.RenderLayer;

import java.util.*;
 
/**
 * The main plugin class to be used in the desktop.
 */
public class VeloxEditorPlugin extends AbstractUIPlugin {
	private static VeloxEditorPlugin plugin;
	private ResourceBundle resourceBundle;
	
	private RenderLayer renderLayer = null;
	
	/**
	 * The constructor.
	 */
	public VeloxEditorPlugin() {
		super();
		plugin = this;
		
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
		
//		Shell shell = PlatformUI.getWorkbench().getDisplay().getActiveShell();
//		renderLayer = new RenderLayer( shell );
//		renderLayer.getRenderAction().GetDevice().Clear();
 	}  
    
 	/**
	 * This method is called upon plug-in activation
	 */
	public void start(BundleContext context) throws Exception {
		super.start(context);
	}

	/**
	 * This method is called when the plug-in is stopped
	 */
	public void stop(BundleContext context) throws Exception {
		super.stop(context);
		plugin = null;
		resourceBundle = null;
	
		VView.Shutdown();
//		VRenderFrameAction.ShutdownRendering();
	}

	/**
	 * Returns the shared instance.
	 */
	public static VeloxEditorPlugin getDefault() {
		return plugin;
	}

	/**
	 * Returns the string from the plugin's resource bundle,
	 * or 'key' if not found.
	 */
	public static String getResourceString(String key) {
		ResourceBundle bundle = VeloxEditorPlugin.getDefault().getResourceBundle();
		try {
			return (bundle != null) ? bundle.getString(key) : key;
		} catch (MissingResourceException e) {
			return key;
		}
	}

	/**
	 * Returns the plugin's resource bundle,
	 */
	public ResourceBundle getResourceBundle() {
		try {
			if (resourceBundle == null)
				resourceBundle = ResourceBundle.getBundle("veloxEditor.VeloxEditorPluginResources");
		} catch (MissingResourceException x) {
			resourceBundle = null;
		}
		return resourceBundle;
	}

	/**
	 * Returns an image descriptor for the image file at the given
	 * plug-in relative path.
	 *
	 * @param path the path
	 * @return the image descriptor
	 */
	public static ImageDescriptor getImageDescriptor(String path) {
		return AbstractUIPlugin.imageDescriptorFromPlugin("VeloxEditor", path);
	}

	/**
	 * Will return an image from the 'icons' directory
	 * 
	 * TODO: do this without recreating the image all the time :) (use an
	 * ImageRegistry)
	 */
	public static Image getImage(String path) {
		ImageDescriptor descriptor = getImageDescriptor(path);
		if( descriptor != null )
			return descriptor.createImage();
		else
			return null;
	}
}

