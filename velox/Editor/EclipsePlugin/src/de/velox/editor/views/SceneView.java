package de.velox.editor.views;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.part.*;
import org.eclipse.jface.viewers.*;
import org.eclipse.swt.custom.SashForm;
import org.eclipse.swt.graphics.Image;
import org.eclipse.jface.action.*;
import org.eclipse.jface.dialogs.IInputValidator;
import org.eclipse.jface.dialogs.InputDialog;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.*;
import org.eclipse.swt.widgets.Menu;
import org.eclipse.swt.SWT;
import org.eclipse.core.runtime.IAdaptable;

import de.velox.IVXMLAttribute;
import de.velox.IVXMLElement;
import de.velox.IVXMLNode;
import de.velox.VEntity;
import de.velox.VView;
import de.velox.VXMLAttributeIterator;
import de.velox.VXMLNodeIterator;
import de.velox.v3d;
import de.velox.editor.entity.*;


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
public class SceneView extends VeloxViewBase {
	private TreeViewer viewer;
	@SuppressWarnings("unused")
	private DrillDownAdapter drillDownAdapter;
	
	private Action addEntityAction = null;
	private Action addPartAction = null;
	private Action addSettingAction = null;
	private Action doubleClickAction = null;
	private Action showXMLAction = null;
	private Action toggleAction = null;
	
	private Composite myParent = null;
	
	private VView renderView = null;

	class ViewContentProvider implements IStructuredContentProvider, 
										   ITreeContentProvider 
	{
		private final Entity root;
		
		ViewContentProvider(VEntity inRoot) {
			root = new Entity("root", inRoot);
			
			root.Add(new Entity("emptyChild"));
			
			Entity childWithParts = new Entity("childWithParts");
			childWithParts.Add(new Part("noSettingsPart"));
			Part partWithSettings = new Part("partWithSettings");
			partWithSettings.SetSetting("setting1" ,"value1");
			partWithSettings.SetSetting("setting2" ,"value2");
			childWithParts.Add(partWithSettings);
			
			root.Add(childWithParts);
			
			Entity childWithSubEntities = new Entity("childWithSubs");
			Entity lala = new Entity("lala");
			Part lalaPart = new Part("blub");
			lalaPart.SetSetting("xyz", "abc");
			lala.Add(lalaPart);
			childWithSubEntities.Add(lala);
			
			root.Add(childWithSubEntities);			
		}
		
		public Object[] getElements(Object parent) {
			if (parent.equals(getViewSite())) {
				return new Object[] { root };
			}
			else {
				return getChildren(parent);
			}
		}

		public void dispose() {
		}

		public void inputChanged(Viewer out_viewer, Object out_oldInput, Object out_newInput) {
		}

		public Object[] getChildren(Object parent) {
			LinkedList<Object> childs = new LinkedList<Object>();

			// if the object is an entity, add it's content
			if( parent instanceof Entity ) {
				Entity entity = (Entity)parent;
				
				
				// add sub entities
				Iterator<Entity> entityIter = entity.EntityIterator();
				while( entityIter.hasNext() ) {
					childs.add(entityIter.next());
				}
				
				// add entity parts
				Iterator<Part> partIter = entity.PartIterator();
				while( partIter.hasNext() ) {
					childs.add(partIter.next());
				}
				
			}
			// if the object is a part, add it's settings and values
			else if( parent instanceof Part ) {
				Part part = (Part)parent;
				
				// add settings and their values
//				Iterator<String> settingNameIter = part.SettingNameIterator();
//				while( settingNameIter.hasNext() ) {
//					String name = settingNameIter.next();
//					String value = part.GetSetting(name);
//					
//					childs.add(name + "=" + value);
//				}
				
				Iterator<Setting> settingIter = part.settingsIterator();
				while( settingIter.hasNext() ) {
					childs.add(settingIter.next());
				}				
			}
//			else if( parent instanceof Setting ) {
//				Setting setting = (Setting)parent;
//				childs.addAll(setting.getChildSettings());
//			}
			
			return childs.toArray();				
		}

		public Object getParent(Object out_element) {
			return null;
		}

		public boolean hasChildren(Object parent) {
			if( parent instanceof Entity ) {
				Entity entity = (Entity)parent;
				
				// entity has childs if it has either sub entities or parts				
				return entity.EntityIterator().hasNext() ||
					entity.PartIterator().hasNext();
			}
			else if( parent instanceof Part ) {
				Part part = (Part)parent;
				
				return part.SettingNameIterator().hasNext();
			}
			else {
				return false;
			}
		}
	}
	
