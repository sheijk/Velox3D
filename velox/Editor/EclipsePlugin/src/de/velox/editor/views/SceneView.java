/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

package de.velox.editor.views;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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

import de.velox.*;
import de.velox.editor.VeloxEditorPlugin;
import de.velox.editor.entity.*;
import de.velox.editor.widgets.FilterDialog;


/**
 */
public class SceneView extends VeloxViewBase {
	private TreeViewer viewer;
	private TreeViewer settingsViewer;
	@SuppressWarnings("unused")
	private DrillDownAdapter drillDownAdapter;
	
//	private SceneAction addEntityAction = null;
//	private SceneAction addPartAction = null;
//	private SceneAction addSettingAction = null;
	private SceneAction doubleClickAction = null;
//	private SceneAction showXMLAction = null;
//	private SceneAction toggleAction = null;
//	private SceneAction removeAction = null;
	
	private LinkedList<SceneAction> entityContextActions = new LinkedList<SceneAction>();
	private LinkedList<SceneAction> partContextActions = new LinkedList<SceneAction>();
	
	private Composite myParent = null;
	
	private Entity root = new Entity("root");

	public void setEntity(Entity inEntity) {
		root = inEntity;
		
		if( root != null ) {
			VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
				@Override public void Run() throws RuntimeException {
					root.synchronize();
				}
			});
		}
		
		viewer.refresh();
	}
	
	private void refresh()
	{
		viewer.refresh();
		settingsViewer.refresh();
	}

	abstract class SceneAction extends Action
	{
		public SceneAction(String caption) {
			setText(caption);		
		}
		
		abstract void update();
		abstract public void run();
	}
	
	private static void addSettings(LinkedList<Object> childs, Node part) {
		Iterator<Setting> settingIter = part.settingsIterator();
		while( settingIter.hasNext() ) {
			childs.add(settingIter.next());
		}
	}

	private static final class DependencyItem {
		private final String targetType;
		private final boolean targetFound;
		private final boolean optional;
		
		private final String description;
		
		public DependencyItem(VNodeDependency dep) {
			targetType = dep.GetTypeInfo().GetName();
			targetFound = dep.GetTarget() != null;
			optional = dep.GetCondition() == VNodeDependency.Condition.Optional;
			
			description = getDescription();
		}
		
		@Override public String toString() {
			return description;
		}
		
		private String getDescription() {
			String description = "Dep: ";
			
			if( optional ) {
				description += "[" + targetType + "]";
				
				if( targetFound )
					description += " (unconnected)";
			}
			else {
				if( ! targetFound )
					description += "(missing) ";
				
				description += targetType;
			}
			
			return description;
		}
	}
	
	private static void addDependencies(LinkedList<Object> childs, Node part) {
		VNodeDependencyIterator depIter = part.dependencyIterator();
		
		while( depIter.HasNext() ) {
			VNodeDependency dep = depIter.Get();
			
			childs.add( new DependencyItem(dep) );
			
			depIter.Next();
		}
	}

	class UpperPaneContentProvider implements IStructuredContentProvider, 
										   ITreeContentProvider 
	{
		UpperPaneContentProvider() {
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
				
//				addDependencies(childs, entity);
//				addSettings(childs, entity);
			}
			// if the object is a part, add it's settings and values
			else if( parent instanceof Part ) {
				Part part = (Part)parent;
				
				addDependencies(childs, part);				
				addSettings(childs, part);
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
//				return entity.EntityIterator().hasNext();
				return entity.EntityIterator().hasNext() ||
					entity.PartIterator().hasNext();
			}
//			else if( parent instanceof Part ) {
//				return true;
//			}
			else {
				return false;
			}
		}
	}
	
	class LowerPaneContentProvider implements IStructuredContentProvider, 
	ITreeContentProvider 
	{
		LowerPaneContentProvider() {
		}
		
		public Object[] getElements(Object parent) {
			if( parent == null ) {
				return new Object[] {};
			}
			if (parent.equals(getViewSite())) {
				final Entity selectedEntity = getSelectedEntity();
				
				if( selectedEntity != null ) {
					return getChildren( selectedEntity );
				}
				else {
					final Part selectedPart = getSelectedPart();
					
					return getChildren( selectedPart );
				}
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

			if( parent instanceof Entity ) {
				Entity entity = (Entity)parent;
				
				addEntityChilds(childs, entity);
			}
			else if( parent instanceof Part ) {
				Part part = (Part)parent;
				
				addPartChilds(childs, part);
			}
			else if( parent instanceof TagListNode ) {
				TagListNode tagNode = (TagListNode)parent;
				
				addTags(childs, tagNode.part);
			}
			
			return childs.toArray();				
		}

		private void addTags(LinkedList<Object> childs, Node part) {
			VTagIterator tags = part.tags();
			while( tags.HasNext() ) {
				childs.add(new TagNode(tags.Get(), part));
				tags.Next();
			}
		}

		private void addEntityChilds(LinkedList<Object> childs, Entity entity) {
			addDependencies(childs, entity);
			addSettings(childs, entity);
			childs.add(new TagListNode(entity));
			
			// add entity parts
			Iterator<Part> partIter = entity.PartIterator();
			while( partIter.hasNext() ) {
				childs.add(partIter.next());
			}
		}

		private void addPartChilds(LinkedList<Object> childs, Part part) {
//			Iterator<VPartDependency> depIter = part.dependencyIterator();
//			while( depIter.hasNext() ) {
//				VPartDependency dep = depIter.next();
//				
//				String descr = "" + dep.GetLocation().toString().charAt(0);
//				
//				if( dep.GetCondition() == VPartDependency.Condition.Optional )
//					descr += "? ";
//				else
//					descr += " ";
//				
//				descr += dep.GetTypeInfo().GetName();
//				
//				if( dep.GetId().length() > 0 )
//					descr += "(id:" + dep.GetId() + ")";
//				
//				childs.add(descr);
//			}				
//			
//			// add all settings				
//			Iterator<Setting> settingIter = part.settingsIterator();
//			while( settingIter.hasNext() ) {
//				childs.add(settingIter.next());
//			}
			
			addDependencies(childs, part);
			addSettings(childs, part);
			childs.add(new TagListNode(part));
		}
		
		public Object getParent(Object out_element) {
			return null;
		}
		
		public boolean hasChildren(Object parent) {
			if( parent instanceof Entity )
				return ((Entity)parent).PartIterator().hasNext();
			else if( parent instanceof Part )
				return ((Part)parent).settingsIterator().hasNext();
			else if( parent instanceof Setting )
				return false;
			else if( parent instanceof TagListNode ) {
				TagListNode tagNode = (TagListNode)parent;
				return tagNode.part.tags().HasNext();
			}
			else if( parent instanceof TagNode )
				return false;
			else
				return true;
		}
	}
	
	private static class TagListNode {
		public TagListNode(Node part2) {
			part = part2;
		}

		private final Node part;

		@Override public String toString() {
			return "Tags";
		}
	}
	
	private static class TagNode {
		public TagNode(VTag tag, Node part) {
			this.tag = tag;
			this.part = part;
		}
		
		private final VTag tag;
		private final Node part;
		
		@Override public String toString() {
			return tag.GetName();
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
			Image image = null;
			String imageKey = null;
			
			if( obj instanceof Entity )
				imageKey = ISharedImages.IMG_OBJ_FOLDER;
			else if( obj instanceof Part )
				imageKey = ISharedImages.IMG_OBJ_FILE;
			else if( obj instanceof DependencyItem ) {
				DependencyItem depItem = (DependencyItem)obj;
				
				String imageName = null;
				if( depItem.targetFound )
					imageName = "icons/Dependency.png";
				else
					imageName = "icons/MissingDependency.png";
				
				image = VeloxEditorPlugin.getImage( imageName );
			}
			else if( getText(obj).matches("[AN].*") )
				imageKey = ISharedImages.IMG_OBJS_INFO_TSK;
			else if( getText(obj).equals("Tags") )
				imageKey = ISharedImages.IMG_OPEN_MARKER;
			else
				imageKey = ISharedImages.IMG_OBJ_ELEMENT;

			if( image == null )
				return PlatformUI.getWorkbench().getSharedImages().getImage(imageKey);
			else
				return image;
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
		
		SashForm sash = new SashForm(parent, SWT.VERTICAL);
		myParent = sash;
		
		viewer = new TreeViewer(myParent, SWT.MULTI | SWT.H_SCROLL | SWT.V_SCROLL);
		
		drillDownAdapter = new DrillDownAdapter(viewer);
		drillDownAdapter.addNavigationActions(
			getViewSite().getActionBars().getToolBarManager());
		viewer.setContentProvider(new UpperPaneContentProvider());
		viewer.setLabelProvider(new ViewLabelProvider());
		viewer.setInput(getViewSite());

		settingsViewer = new TreeViewer(myParent, SWT.MULTI | SWT.H_SCROLL | SWT.V_SCROLL);
		DrillDownAdapter settingsDrillDownAdapter = new DrillDownAdapter(settingsViewer);
		settingsDrillDownAdapter.addNavigationActions(
			getViewSite().getActionBars().getToolBarManager());
		settingsViewer.setContentProvider(new LowerPaneContentProvider());
		settingsViewer.setLabelProvider(new ViewLabelProvider());
		settingsViewer.setInput(getViewSite());

		makeActions();
		hookContextMenu();
		hookDoubleClickAction();

		viewer.addSelectionChangedListener(new ISelectionChangedListener() {
			public void selectionChanged(SelectionChangedEvent event) {
				final Entity selectedEntity = getSelectedEntity();
				final Part selectedPart = getSelectedPart();
				
				if( selectedEntity != null || selectedPart != null ) {
					settingsViewer.refresh();
					settingsViewer.expandAll();
				}				
			}
		});
		
//		settingsView.addSelectionChangedListener(new ISelectionChangedListener() {
//			public void selectionChanged(SelectionChangedEvent event) {
//				final Part selectedPart = getSelectedPart();
//				
//				if( selectedPart != null ) {
//					System.out.println("Selected part of type " + selectedPart.GetId());
//					// display all settings
//					Iterator<Setting> settingNameIter = selectedPart.settingsIterator();
//					while( settingNameIter.hasNext() ) {
//						Setting setting = settingNameIter.next();
//						
//						System.out.println(setting.GetName() + "=" + setting.GetValue());
//					}
//				}
//			}
//		});
		
		refresh();
				
		
//		Button test = new Button(myParent, SWT.DEFAULT);
//		test.setText("this be button!");
		
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
		
		refresh();
		*/
	}
	
	private void makeActions() {
		entityContextActions.add(new SceneAction("Add entity") {
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
				
				refresh();
			}
			
			void update() {
				setEnabled(getSelectedEntity() != null);
			}
		});
		
		entityContextActions.add(new SceneAction("Remove") {
			@Override
			public void run() {
				Entity selectedEntity = getSelectedEntity();
				
				if( selectedEntity != null )
				{
					Entity parent = selectedEntity.getParent();
					
					if( parent != null ) {				
						parent.Remove(selectedEntity);
					}
				}
				refresh();
			}
			
			void update() {
				final boolean removeableEntitySelected = 
					getSelectedEntity() != null && getSelectedEntity().getParent() != null;
				setEnabled(removeableEntitySelected);
			}
		});
		
		partContextActions.add(new SceneAction("Remove") {
			@Override public void run() {
				Part selectedPart = getSelectedPart();
				
				if( selectedPart != null )
				{
					Entity owner = selectedPart.getOwner();
					
					if( owner != null )
						owner.Remove(selectedPart);
				}
				
				settingsViewer.refresh();				
			}
		
			@Override void update() {
				setEnabled( 
						getSelectedPart() != null && 
						getSelectedPart().getOwner() != null);
			}
		});
		
		entityContextActions.add(new SceneAction("Add part") {
			public void run() {
				final Entity selectedEntity = getSelectedEntity();
				
				if( selectedEntity == null )
					return;

				LinkedList<String> options = new LinkedList<String>();
				VPartParserIter partParser = v3d.GetEntitySerializationService().PartParsers();
				while(partParser.HasNext())
				{
					options.add(partParser.Get().GetType());
					partParser.Next();
				}
				FilterDialog dialog = new FilterDialog(myParent.getShell(),
						"Add part", options);
				
				final String selection = dialog.open();
				
				if( selection != null ) 
				{
					VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
						@Override public void Run() throws RuntimeException {
							selectedEntity.Add(new Part(selection));				
						}
					});
				}
				
				refresh();								
			}
			
			void update() {
				setEnabled(getSelectedEntity() != null);
			}
		});
		
		doubleClickAction = new SceneAction("") {
			public void run() {
				final Setting selectedSetting = getSelectedSetting();
				
				if( selectedSetting == null )
					return;
				
				final InputDialog dialog = new InputDialog(myParent.getShell(),
						"Change value of " + selectedSetting.GetName(), 
						"Value", 
						selectedSetting.GetValue(),
						new IInputValidator() {
					public String isValid(String x) { return null; }
				});
				
				if( dialog.open() == InputDialog.OK ) {
					VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
						@Override
						public void Run() throws RuntimeException {
							selectedSetting.SetValue(dialog.getValue());
						}
					});
					
				}
				
				refresh();
			}
			
			@Override public void update() {}
		};
		
		partContextActions.add(new SceneAction("Show XML") {
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
		
		entityContextActions.add(new SceneAction("Activate") {
			public void run() {
				final Entity entity = getSelectedEntity();
				
				VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
					@Override public void Run() throws RuntimeException {
						if( entity != null ) {				
							if( entity.IsActive() )
								entity.Deactivate();
							else
								entity.Activate();
						}
					}
				});
				
				refresh();
			}
			
			void update() {
				if( getSelectedEntity() != null ) {
					setText(
						getSelectedEntity().IsActive() ? "Deactivate" : "Activate");
				}
				
				setEnabled(getSelectedEntity() != null);
			}
		});
		
		entityContextActions.add(new SceneAction("Refresh") {
			public void run() {
				VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
					@Override public void Run() throws RuntimeException {
						root.synchronize();
					}
				});
				refresh();
			}

			@Override void update() {}
		});

		partContextActions.add(new SceneAction("Set look at"){
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

		/*
		entityContextActions.add(new SceneAction("test dialog") {
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
		*/
		
		entityContextActions.add(new SceneAction("Update") {
			void updatePart(Part part) {
				if( part != null &&
					part.GetPart() != null &&
					part.GetPart().Get() != null )
				{
					v3d.UpdatePart(.0f, part.GetPart().Get());
				}
			}
			
			public void run() {
				Entity selectedEntity = getSelectedEntity();
				if( selectedEntity != null ) {
					Iterator<Part> partIter = selectedEntity.PartIterator();
					while(partIter.hasNext()) {
						updatePart(partIter.next());
					}
				}
			}
			
			public void update() {
				setEnabled(getSelectedEntity() != null);
			}
		});
		
		partContextActions.add(new SceneAction("Update") {
			void updatePart(Part part) {
				if( part != null &&
					part.GetPart() != null &&
					part.GetPart().Get() != null )
				{
					v3d.UpdatePart(.0f, part.GetPart().Get());
				}
			}
			
			@Override public void run() {
				updatePart(getSelectedPart());
			}
		
			@Override void update() {
				boolean enable = false;
				
				Part selectedPart = getSelectedPart();
				if( selectedPart != null && selectedPart.GetPart() != null )
					enable = v3d.CanBeUpdated(selectedPart.GetPart().Get());
				
				setEnabled(enable);
			}
		});
		
		partContextActions.add(new SceneAction("Add tag") {
			@Override public void run() {
				final TagListNode tagNode = getSelectedTagNode();
				
				if( tagNode == null ) {
					setEnabled(false);
					return;
				}
				
				final InputDialog dialog = new InputDialog(myParent.getShell(),
						"Add new tag", 
						"Name",
						"",
						new IInputValidator() {
					public String isValid(String x) { return null; }
				});
				
				if( dialog.open() == InputDialog.OK ) {
					VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
						@Override public void Run() throws RuntimeException {
							tagNode.part.AttachTag(dialog.getValue());
						}
					});
				}
				
				refresh();
			}

			@Override void update() {
				setEnabled(getSelectedTagNode() != null);
			}
		});
		
		partContextActions.add(new SceneAction("Remove tag") {
			@Override public void run() {
				final TagNode selectedTag = getSelectedTag();
				
				if( selectedTag == null ) {
					setEnabled(false);
					return;
				}
				
				selectedTag.part.RemoveTag(selectedTag.tag.GetName());
				
				refresh();
			}

			@Override void update() {
				setEnabled(getSelectedTag() != null);
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
		settingsViewer.addDoubleClickListener(new IDoubleClickListener() {
			public void doubleClick(DoubleClickEvent event) {
				doubleClickAction.run();
			}
		});
	}
	
	private TagListNode getSelectedTagNode() {
		Object selectedObject = getSelectedObjectInPartView();
		
		if( selectedObject instanceof TagListNode )
			return (TagListNode)selectedObject;
		else
			return null;
	}

	private TagNode getSelectedTag() {
		Object selectedObject = getSelectedObjectInPartView();
		
		if( selectedObject instanceof TagNode )
			return (TagNode)selectedObject;
		else
			return null;
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
	
	private Object getSelectedObjectInPartView() {
		IStructuredSelection selection = 
			(IStructuredSelection)settingsViewer.getSelection();
		return selection.getFirstElement();
	}
	
	private Part getSelectedPart() {
		Object selectedElement = getSelectedObjectInPartView();
		
		if( selectedElement instanceof Part ) {
			return (Part)selectedElement;
		}
		else {
			Object selectedUpperElement = getSelectedObject();
			
			if( selectedUpperElement instanceof Part )
				return (Part)selectedUpperElement;
			else
				return null;
		}
	}
	
	private Setting getSelectedSetting() {
		IStructuredSelection selection = 
			(IStructuredSelection)settingsViewer.getSelection();
		Object selectedElement = selection.getFirstElement();
		
		if( selectedElement instanceof Setting )
			return (Setting)selectedElement;
		else
			return null;
	}

	private Object getSelectedObject() {
		IStructuredSelection selection = 
			(IStructuredSelection)viewer.getSelection();
		
		Object selectedElement = selection.getFirstElement();
		return selectedElement;
	}
	
	/**
	 * returns the entity which is currently selected (if a part or a setting
	 * is selected, it's parent entity will be returned
	 */
	public Entity getActiveEntity() {
		Entity selectedEntity = getSelectedEntity();
		
		if( selectedEntity == null ) {
			Part selectedPart = getSelectedPart();
			if( selectedPart != null )
				selectedEntity = selectedPart.getOwner();
		}
		
		return selectedEntity;
	}
	
	private void hookContextMenu() {
		{
			MenuManager menuMgr = new MenuManager("#PopupMenu");
			menuMgr.setRemoveAllWhenShown(true);
			menuMgr.addMenuListener(new IMenuListener() {
				public void menuAboutToShow(IMenuManager manager) {
					fillEntityContextMenu(manager);
				}
			});
			Menu entityMenu = menuMgr.createContextMenu(viewer.getControl());
			viewer.getControl().setMenu(entityMenu);
			
			getSite().registerContextMenu(menuMgr, viewer);
		}
		
		{
			MenuManager menuMgrSettings = new MenuManager("#PopupMenu");
			menuMgrSettings.setRemoveAllWhenShown(true);
			menuMgrSettings.addMenuListener(new IMenuListener() {
				public void menuAboutToShow(IMenuManager manager) {
					fillPartContextMenu(manager);
				}
			});
			Menu partsMenu = menuMgrSettings.createContextMenu(settingsViewer.getControl());
			settingsViewer.getControl().setMenu(partsMenu);
			
			getSite().registerContextMenu(menuMgrSettings, viewer);
		}
	}
	
	private void fillEntityContextMenu(IMenuManager manager) {
		for(SceneAction action : entityContextActions) {
			action.update();
			manager.add(action);
		}
		
		manager.add(new Separator(IWorkbenchActionConstants.MB_ADDITIONS));
	}
	
	private void fillPartContextMenu(IMenuManager manager) {
		for(SceneAction action : partContextActions) {
			action.update();
			manager.add(action);
		}
		
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
