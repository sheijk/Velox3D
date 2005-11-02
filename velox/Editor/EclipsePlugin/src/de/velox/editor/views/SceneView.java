package de.velox.editor.views;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.part.*;
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
import de.velox.editor.entity.*;
import de.velox.editor.gui.ComboboxDialog;


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
	
//	private SceneAction addEntityAction = null;
//	private SceneAction addPartAction = null;
//	private SceneAction addSettingAction = null;
	private SceneAction doubleClickAction = null;
//	private SceneAction showXMLAction = null;
//	private SceneAction toggleAction = null;
//	private SceneAction removeAction = null;
	
	private LinkedList<SceneAction> contextMenuActions = new LinkedList<SceneAction>();
	
	private Composite myParent = null;
	
	private Entity root = new Entity("root");

	public void setEntity(Entity inEntity) {
		root = inEntity;
		root.synchronize();
		viewer.refresh();
	}

	class SceneAction extends Action
	{
		public SceneAction(String caption) {
			setText(caption);		
		}
		
		void update() {}
	}
	
	class ViewContentProvider implements IStructuredContentProvider, 
										   ITreeContentProvider 
	{
		ViewContentProvider() {
//			root.Add(new Entity("emptyChild"));
//			
//			Entity childWithParts = new Entity("childWithParts");
//			childWithParts.Add(new Part("noSettingsPart"));
//			Part partWithSettings = new Part("partWithSettings");
//			partWithSettings.SetSetting("setting1" ,"value1");
//			partWithSettings.SetSetting("setting2" ,"value2");
//			childWithParts.Add(partWithSettings);
//			
//			root.Add(childWithParts);
//			
//			Entity childWithSubEntities = new Entity("childWithSubs");
//			Entity lala = new Entity("lala");
//			Part lalaPart = new Part("blub");
//			lalaPart.SetSetting("xyz", "abc");
//			lala.Add(lalaPart);
//			childWithSubEntities.Add(lala);
//			
//			root.Add(childWithSubEntities);			
		}
		
		public Object[] getElements(Object parent) {
			if( parent == null || root == null ) {
				return new Object[] {};
			}
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
				
				String dependencyList = "Dependencies: ";
				boolean firstDep = true;
				Iterator<VPartDependency> depIter = part.dependencyIterator();
				while( depIter.hasNext() ) {
					VPartDependency dep = depIter.next();
					
					if( ! firstDep )
						dependencyList += ", ";
					
					dependencyList += dep.GetId() + "@" + dep.GetLocation();
					firstDep = false;
				}				
				childs.add(dependencyList);
				
				// add all settings				
				Iterator<Setting> settingIter = part.settingsIterator();
				while( settingIter.hasNext() ) {
					childs.add(settingIter.next());
				}
			}
			
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
				return true;
			}
			else {
				return false;
			}
		}
	}
	
	class ViewLabelProvider extends LabelProvider {

		public String getText(Object obj) {
			if( obj == null ) {
				return "null";
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
		if( defaultSceneView == null )
			defaultSceneView = this;
	}
	
	private static SceneView defaultSceneView = null;
	
	public static SceneView getDefaultInstance() {
		return defaultSceneView;
	}
	
	/**
	 * This is a callback that will allow us
	 * to create the viewer and initialize it.
	 */
	public void createPartControl(Composite parent) {
		myParent = parent;
		
		viewer = new TreeViewer(myParent, SWT.MULTI | SWT.H_SCROLL | SWT.V_SCROLL);
		
		viewer.addSelectionChangedListener(new ISelectionChangedListener() {
			public void selectionChanged(SelectionChangedEvent event) {
				final Part selectedPart = getSelectedPart();
//				final Entity selectedEntity = getSelectedEntity();
				
				if( selectedPart != null ) {
					System.out.println("Selected part of type " + selectedPart.GetId());
					// display all settings
					Iterator<Setting> settingNameIter = selectedPart.settingsIterator();
					while( settingNameIter.hasNext() ) {
						Setting setting = settingNameIter.next();
						
						System.out.println(setting.GetName() + "=" + setting.GetValue());
					}
				}
			}
		});
		
		drillDownAdapter = new DrillDownAdapter(viewer);
		drillDownAdapter.addNavigationActions(
			getViewSite().getActionBars().getToolBarManager());
		viewer.setContentProvider(new ViewContentProvider());
		viewer.setLabelProvider(new ViewLabelProvider());
		viewer.setInput(getViewSite());

		makeActions();
		hookContextMenu();
		hookDoubleClickAction();
		
		viewer.refresh();
		/*
		SashForm splitter = new SashForm(myParent, SWT.DEFAULT);
		
		viewer = new TreeViewer(
			splitter, SWT.MULTI | SWT.H_SCROLL | SWT.V_SCROLL);
		
		Composite preview = new Composite(splitter, SWT.DEFAULT);

		renderAction = new VRenderFrameAction(preview.handle);
		addSceneAndShootingToRoot();
		VView.GetInstance().Add(renderAction);
//		sceneRoot = createDefaultScene();
		
		drillDownAdapter = new DrillDownAdapter(viewer);
		drillDownAdapter.addNavigationActions(
			getViewSite().getActionBars().getToolBarManager());
		viewer.setContentProvider(new ViewContentProvider());
		viewer.setLabelProvider(new ViewLabelProvider());
		viewer.setInput(getViewSite());

//		Button button = new Button(splitter, SWT.DEFAULT);
//		button.setText("lala");

		makeActions();
		hookContextMenu();
		hookDoubleClickAction();
		
		viewer.refresh();
		*/
	}
	
	private void makeActions() {
//		addEntityAction = new SceneAction() {
		contextMenuActions.add(new SceneAction("Add entity") {
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
			
			void update() {
				setEnabled(getSelectedEntity() != null);
			}
		});
//		addEntityAction.setText("Add entity");
		
		contextMenuActions.add(new SceneAction("Remove") {
//		removeAction = new SceneAction() {
			@Override
			public void run() {
				Entity selectedEntity = getSelectedEntity();
				Part selectedPart = getSelectedPart();
				
				if( selectedEntity != null )
				{
					Entity parent = selectedEntity.getParent();
					
					if( parent != null ) {				
						parent.Remove(selectedEntity);
					}
				}
				else if( selectedPart != null )
				{
					Entity owner = selectedPart.getOwner();
					
					if( owner != null )
						owner.Remove(selectedPart);
				}
				
				viewer.refresh();
			}
			
			void update() {
				final boolean removeableEntitySelected = 
					getSelectedEntity() != null && getSelectedEntity().getParent() != null;
				final boolean removeablePartSelected = 
					getSelectedPart() != null && getSelectedPart().getOwner() != null;
				setEnabled(removeablePartSelected || removeableEntitySelected);
			}
		});
//		removeAction.setText("Remove");
		
		contextMenuActions.add(new SceneAction("Add part") {
			public void run() {
				Entity selectedEntity = getSelectedEntity();
				
				if( selectedEntity == null )
					return;

				LinkedList<String> options = new LinkedList<String>();
				VPartParserIter partParser = v3d.GetEntitySerializationService().PartParsers();
				while(partParser.HasNext())
				{
					options.add(partParser.Get().GetType());
					partParser.Next();
				}
				ComboboxDialog dialog = new ComboboxDialog(myParent.getShell(), 
						"Add part",	"Type",	"", options);
				
				String selection = dialog.open();
				
				if( selection != null ) 
				{
					selectedEntity.Add(new Part(selection));				
				}
				
				viewer.refresh();								
			}
			
			void update() {
				setEnabled(getSelectedEntity() != null);
			}
		});
		
		doubleClickAction = new SceneAction("") {
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
		
		contextMenuActions.add(new SceneAction("Show XML") {
//		showXMLAction = new SceneAction() {
			public void run() {
				Object obj = getSelectedObject();
				
				if( obj != null && obj instanceof XMLSerializable ) {
					XMLSerializable selected = (XMLSerializable)obj;
					
					IVXMLElement xmlElement = v3d.CreateXMLElement(""); 
					selected.writeToXML(xmlElement);
					String source = createFormattedSource(xmlElement);
					showMessage(source);
				}
			}
			
			void update() {
				setEnabled(getSelectedPart() != null || getSelectedEntity() != null);
			}
		});
//		showXMLAction.setText("Show XML");
		
		contextMenuActions.add(new SceneAction("Activate") {
//		toggleAction = new SceneAction() {
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
			
			void update() {
				if( getSelectedEntity() != null ) {
					setText(
						getSelectedEntity().IsActive() ? "Deactivate" : "Activate");
				}
				
				setEnabled(getSelectedEntity() != null);
			}
		});
		
		contextMenuActions.add(new SceneAction("Refresh") {
			public void run() {
				root.synchronize();
				viewer.refresh();
			}
		});

		contextMenuActions.add(new SceneAction("Set look at"){
			@Override public void run() {
				final Part selectedPart = getSelectedPart();
				
				if( selectedPart == null )
					return;
				
				String lookAt = askUser("Orient object", "Look at", "");
				
				if( lookAt != null ) {
					VMessage message = new VMessage();
					message.AddProperty("type", "update");
					message.AddProperty("name", "direction");
					message.AddProperty("value", lookAt);
					selectedPart.Send(message);						
				}
			}
			
			@Override public void update() {
				final Part selectedPart = getSelectedPart();
				setEnabled(selectedPart != null && 
					selectedPart.GetType().equalsIgnoreCase(
						"v3d::entity::VRigidBodyPart"));
			}
		});
		
		contextMenuActions.add(new SceneAction("test dialog") {
			public void run() {
				LinkedList<String> options = new LinkedList<String>();
				VPartParserIter partParser = v3d.GetEntitySerializationService().PartParsers();
				while(partParser.HasNext())
				{
					options.add(partParser.Get().GetType());
					partParser.Next();
				}
				ComboboxDialog dialog = new ComboboxDialog(myParent.getShell(), 
						"Add part",	"Type",	"", options);
				
				String selection = dialog.open();
				
				System.out.println("Selected option " + selection);
			}
		});
	}
	
	private String askUser(String inTitle, String inQuestion, String inDefaultArgument) {
		InputDialog dialog = new InputDialog(myParent.getShell(),
				inTitle, inQuestion, inDefaultArgument,
				new IInputValidator() {
					public String isValid(String x) { return null; }
				});
			
		if( dialog.open() == InputDialog.OK )
			return dialog.getValue();
		else
			return null;
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
//		final boolean entitySelected = getSelectedEntity() != null;
//		final boolean partSelected = getSelectedPart() != null;
		
		for(SceneAction action : contextMenuActions) {
			action.update();
			manager.add(action);
		}
/*		
		toggleAction.setEnabled(entitySelected);
		if( entitySelected ) {
			toggleAction.setText(
				getSelectedEntity().IsActive() ? "Deactivate" : "Activate");
		}
		manager.add(toggleAction);

		addEntityAction.setEnabled(entitySelected);		
		manager.add(addEntityAction);

		final boolean removeableEntitySelected = 
			entitySelected && getSelectedEntity().getParent() != null;
		final boolean removeablePartSelected = 
			partSelected && getSelectedPart().getOwner() != null;
		removeAction.setEnabled(removeablePartSelected || removeableEntitySelected);
		manager.add(removeAction);
		
		addPartAction.setEnabled(entitySelected);
		manager.add(addPartAction);
		
		addSettingAction.setEnabled(partSelected);
		manager.add(addSettingAction);
		
		showXMLAction.setEnabled(partSelected | entitySelected);
		manager.add(showXMLAction);
*/		
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