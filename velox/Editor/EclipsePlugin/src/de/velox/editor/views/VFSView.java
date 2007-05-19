/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

package de.velox.editor.views;

import java.util.LinkedList;

import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.part.*;
import org.eclipse.jface.viewers.*;
import org.eclipse.swt.graphics.Image;
import org.eclipse.jface.action.Action;
import org.eclipse.jface.action.IMenuManager;
import org.eclipse.jface.action.IToolBarManager;
import org.eclipse.jface.action.Separator;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.*;
import org.eclipse.swt.SWT;
import org.eclipse.core.runtime.IPath;

import org.eclipse.core.resources.*;

import de.velox.*;


/**
 * This sample class demonstrates how to plug-in a new
 * workbench view. The view shows data obtained from the
 * model. The sample creates a dummy model on the fly,
 * but a real implementation would connect to the model
 * available either in this or another plug-in (e.g. the workspace).
 * The view is connected to the model using a content provider.
 * <p>
 * The view uses a label provider to define how model
 * objects should be presented in the view. Each
 * view can present the same model objects using
 * different labels and icons, if needed. Alternatively,
 * a single label provider can be shared between views
 * in order to ensure that objects of the same type are
 * presented in the same way everywhere.
 * <p>
 */

public class VFSView extends VeloxViewBase {
	private TreeViewer viewer;
	private DrillDownAdapter drillDownAdapter;


	class ViewContentProvider implements IStructuredContentProvider, 
										   ITreeContentProvider {
		public void inputChanged(Viewer v, Object oldInput, Object newInput) {
		}
		
		public void dispose() {
		}
		
		public Object[] getElements(Object parent) {
			if (parent.equals(getViewSite())) {
				// get root dir
				IVDirectory dir = v3d.GetFileSystem().GetDir();
				
				return getChildren(dir);
			}
			else {
				return getChildren(parent);
			}
		}
		
		public Object getParent(Object child) {
			return null;
		}
		
		public Object [] getChildren(Object parent) {
			if (parent instanceof IVDirectory) {
				IVDirectory dir = (IVDirectory)parent;
				
				LinkedList<Object> childs = new LinkedList<Object>();
				
				VDirectoryIterator dirIter = dir.SubDirs();
				while( dirIter.HasNext() ) {
					childs.add( dirIter.Get() );
					dirIter.Next();
				}
				
				VFileIterator fileIter = dir.Files();
				while( fileIter.HasNext() ) {
					childs.add( fileIter.Get() );
					fileIter.Next();
				}
				
				return childs.toArray();
			}
			return new Object[0];
		}
		
		public boolean hasChildren(Object parent) {
			if (parent instanceof IVDirectory) {
				IVDirectory dir = (IVDirectory)parent;

				return dir.SubDirs().HasNext() ||
					dir.Files().HasNext();
			}
			return false;
		}
	}
	
	class ViewLabelProvider extends LabelProvider {

		public String getText(Object obj) {
			if( obj instanceof IVFileSystemObject ) {
				IVFileSystemObject fso = (IVFileSystemObject)obj;
				
				return fso.GetName().AsCString();
			}
			else {
				return "!Unknown object!";
			}
		}
		
		public Image getImage(Object obj) {
			String imageKey = ISharedImages.IMG_OBJ_ELEMENT;
			
			if( obj instanceof IVDirectory )
				imageKey = ISharedImages.IMG_OBJ_FOLDER;
			else if( obj instanceof IVFile )
				imageKey = ISharedImages.IMG_OBJ_FILE;

			return PlatformUI.getWorkbench().getSharedImages().getImage(imageKey);
		}
	}

	/**
	 * The constructor.
	 */
	public VFSView() {
//		// get the workspace directory
//		IWorkspace workspace = ResourcesPlugin.getWorkspace();
//		
//		IPath workspaceDir = workspace.getRoot().getLocation();
//		
//		v3d.PrintLn("Workspace path = " + workspaceDir.toString());
//		
//		IPath mountfile = workspaceDir.append("vfs.xml");
//		
//		if( mountfile.toFile().exists() ) {
//			v3d.PrintLn("Found vfs.xml, mounting it");
//			
//			// look for vfs.xml and let the vfs load it if it exists
//			v3d.GetFileSystem().MountFromXML(mountfile.toString());
//		}
//		else {
//			v3d.PrintLn("No vfs.xml file found, nothing mounted");
//		}
	}

	/**
	 * This is a callback that will allow us
	 * to create the viewer and initialize it.
	 */
	public void createPartControl(Composite parent) {
		viewer = new TreeViewer(parent, 
			SWT.MULTI | SWT.H_SCROLL | SWT.V_SCROLL);
		drillDownAdapter = new DrillDownAdapter(viewer);
		drillDownAdapter.addNavigationActions(
			getViewSite().getActionBars().getToolBarManager());
		viewer.setContentProvider(new ViewContentProvider());
		viewer.setLabelProvider(new ViewLabelProvider());
		viewer.setInput(getViewSite());
		
		makeActions();
		contributeToActionBars();
	}
	
	private Action dumpAction = null;
	private Action refreshAction = null;
	
	private void makeActions() {
		dumpAction = new Action(){
			@Override public void run() {
				v3d.DumpDir(v3d.GetFileSystem().GetDir("/"), "");
			}
		};
		dumpAction.setText("Dump");
		
		refreshAction = new Action() {
			@Override public void run() {
				viewer.refresh();
			}
		};
		refreshAction.setText("Refresh");
	}

	private void contributeToActionBars() {
		IActionBars bars = getViewSite().getActionBars();
//		fillLocalPullDown(bars.getMenuManager());
		fillLocalToolBar(bars.getToolBarManager());
	}

	private void fillLocalToolBar(IToolBarManager manager) {
		manager.add(dumpAction);
		manager.add(refreshAction);
//		drillDownAdapter.addNavigationActions(manager);
	}
	
	@SuppressWarnings("unused")
	private void showMessage(String message) {
		MessageDialog.openInformation(
			viewer.getControl().getShell(),
			"VFS Editor",
			message);
	}

	/**
	 * Passing the focus request to the viewer's control.
	 */
	public void setFocus() {
		viewer.getControl().setFocus();
	}
}