	class ViewLabelProvider extends LabelProvider {

		public String getText(Object obj) {
			if( obj instanceof Entity ) {
				Entity entity = (Entity)obj;
				
				return (entity.IsActive() ? "(E)" : "(e)") 
					+ " " + entity.GetName();
			}
			else if( obj instanceof Part ) {
				Part part = (Part)obj;
				
				return "(P) " + part.GetType();
			}
			else if( obj instanceof Setting ) {
				Setting setting = (Setting)obj;
				
				return setting.GetName() + "=" + setting.GetValue();
			}
			else {
				return obj.toString();
			}
		}
		
		public Image getImage(Object obj) {
			String imageKey = ISharedImages.IMG_OBJ_ELEMENT;
			return PlatformUI.getWorkbench().getSharedImages().getImage(imageKey);
		}
	}

	/**
	 * The constructor.
	 */
	public SceneView() {
	}

	/**
	 * This is a callback that will allow us
	 * to create the viewer and initialize it.
	 */
	public void createPartControl(Composite parent) {
		myParent = parent;
		
		SashForm splitter = new SashForm(myParent, SWT.DEFAULT);
		
		viewer = new TreeViewer(
			splitter, SWT.MULTI | SWT.H_SCROLL | SWT.V_SCROLL);
		
		Composite preview = new Composite(splitter, SWT.DEFAULT);
		renderView = new VView(preview.handle);
		
		drillDownAdapter = new DrillDownAdapter(viewer);
		drillDownAdapter.addNavigationActions(
			getViewSite().getActionBars().getToolBarManager());
		viewer.setContentProvider(
			new ViewContentProvider(renderView.GetSceneRoot()));
		viewer.setLabelProvider(new ViewLabelProvider());
		viewer.setInput(getViewSite());

		
		renderView.StartRendering();
		
//		Button button = new Button(splitter, SWT.DEFAULT);
//		button.setText("lala");

		makeActions();
		hookContextMenu();
		hookDoubleClickAction();
		
		viewer.refresh();
	}
	
	private void makeActions() {
		addEntityAction = new Action() {
			public void run() {
				// get selected entity
				Entity selectedEntity = getSelectedEntity();
				
				if( selectedEntity == null ) 
					return;
				
				// ask user for entity name
				InputDialog dialog = new InputDialog(myParent.getShell(),
						"Add entity",
						"Name",
						"",
						new IInputValidator(){
							public String isValid(String out_newText) {
								return null;
							}
						});
					
				// add entity
				if( dialog.open() == InputDialog.OK ) {
					String name = dialog.getValue();
					selectedEntity.Add(new Entity(name));
				}
				
				viewer.refresh();
			}
		};
		addEntityAction.setText("Add entity");
		
		addPartAction = new Action() {
			public void run() {
				Entity selectedEntity = getSelectedEntity();
				
				if( selectedEntity == null )
					return;
				
				InputDialog dialog = new InputDialog(myParent.getShell(),
					"Add part", "Type", "",
					new IInputValidator() {
						public String isValid(String x) { return null; }
					});
				
				if( dialog.open() == InputDialog.OK ) {
					String type = dialog.getValue();
					selectedEntity.Add(new Part(type));
				}
				
				viewer.refresh();								
			}
		};
		addPartAction.setText("Add part");
		
		addSettingAction = new Action() {
			public void run() {
				Part selectedPart = getSelectedPart();
				
				if( selectedPart == null )
					return;
				
				InputDialog dialog = new InputDialog(myParent.getShell(),
					"Add setting", "Name", "",
					new IInputValidator() {
						public String isValid(String x) { return null; }
					});
				
				if( dialog.open() == InputDialog.OK ) {
					String name = dialog.getValue();
					selectedPart.SetSetting(name, "...");
				}
				
				viewer.refresh();								
			}
		};
		addSettingAction.setText("Add setting");
		
		doubleClickAction = new Action() {
			public void run() {
				Setting selectedSetting = getSelectedSetting();
				
				if( selectedSetting == null )
					return;
				
				InputDialog dialog = new InputDialog(myParent.getShell(),
					"Change value of " + selectedSetting.GetName(), 
					"Value", 
					selectedSetting.GetValue(),
					new IInputValidator() {
						public String isValid(String x) { return null; }
					});
				
				if( dialog.open() == InputDialog.OK ) {
					selectedSetting.SetValue(dialog.getValue());
				}
				
				viewer.refresh();
			}
		};
		
		showXMLAction = new Action() {
			public void run() {
				Object obj = getSelectedObject();
				
				if( obj != null && obj instanceof XMLSerializable ) {
					XMLSerializable selected = (XMLSerializable)obj;
					
					IVXMLElement xmlElement = v3d.CreateXMLElement(""); 
					selected.ToXML(xmlElement);
					String source = createFormattedSource(xmlElement);
					showMessage(source);
				}
			}
		};
		showXMLAction.setText("Show XML");
		
		toggleAction = new Action() {
			public void run() {
				Entity entity = getSelectedEntity();
				
				if( entity != null ) {				
					if( entity.IsActive() )
						entity.Deactivate();
					else
						entity.Activate();
					
					viewer.refresh();
				}
			}
		};
		toggleAction.setText("Activate");
	}

