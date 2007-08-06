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

	UpperPaneContentProvider contentProvider = new UpperPaneContentProvider(); 
	UpperPaneContentProvider settingsContentProvider = new UpperPaneContentProvider();
	
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
		
//		if( root != null ) {
//			VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
//				@Override public void Run() throws RuntimeException {
//					root.synchronize();
//				}
//			});
//		}
		
//		viewer.refresh();
		
		refresh();
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
		if( ! part.isImplValid() ) {
			System.err.println( "Warning, found invalid part: " + part.GetId() );
			return;
		}

		Iterator<Setting> settingIter = part.settingsIterator();
		while( settingIter.hasNext() ) {
			childs.add(settingIter.next());
		}
	}

	private class NodeSetting {
		private final VNodePtr node;
		private final String name;
		private String value;
		
		public NodeSetting(VNodePtr node, String name, String value) {
			this.node = node;
			this.name = name;
			this.value = value;
		}

		public String getValue() {
			return value;
		}
		
		private String updateValue() {
			VMessage requestMessage = new VMessage();
			requestMessage.AddProperty("type", "getSettings");
			
			VMessage answer = new VMessage();
			node.Send(requestMessage, answer);
			
			return answer.Get(name).ToString();
		}

		public void setValue(String value) {
			this.value = value;
		
			if( node != null && node.Get() != null ) {
				VMessage msg = new VMessage();
				msg.AddProperty("type", "update");
				msg.AddProperty("name", name);
				msg.AddProperty("value", value);

				try {
					node.Send(msg);
					value = updateValue();
				}
				catch(Throwable e) {
					System.err.println(e.getMessage());
					e.printStackTrace(System.err);
				}
			}
		}

		public VNodePtr getNode() {
			return node;
		}

		public String getName() {
			return name;
		}
	}
	
	private void addSettings(LinkedList<Object> childs, VNodePtr node) {
		VMessage requestMessage = new VMessage();
		requestMessage.AddProperty("type", "getSettings");
		
		VMessage answer = new VMessage();
		node.Send(requestMessage, answer);
		
		VStringIter nameIter = answer.PropertyIterator();
		while( nameIter.HasNext() ) {
			final String name = nameIter.Get();
			final String value = answer.Get(name).ToString();
			NodeSetting setting = new NodeSetting( node, name, value );
			
			childs.add( setting );
			
			nameIter.Next();
		}
	}
	
	private void addTags(LinkedList<Object> childs, VNodePtr node) {
		VTagIterator tags = node.Tags();
		while( tags.HasNext() ) {
			childs.add( new TagNode(tags.Get(), node) );
			tags.Next();
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
				
				if( ! targetFound )
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
	
	private static void addDependencies(LinkedList<Object> childs, VNodePtr node ) {
		if( node == null || node.Get() == null ) {
			System.err.println( "Warning, found invalid node" );
			return;
		}
		
		VNodeDependencyIterator depIter = node.Connections();
		
		while( depIter.HasNext() ) {
			VNodeDependency dep = depIter.Get();
			
			childs.add( new DependencyItem(dep) );
			
			depIter.Next();
		}
	}
	
	private static boolean isEntity(VNode node) {
		return node != null 
		&& node.GetTypeInfo().CanBeCastedTo("v3d::entity::VEntity");
	}
	
	private boolean isEditorInternal(VNode node) {
		if( node == null )
			return true;
		else
			return node.HasTag( EDITOR_INTERNAL_TAG );
	}
	
	private class UpperPaneContentProvider implements IStructuredContentProvider, ITreeContentProvider
	{
		VNodePtr rootNode = null;

		private boolean showEntities = true; 
		private boolean showSettings = true;
		
		public void setRootNode(VNodePtr newRootNode) {
			rootNode = newRootNode;
		}
		
		public boolean isShowEntities() {
			return showEntities;
		}

		public void setShowEntities(boolean showEntities) {
			this.showEntities = showEntities;
		}

		public boolean isShowSettings() {
			return showSettings;
		}

		public void setShowSettings(boolean showSettings) {
			this.showSettings = showSettings;
		}

		@Override public Object[] getElements(Object parent) {
			if( parent == null || root == null ) {
				return new Object[] {};
			}
			if( parent.equals(getViewSite()) ) {
				if( rootNode != null )
					return getChildren( rootNode );
				else
					return new Object[] { root.nodeptr() };
			}
			else {
				return getChildren(parent);
			}
		}

		@Override public void dispose() {
		}

		@Override public void inputChanged(Viewer viewer, Object oldInput, Object newInput) {
		}

		@Override public Object[] getChildren(Object parentElement) {
			final LinkedList<Object> childs = new LinkedList<Object>();
			
			if( parentElement instanceof VNodePtr ) {
				VNodePtr parentNode = (VNodePtr)parentElement;
				VNodePtrIterator child = parentNode.ChildPtrIterator();
				while( child.HasNext() ) {
					VNodePtr node = child.Get();
					
					if( ! isEditorInternal(node.Get()) ) {
						if( isEntity(node.Get()) ) {
							if( showEntities )
								childs.add( node );
						}
						else {
							childs.add( node );
						}
					}
					
					child.Next();
				}
				
				if( showSettings ) {
					addSettings( childs, parentNode );
					
					addDependencies( childs, parentNode );
					
					childs.add( new TagListNode(parentNode) );
				}
			}
			else if( parentElement instanceof TagListNode ) {
				TagListNode tagListNode = (TagListNode)parentElement;
				addTags( childs, tagListNode.node );  
			}
			
			return childs.toArray();
		}

		@Override public Object getParent(Object element) {
			return null;
		}

		@Override public boolean hasChildren(Object element) {
			return getElements(element).length > 0;
		}
	}

	class ViewLabelProvider extends LabelProvider {
		public String getText(Object obj) {
			if( obj instanceof VNodePtr ) {
				VNodePtr node = (VNodePtr)obj;
				
				if( node.Get() == null )
					return "!invalid!";
				
				String caption;
				
				if( isEntity(node.Get()) ) {
					caption = node.GetName();
				}
				else {
					caption = node.GetTypeInfo().GetName();
				}
				
				if( node.GetState() == VNode.State.Inactive ) {
					caption += " (inactive)";
				}
				
				boolean connected = true;
				VNodeDependencyIterator deps = node.Connections();
				while( deps.HasNext() ) {
					VNodeDependency dep = deps.Get();
					if( dep.GetCondition() == VNodeDependency.Condition.Mandatory 
							&& dep.GetTarget() == null )
					{
						connected = false;
					}
					
					deps.Next();
				}
				
				if( ! connected )
					caption += " (unconnected)";
				
				return caption;
			}
			else if( obj instanceof NodeSetting ) {
				NodeSetting setting = (NodeSetting) obj;
				
				return setting.getName() + " = " + setting.getValue();
			}
			else {
				return obj.toString();
			}
		}
		
		public Image getImage(Object obj) {
			Image image = null;
			String imageKey = null;

			if( obj instanceof VNodePtr ) {
				VNodePtr node = (VNodePtr) obj;
				
				if( isEntity(node.Get()) )
					imageKey = ISharedImages.IMG_OBJ_FOLDER;
				else
					imageKey = ISharedImages.IMG_OBJ_FILE;
			}
			else if( obj instanceof DependencyItem ) {
				DependencyItem depItem = (DependencyItem)obj;

				String imageName = null;
				if( depItem.optional )
					imageName = "icons/OptionalDependency.png";
				else if( depItem.targetFound )
					imageName = "icons/Dependency.png";
				else
					imageName = "icons/MissingDependency.png";

				image = VeloxEditorPlugin.getImage( imageName );
			}
			else if( obj instanceof NodeSetting )
				imageKey = ISharedImages.IMG_OBJS_TASK_TSK;
			else if( obj instanceof TagListNode || obj instanceof TagNode )
				imageKey = ISharedImages.IMG_OPEN_MARKER;
			else
				imageKey = ISharedImages.IMG_OBJ_ELEMENT;

			if( image == null )
				return PlatformUI.getWorkbench().getSharedImages().getImage(imageKey);
			else
				return image;
		}		
	}
	
//	class UpperPaneContentProvider implements IStructuredContentProvider, 
//										   ITreeContentProvider 
//	{
//		private Node rootNode = null;
//		private boolean showEntities = true; 
//		private boolean showSettings = true;
//		
//		UpperPaneContentProvider() {
//		}
//		
//		public void setRootNode(Node newRootNode) {
//			rootNode = newRootNode;
//		}
//		
//		public void setShowEntities(boolean newValue) {
//			showEntities = newValue;
//		}
//		
//		public void setShowSettings(boolean newValue) {
//			showSettings = newValue;
//		}
//		
//		public Object[] getElements(Object parent) {
//			if( parent == null || root == null ) {
//				return new Object[] {};
//			}
//			if (parent.equals(getViewSite())) {
//				if( rootNode != null )
//					return getChildren( rootNode );
//				else
//					return new Object[] { root };
//			}
//			else {
//				return getChildren(parent);
//			}
//		}
//
//		public void dispose() {
//		}
//
//		public void inputChanged(Viewer out_viewer, Object out_oldInput, Object out_newInput) {
//		}
//
//		public Object[] getChildren(Object parent) {
//			LinkedList<Object> childs = new LinkedList<Object>();
//
//			// if the object is an entity, add it's content
//			if( parent instanceof Entity ) {
//				Entity entity = (Entity)parent;
//				
//				if (entity.isImplValid()) {
//					// add sub entities
//					if( showEntities ) {
//						Iterator<Entity> entityIter = entity.EntityIterator();
//						while (entityIter.hasNext()) {
//							childs.add(entityIter.next());
//						}
//					}
//
//					// add entity parts
//					Iterator<Part> partIter = entity.PartIterator();
//					while (partIter.hasNext()) {
//						childs.add(partIter.next());
//					}
//				} else {
//					System.err.println("Warning, found invalid node: "
//							+ entity.GetId());
//				}
//			}
//			// if the object is a part, add it's settings and values
//			else if( parent instanceof Part ) {
//				Part part = (Part)parent;
//				
//				if( part.isImplValid() ) {
//					addDependencies(childs, part);				
//					addSettings(childs, part);
//				}
//				else {
//					System.err.println("Warning, found invalid node: "
//							+ part.GetId());
//				}
//			}
//			
//			return childs.toArray();				
//		}
//
//		public Object getParent(Object out_element) {
//			return null;
//		}
//
//		public boolean hasChildren(Object parent) {
//			if( parent instanceof Entity ) {
//				Entity entity = (Entity)parent;
//				
//				// entity has childs if it has either sub entities or parts
//				return entity.EntityIterator().hasNext() ||
//					entity.PartIterator().hasNext();
//			}
//			else {
//				return false;
//			}
//		}
//	}
	
//	class LowerPaneContentProvider implements IStructuredContentProvider, 
//	ITreeContentProvider 
//	{
//		LowerPaneContentProvider() {
//		}
//		
//		public Object[] getElements(Object parent) {
//			if( parent == null ) {
//				return new Object[] {};
//			}
//			if (parent.equals(getViewSite())) {
//				final Entity selectedEntity = getSelectedEntity();
//				
//				if( selectedEntity != null ) {
//					return getChildren( selectedEntity );
//				}
//				else {
//					final Part selectedPart = getSelectedPart();
//					
//					return getChildren( selectedPart );
//				}
//			}
//			else {
//				return getChildren(parent);
//			}
//		}
//		
//		public void dispose() {
//		}
//		
//		public void inputChanged(Viewer out_viewer, Object out_oldInput, Object out_newInput) {
//		}
//		
//		public Object[] getChildren(Object parent) {
//			LinkedList<Object> childs = new LinkedList<Object>();
//
//			if( parent instanceof Entity ) {
//				Entity entity = (Entity)parent;
//				
//				addEntityChilds(childs, entity);
//			}
//			else if( parent instanceof Part ) {
//				Part part = (Part)parent;
//				
//				addPartChilds(childs, part);
//			}
//			else if( parent instanceof TagListNode ) {
//				TagListNode tagNode = (TagListNode)parent;
//				
//				addTags(childs, tagNode.part);
//			}
//			
//			return childs.toArray();				
//		}
//
//		private void addTags(LinkedList<Object> childs, Node part) {
//			VTagIterator tags = part.tags();
//			while( tags.HasNext() ) {
//				childs.add(new TagNode(tags.Get(), part));
//				tags.Next();
//			}
//		}
//
//		private void addEntityChilds(LinkedList<Object> childs, Entity entity) {
//			addDependencies(childs, entity);
//			addSettings(childs, entity);
//			childs.add(new TagListNode(entity));
//			
//			// add entity parts
//			Iterator<Part> partIter = entity.PartIterator();
//			while( partIter.hasNext() ) {
//				childs.add(partIter.next());
//			}
//		}
//
//		private void addPartChilds(LinkedList<Object> childs, Part part) {
//			addDependencies(childs, part);
//			addSettings(childs, part);
//			childs.add(new TagListNode(part));
//		}
//		
//		public Object getParent(Object out_element) {
//			return null;
//		}
//		
//		public boolean hasChildren(Object parent) {
//			if( parent instanceof Entity )
//				return ((Entity)parent).PartIterator().hasNext();
//			else if( parent instanceof Part )
//				return ((Part)parent).settingsIterator().hasNext();
//			else if( parent instanceof Setting )
//				return false;
//			else if( parent instanceof TagListNode ) {
//				TagListNode tagNode = (TagListNode)parent;
//				return tagNode.part.tags().HasNext();
//			}
//			else if( parent instanceof TagNode )
//				return false;
//			else
//				return true;
//		}
//	}
	
	private static class TagListNode {
		public TagListNode(VNodePtr node) {
			this.node = node;
		}

		private final VNodePtr node;
		
		public void addTag(String tagName) {
			node.AttachTag( v3d.GetTagRegistry().GetTagWithName(tagName) );
		}

		@Override public String toString() {
			return "Tags";
		}
	}
	
	private static class TagNode {
		public TagNode(VTag tag, VNodePtr node) {
			this.tag = tag;
			this.node = node;
		}
		
		private final VTag tag;
		private final VNodePtr node;
		
		@Override public String toString() {
			return tag.GetName();
		}

		public void remove() {
			node.RemoveTag( tag );
		}
	}
	
//	class ViewLabelProvider extends LabelProvider {
//
//		public String getText(Object obj) {
//			if( obj == null ) {
//				return "null";
//			}
//			else {
//				return obj.toString();
//			}
//		}
//		
//		public Image getImage(Object obj) {
//			Image image = null;
//			String imageKey = null;
//			
//			if( obj instanceof Entity )
//				imageKey = ISharedImages.IMG_OBJ_FOLDER;
//			else if( obj instanceof Part )
//				imageKey = ISharedImages.IMG_OBJ_FILE;
//			else if( obj instanceof DependencyItem ) {
//				DependencyItem depItem = (DependencyItem)obj;
//				
//				String imageName = null;
//				if( depItem.targetFound )
//					imageName = "icons/Dependency.png";
//				else
//					imageName = "icons/MissingDependency.png";
//				
//				image = VeloxEditorPlugin.getImage( imageName );
//			}
//			else if( getText(obj).matches("[AN].*") )
//				imageKey = ISharedImages.IMG_OBJS_INFO_TSK;
//			else if( getText(obj).equals("Tags") )
//				imageKey = ISharedImages.IMG_OPEN_MARKER;
//			else
//				imageKey = ISharedImages.IMG_OBJ_ELEMENT;
//
//			if( image == null )
//				return PlatformUI.getWorkbench().getSharedImages().getImage(imageKey);
//			else
//				return image;
//		}
//	}

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

	VNodePtr selectedEntity = null;
	private final VTag EDITOR_INTERNAL_TAG = v3d.GetTagRegistry().GetTagWithName("v3d-editor-internal");
	VNodePtr markerNode = createMarkerPart();
	
	
	private VNodePtr createMarkerPart() {
		VNodePtr markerPart = v3d.CreatePart( "v3d::scene::VShowSelectionPart" );
		markerPart.AttachTag( EDITOR_INTERNAL_TAG );
		
		return markerPart;
	}
	
	VNodePtr getSelectedNode() {
		Object selectedObject = getSelectedObject();
		
		if( selectedObject instanceof VNodePtr )
			return (VNodePtr)selectedObject;
		else
			return null;
	}

	private void changeSelectedNode() {
		if( markerNode == null || markerNode.Get() == null )
			return;

		final VNodePtr selectedNode = getSelectedNode();
		
		VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
			@Override public void Run() throws RuntimeException {
				if( selectedEntity != null && selectedEntity.Get() != null ) {
					markerNode.Deactivate();
					selectedEntity.Remove( markerNode );
				}
				
				if( selectedNode != null && selectedNode.Get() != null ) {
					selectedNode.Add( markerNode );
					markerNode.Activate();
				}
			}
		});
		
		selectedEntity = selectedNode;
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
		viewer.setContentProvider( contentProvider );
		contentProvider.setShowSettings( false );
		viewer.setLabelProvider(new ViewLabelProvider());
		viewer.setInput(getViewSite());

		settingsViewer = new TreeViewer(myParent, SWT.MULTI | SWT.H_SCROLL | SWT.V_SCROLL);
		DrillDownAdapter settingsDrillDownAdapter = new DrillDownAdapter(settingsViewer);
		settingsDrillDownAdapter.addNavigationActions(
			getViewSite().getActionBars().getToolBarManager());

		settingsContentProvider.setShowEntities( false );
		settingsViewer.setContentProvider( settingsContentProvider );
//		settingsViewer.setContentProvider(new LowerPaneContentProvider());
		settingsViewer.setLabelProvider(new ViewLabelProvider());
		settingsViewer.setInput(getViewSite());

		makeActions();
		hookContextMenu();
		hookDoubleClickAction();

		viewer.addSelectionChangedListener(new ISelectionChangedListener() {
			public void selectionChanged(SelectionChangedEvent event) {
				final VNodePtr selectedNode = getSelectedNode();
				
				if( selectedNode != null ) {
					settingsContentProvider.setRootNode(selectedNode);
					settingsViewer.refresh();
					settingsViewer.expandAll();
				}
				
				changeSelectedNode();
				
//				final Entity selectedEntity = getSelectedEntity();
////				final Part selectedPart = getSelectedPart();
//				
////				if( selectedEntity != null || selectedPart != null ) {
//				if( selectedEntity != null ) {
//					settingsContentProvider.setRootNode( selectedEntity.nodeptr() );
//					settingsViewer.refresh();
//					settingsViewer.expandAll();
//				}
//				
//				changeSelectedNode();
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
//				Entity selectedEntity = getSelectedEntity();
//				
//				if( selectedEntity != null )
//				{
//					Entity parent = selectedEntity.getParent();
//					
//					if( parent != null ) {				
//						parent.Remove(selectedEntity);
//					}
//				}
				
				VNodePtr selectedNode = getSelectedNode();
				
				if( selectedNode != null && selectedNode.GetParent() != null ) {
					settingsContentProvider.setRootNode( null );
					
					if( selectedNode.GetState() == VNode.State.Active ) {
						selectedNode.Deactivate();
					}
					
					selectedNode.GetParent().Remove( selectedNode );
				}
				
				refresh();
			}
			
			void update() {
				VNodePtr node = getSelectedNode();
				boolean canBeRemoved = node != null && node.GetParent() != null;
				setEnabled( canBeRemoved );
//				final boolean removeableEntitySelected = 
//					getSelectedEntity() != null && getSelectedEntity().getParent() != null;
//				setEnabled(removeableEntitySelected);
			}
		});
		
//		partContextActions.add(new SceneAction("Remove") {
//			@Override public void run() {
//				Part selectedPart = getSelectedPart();
//				
//				if( selectedPart != null )
//				{
//					Entity owner = selectedPart.getOwner();
//					
//					if( owner != null )
//						owner.Remove(selectedPart);
//				}
//				
//				settingsViewer.refresh();				
//			}
//		
//			@Override void update() {
//				setEnabled( 
//						getSelectedPart() != null && 
//						getSelectedPart().getOwner() != null);
//			}
//		});
		
		entityContextActions.add(new SceneAction("Add part") {
			public void run() {
				final VNodePtr selectedNode = getSelectedNode();
				
				if( selectedNode == null )
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
							selectedNode.Add( v3d.CreatePart(selection) );
						}
					});
				}
				
				refresh();								
			}
			
			void update() {
				setEnabled(getSelectedNode() != null);
			}
		});
		
		doubleClickAction = new SceneAction("") {
			public void run() {
				final NodeSetting selectedSetting = getSelectedSetting();
				
				if( selectedSetting == null )
					return;
				
				final InputDialog dialog = new InputDialog(myParent.getShell(),
						"Change value of " + selectedSetting.getName(), 
						"Value", 
						selectedSetting.getValue(),
						new IInputValidator() {
					public String isValid(String x) { return null; }
				});
				
				if( dialog.open() == InputDialog.OK ) {
					VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
						@Override
						public void Run() throws RuntimeException {
							selectedSetting.setValue(dialog.getValue());
						}
					});
					
					settingsViewer.refresh();
					settingsViewer.expandAll();
				}
			}
			
			@Override public void update() {}
		};
		
