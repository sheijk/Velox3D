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
import org.eclipse.jface.action.*;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.*;
import org.eclipse.swt.widgets.Menu;
import org.eclipse.swt.SWT;
import de.velox.IVResourceManager;
import de.velox.VResDataIterator;
import de.velox.VResource;
import de.velox.VResourceData;
import de.velox.VResourceIterator;
import de.velox.v3d;
import de.velox.editor.SyncAction;


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

public class ResourceView extends VeloxViewBase {
	private TreeViewer viewer;
	private DrillDownAdapter drillDownAdapter;
	private Action action1;
	private Action action2;
	private Action doubleClickAction;

	/** Provides the "tree" to be shown */
	class ViewContentProvider implements IStructuredContentProvider, 
										   ITreeContentProvider 
	{
		VResource root = null;

		public void inputChanged(Viewer v, Object oldInput, Object newInput) {
		}
		
		public void dispose() {
		}
		
		public Object[] getElements(Object parent) {
			if (parent.equals(getViewSite())) {
				if( root == null ) {
					root = v3d.GetResourceManager().GetResourceByName("/").__deref__();
				}
				
//				root.DumpInfo("#");
				
				return getChildren(root);
			}
			else {
				return getChildren(parent);
			}
		}
		
		/** Get parent of object */
		public Object getParent(Object child) {
			return null;
//			if( child instanceof VResource ) {
//				return ((VResource)child).get
//			}
//			else {
//				return null;
//			}
		}
		
		/** Get children of object */		
		public Object [] getChildren(Object parent) {
			if( parent instanceof VResource ) {
				VResource res = (VResource)parent;
				
				LinkedList<Object> childs = new LinkedList<Object>();
				
				VResourceIterator iter = res.ChildIterator();
				while( iter.HasNext() ) {
					VResource child = iter.Get();
					childs.add(child);
					iter.Next();
				}
				
				VResDataIterator data = res.DataIterator();
				while( data.HasNext() ) {
					childs.add(data.Get());
					data.Next();
				}
				
				return childs.toArray();				
			}

			return new Object[0];
		}
		
		/** Return whether the object has any children */
		public boolean hasChildren(Object parent) {
			if( parent instanceof VResource ) {
				VResource res = (VResource)parent;
				
				VResourceIterator iter = res.ChildIterator();
				VResDataIterator data = res.DataIterator();
				
				return iter.HasNext() || data.HasNext();
			}
			else { 
				return false;
			}
		}
	}

	/** Provides text and image labels for objects of the tree */
	class ViewLabelProvider extends LabelProvider {

		public String getText(Object obj) {
			if( obj instanceof VResource ) {
				VResource res = (VResource)obj;
				return res.GetName();
			}
			else if( obj instanceof VResourceData ) {
				VResourceData resdata = (VResourceData)obj;
				return resdata.GetTypeId().GetName();
			}
			else {
				return obj.toString();
			}
		}
		
		public Image getImage(Object obj) {
			String imageKey = ISharedImages.IMG_OBJ_ELEMENT;
			
			if( obj instanceof VResource )
				imageKey = ISharedImages.IMG_OBJ_FOLDER;
			else if( obj instanceof VResourceData )
				imageKey = ISharedImages.IMG_OBJ_FILE;

			return PlatformUI.getWorkbench().getSharedImages().getImage(imageKey);
		}
	}
	
	class NameSorter extends ViewerSorter {
	}

	/**
	 * The constructor.
	 */
	public ResourceView() {
	}

	/**
	 * This is a callback that will allow us
	 * to create the viewer and initialize it.
	 */
	public void createPartControl(Composite parent) {
		viewer = new TreeViewer(parent, SWT.MULTI | SWT.H_SCROLL | SWT.V_SCROLL);
		drillDownAdapter = new DrillDownAdapter(viewer);
		viewer.setContentProvider(new ViewContentProvider());
		viewer.setLabelProvider(new ViewLabelProvider());
		viewer.setSorter(new NameSorter());
		viewer.setInput(getViewSite());
		makeActions();
		hookContextMenu();
		hookDoubleClickAction();
		contributeToActionBars();
	}

