/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

package de.velox.editor.views;

import java.util.LinkedList;
import java.util.List;

import org.eclipse.swt.widgets.Composite;
import org.eclipse.jface.viewers.*;
import org.eclipse.swt.graphics.Image;
import org.eclipse.jface.action.*;
import org.eclipse.jface.dialogs.IInputValidator;
import org.eclipse.jface.dialogs.InputDialog;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.*;
import org.eclipse.swt.widgets.Menu;
import org.eclipse.swt.SWT;

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

public class PropertiesView extends VeloxViewBase {
	private TableViewer viewer;
	private Action addAction;
	private Action refreshAction;
	private Action doubleClickAction;
	private Composite myParent = null;

	private static class Property {
		final String name;
		String value;
		
		public Property(String n, String v) {
			name = n;
			value = v;
		}

		public String getName() {
			return name;
		}

		public String getValue() {
			return value;
		}

		public void setValue(String out_value) {
			value = out_value;
		}
		
		public void apply() {
			VPropertyManager propertyManager = v3d.GetPropertyManager();
			propertyManager.SetValue(name, new VStringValue(value));
		}
		
		public String toString() {
			return name + "=" + value;
		}
	}
  	  
	/*
	 * The content provider class is responsible for
	 * providing objects to the view. It can wrap
	 * existing objects in adapters or simply return
	 * objects as-is. These objects may be sensitive
	 * to the current input of the view, or ignore
	 * it and always show the same content 
	 * (like Task List, for example).
	 */
	class ViewContentProvider implements IStructuredContentProvider {
		public void inputChanged(Viewer v, Object oldInput, Object newInput) {
		}
		public void dispose() {
		}
		public Object[] getElements(Object parent) {
			v3d.PrintLn("This is a test line");
			
			VPropertyManager propertyManager = v3d.GetPropertyManager();
			
			List<Property> strings = new LinkedList<Property>();
			VStringIter iter = propertyManager.GetPropertyNames();
			while( iter.HasNext() ) {
				String name = iter.Get();
				String value = v3d.ToString(propertyManager.GetValue(name));
				
				Property property = new Property(name, value);
				
				strings.add(property);
				iter.Next();
			}
			
			return strings.toArray();
		}
	}
	class ViewLabelProvider extends LabelProvider implements ITableLabelProvider {
		public String getColumnText(Object obj, int index) {
			return getText(obj);
		}
		public Image getColumnImage(Object obj, int index) {
			return getImage(obj);
		}
		public Image getImage(Object obj) {
			return PlatformUI.getWorkbench().
					getSharedImages().getImage(ISharedImages.IMG_OBJ_ELEMENT);
		}
	}
	class NameSorter extends ViewerSorter {
	}

	/**
	 * The constructor.
	 */
	public PropertiesView() {
	}

	/**
	 * This is a callback that will allow us
	 * to create the viewer and initialize it.
	 */
	public void createPartControl(Composite parent) {
		myParent = parent;
		viewer = new TableViewer(parent, SWT.MULTI | SWT.H_SCROLL | SWT.V_SCROLL);
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
				PropertiesView.this.fillContextMenu(manager);
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
		manager.add(addAction);
		manager.add(new Separator());
		manager.add(refreshAction);
	}

	private void fillContextMenu(IMenuManager manager) {
		manager.add(addAction);
		manager.add(refreshAction);
		// Other plug-ins can contribute there actions here
		manager.add(new Separator(IWorkbenchActionConstants.MB_ADDITIONS));
	}
	
	private void fillLocalToolBar(IToolBarManager manager) {
		manager.add(addAction);
		manager.add(refreshAction);
	}

	private void makeActions() {
		addAction = new Action() {
			public void run() {
				InputDialog dialog = new InputDialog(myParent.getShell(),
					"Add property", "Name", "", new IInputValidator(){
						public String isValid(String out_newText) {
							return null;
						}
					});
				
				int result = dialog.open();
				
				if( result == InputDialog.OK ) {
					String name = dialog.getValue();
					
					VPropertyManager propertyManager = v3d.GetPropertyManager();
					propertyManager.SetValue(name, 
						new VStringValue("newValue"));
					
					viewer.refresh();
				}
			}
		};
		addAction.setText("Add");
		addAction.setToolTipText("Adds a new property");
//		addAction.setImageDescriptor(PlatformUI.getWorkbench().getSharedImages().
//			getImageDescriptor(ISharedImages.IMG_OBJS_INFO_TSK));
		
		refreshAction = new Action() {
			public void run() {
				
				viewer.refresh();
			}
		};
		refreshAction.setText("Refresh");
		refreshAction.setToolTipText("Refresh the property list");
//		refreshAction.setImageDescriptor(PlatformUI.getWorkbench().getSharedImages().
//				getImageDescriptor(ISharedImages.IMG_OBJS_INFO_TSK));

		doubleClickAction = new Action() {
			public void run() {
				IStructuredSelection selection = 
					(IStructuredSelection)viewer.getSelection();
				
				Property prop = (Property)selection.getFirstElement();
				
				System.out.println("Selected: " + prop);
				
				InputDialog dialog = new InputDialog(myParent.getShell(),
						"Change property", 
						"New value of " + prop.getName(), 
						prop.getValue(), 
						new IInputValidator(){
							public String isValid(String out_newText) {
								return null;
							}
						});
					
				int result = dialog.open();
				
				if( result == InputDialog.OK ) {
					String value = dialog.getValue();
					prop.setValue(value);
					prop.apply();
				}
				
				viewer.refresh();
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
	@SuppressWarnings("unused")
	private void showMessage(String message) {
		MessageDialog.openInformation(
			viewer.getControl().getShell(),
			"Property Manager",
			message);
	}

	/**
	 * Passing the focus request to the viewer's control.
	 */
	public void setFocus() {
		viewer.getControl().setFocus();
	}
}