//		partContextActions.add(new SceneAction("Show XML") {
//			public void run() {
//				Object obj = getSelectedObject();
//				
//				if( obj != null && obj instanceof XMLSerializable ) {
//					XMLSerializable selected = (XMLSerializable)obj;
//					
//					IVXMLElement xmlElement = v3d.CreateXMLElement(""); 
//					selected.writeToXML(xmlElement);
//					String source = createFormattedSource(xmlElement);
//					showMessage(source);
//				}
//			}
//			
//			void update() {
//				setEnabled(getSelectedPart() != null || getSelectedEntity() != null);
//			}
//		});
		
		entityContextActions.add(new SceneAction("Activate") {
			public void run() {
//				final Entity entity = getSelectedEntity();
				final VNodePtr selectedNode = getSelectedNode();
				
				VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
					@Override public void Run() throws RuntimeException {
						if( selectedNode != null ) {				
							if( selectedNode.GetState() == VNode.State.Active )
								selectedNode.Deactivate();
							else
								selectedNode.Activate();
						}
					}
				});
				
				refresh();
			}
			
			void update() {
				if( getSelectedNode() != null ) {
					if( getSelectedNode().GetState() == VNode.State.Active )
						setText( "Deactivate" );
					else
						setText( "Activate" );
				}
				
				setEnabled( getSelectedNode() != null );
			}
		});
		
		entityContextActions.add(new SceneAction("Refresh") {
			public void run() {
//				VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
//					@Override public void Run() throws RuntimeException {
//						root.synchronize();
//					}
//				});
				refresh();
			}

			@Override void update() {}
		});