	private void hookContextMenu() {
		MenuManager menuMgr = new MenuManager("#PopupMenu");
		menuMgr.setRemoveAllWhenShown(true);
		menuMgr.addMenuListener(new IMenuListener() {
			public void menuAboutToShow(IMenuManager manager) {
				ResourceView.this.fillContextMenu(manager);
			}
		});
		Menu menu = menuMgr.createContextMenu(viewer.getControl());
		viewer.getControl().setMenu(menu);
		getSite().registerContextMenu(menuMgr, viewer);
	}

	private void contributeToActionBars() {
		IActionBars bars = getViewSite().getActionBars();
		fillLocalPullDown(bars.getMenuManager());
		fillLocalToolBar(bars.getToolBarManager());
	}

	private void fillLocalPullDown(IMenuManager manager) {
		manager.add(action1);
		manager.add(new Separator());
		manager.add(action2);
	}

	private Object getSelectedObject() {
		IStructuredSelection selection = 
			(IStructuredSelection)viewer.getSelection();
		
		Object selectedElement = selection.getFirstElement();
		return selectedElement;
	}
	
	private VResource getSelectedResource() {
		Object selectedObj = getSelectedObject();
		if( selectedObj instanceof VResource ) {
			return (VResource)selectedObj;
		}
		else {
			return null;
		}
	}
	
	private VResourceData getSelectedResourceData() {
		Object selectedObj = getSelectedObject();
		if( selectedObj instanceof VResourceData ) {
			return (VResourceData)selectedObj;
		}
		else {
			return null;
		}
	}
	
	private void fillContextMenu(IMenuManager manager) {
		manager.add(new SyncAction("Notify change") {
			final VResourceData resdata = getSelectedResourceData();
			
			@Override protected void exec() {
				if( resdata != null ) {
					resdata.GetEnclosingResource().NotifyChanged(
							resdata.GetTypeId());
				}
			}
		});
//		manager.add(new Action(){
//			@Override public void run() {
//				VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
//					@Override public void Run() throws RuntimeException {
//						VResourceData resdata = getSelectedResourceData();
//						if( resdata != null ) {
//							resdata.GetEnclosingResource().NotifyChanged(
//									resdata.GetTypeId());
//						}
//					}
//				});
//			}
//		});
		
		manager.add(action1);
		manager.add(action2);
		manager.add(new Separator());
		drillDownAdapter.addNavigationActions(manager);
		// Other plug-ins can contribute there actions here
		manager.add(new Separator(IWorkbenchActionConstants.MB_ADDITIONS));
	}
	
	private void fillLocalToolBar(IToolBarManager manager) {
		manager.add(action1);
		manager.add(action2);
		manager.add(new Separator());
		drillDownAdapter.addNavigationActions(manager);
	}

	private void makeActions() {
		action1 = new Action() {
			public void run() {
				IVResourceManager resourceManager = v3d.GetResourceManager();
				resourceManager.DumpResourceInfo();
			}
		};
		action1.setText("Dump");
		action1.setToolTipText("Dump all resources to stdout");
//		action1.setImageDescriptor(PlatformUI.getWorkbench().getSharedImages().
//			getImageDescriptor(ISharedImages.IMG_OBJS_INFO_TSK));
		
		action2 = new Action() {
			public void run() {
				viewer.refresh();
			}
		};
		action2.setText("Refresh");
		action2.setToolTipText("Refresh resource tree");
//		action2.setImageDescriptor(PlatformUI.getWorkbench().getSharedImages().
//				getImageDescriptor(ISharedImages.IMG_OBJS_INFO_TSK));

		doubleClickAction = new Action() {
			public void run() {
				ISelection selection = viewer.getSelection();
				Object obj = ((IStructuredSelection)selection).getFirstElement();
				showMessage("Double-click detected on "+obj.toString());
			}
		};
	}

	private void hookDoubleClickAction() {
		viewer.addDoubleClickListener(new IDoubleClickListener() {
			public void doubleClick(DoubleClickEvent event) {
				doubleClickAction.run();
			}
		});
	}
	private void showMessage(String message) {
		MessageDialog.openInformation(
			viewer.getControl().getShell(),
			"Sample View",
			message);
	}

	/**
	 * Passing the focus request to the viewer's control.
	 */
	public void setFocus() {
		viewer.getControl().setFocus();
	}
}