	private static String createFormattedSource(IVXMLElement root) {
		StringBuffer source = new StringBuffer();
		
		source.append("<" + root.GetName());
		VXMLAttributeIterator attribIter = root.AttributeBegin();
		while(attribIter.HasNext()) {
			IVXMLAttribute attrib = attribIter.Get();
			source.append(" " + attrib.GetName() + "=\"" 
				+ attrib.GetValue().ToString() + "\"");			
			attribIter.Next();
		}
		source.append(">\n");
		
		VXMLNodeIterator nodeIter = root.ChildBegin();
		while(nodeIter.HasNext()) {
			IVXMLNode node = nodeIter.Get();
			IVXMLElement element = node.ToElement();
			
			if( element != null ) {
				String childSource = createFormattedSource(element);
				String indentedChildSource = childSource;
				
				Matcher m = Pattern.compile(".*\n").matcher(childSource);
				indentedChildSource = m.replaceAll("  $0");
				
				source.append(indentedChildSource);
			}
			
			nodeIter.Next();
		}
		
		source.append("</" + root.GetName() + ">\n");
		
		return source.toString();
	}
	
	private void hookDoubleClickAction() {
		viewer.addDoubleClickListener(new IDoubleClickListener() {
			public void doubleClick(DoubleClickEvent event) {
				doubleClickAction.run();
			}
		});
	}
	
	private Entity getSelectedEntity() {
		Object selectedElement = getSelectedObject();
		
		if( selectedElement instanceof Entity ) {
			Entity entity = (Entity)selectedElement;
			return entity;
		}
		else
			return null;
	}
	
	private Part getSelectedPart() {
		Object selectedElement = getSelectedObject();
		
		if( selectedElement instanceof Part )
			return (Part)selectedElement;
		else
			return null;
	}
	
	private Setting getSelectedSetting() {
		Object selected = getSelectedObject();
		
		if( selected instanceof Setting )
			return (Setting)selected;
		else
			return null;
	}

	private Object getSelectedObject() {
		IStructuredSelection selection = 
			(IStructuredSelection)viewer.getSelection();
		
		Object selectedElement = selection.getFirstElement();
		return selectedElement;
	}
	
	private void hookContextMenu() {
		MenuManager menuMgr = new MenuManager("#PopupMenu");
		menuMgr.setRemoveAllWhenShown(true);
		menuMgr.addMenuListener(new IMenuListener() {
			public void menuAboutToShow(IMenuManager manager) {
				fillContextMenu(manager);
			}
		});
		Menu menu = menuMgr.createContextMenu(viewer.getControl());
		viewer.getControl().setMenu(menu);
		getSite().registerContextMenu(menuMgr, viewer);
	}
	
	private void fillContextMenu(IMenuManager manager) {
		final boolean entitySelected = getSelectedEntity() != null;
		final boolean partSelected = getSelectedPart() != null;
		
		toggleAction.setEnabled(entitySelected);
		if( entitySelected ) {
			toggleAction.setText(
				getSelectedEntity().IsActive() ? "Deactivate" : "Activate");
		}
		manager.add(toggleAction);

		addEntityAction.setEnabled(entitySelected);		
		manager.add(addEntityAction);
		
		addPartAction.setEnabled(entitySelected);
		manager.add(addPartAction);
		
		addSettingAction.setEnabled(partSelected);
		manager.add(addSettingAction);
		
		showXMLAction.setEnabled(partSelected | entitySelected);
		manager.add(showXMLAction);
		
		manager.add(new Separator(IWorkbenchActionConstants.MB_ADDITIONS));
	}

	@SuppressWarnings("unused")
	private void showMessage(String message) {
		MessageDialog.openInformation(
			viewer.getControl().getShell(),
			"Scene Editor",
			message);
	}

	/**
	 * Passing the focus request to the viewer's control.
	 */
	public void setFocus() {
		viewer.getControl().setFocus();
	}
}