//		partContextActions.add(new SceneAction("Set look at"){
//			@Override public void run() {
//				final Part selectedPart = getSelectedPart();
//				
//				if( selectedPart == null )
//					return;
//				
//				String lookAt = askUser("Orient object", "Look at", "");
//				
//				if( lookAt != null ) {
//					VMessage message = new VMessage();
//					message.AddProperty("type", "update");
//					message.AddProperty("name", "direction");
//					message.AddProperty("value", lookAt);
//					selectedPart.Send(message);						
//				}
//			}
//			
//			@Override public void update() {
//				final Part selectedPart = getSelectedPart();
//				setEnabled(selectedPart != null && 
//					selectedPart.GetType().equalsIgnoreCase(
//						"v3d::entity::VRigidBodyPart"));
//			}
//		});

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
		
//		entityContextActions.add(new SceneAction("Update") {
//			void updatePart(Part part) {
//				if( part != null &&
//					part.GetPart() != null &&
//					part.GetPart().Get() != null )
//				{
//					v3d.UpdatePart(.0f, part.GetPart().Get());
//				}
//			}
//			
//			public void run() {
//				Entity selectedEntity = getSelectedEntity();
//				if( selectedEntity != null ) {
//					Iterator<Part> partIter = selectedEntity.PartIterator();
//					while(partIter.hasNext()) {
//						updatePart(partIter.next());
//					}
//				}
//			}
//			
//			public void update() {
//				setEnabled(getSelectedEntity() != null);
//			}
//		});
		
//		partContextActions.add(new SceneAction("Update") {
//			void updatePart(Part part) {
//				if( part != null &&
//					part.GetPart() != null &&
//					part.GetPart().Get() != null )
//				{
//					v3d.UpdatePart(.0f, part.GetPart().Get());
//				}
//			}
//			
//			@Override public void run() {
//				updatePart(getSelectedPart());
//			}
//		
//			@Override void update() {
//				boolean enable = false;
//				
//				Part selectedPart = getSelectedPart();
//				if( selectedPart != null && selectedPart.GetPart() != null )
//					enable = v3d.CanBeUpdated(selectedPart.GetPart().Get());
//				
//				setEnabled(enable);
//			}
//		});
		
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
							tagNode.addTag( dialog.getValue() );
//							tagNode.part.AttachTag(dialog.getValue());
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
	
				selectedTag.remove();
//				selectedTag.node.RemoveTag(selectedTag.tag.GetName());
				
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
	
	private NodeSetting getSelectedSetting() {
		IStructuredSelection selection = 
			(IStructuredSelection)settingsViewer.getSelection();
		Object selectedElement = selection.getFirstElement();
		
		if( selectedElement instanceof NodeSetting )
			return (NodeSetting)selectedElement;
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
