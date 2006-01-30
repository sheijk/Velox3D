package de.velox.editors;

import java.io.File;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.jface.action.Action;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.events.MouseMoveListener;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.swt.widgets.MessageBox;
import org.eclipse.ui.IActionBars;
import org.eclipse.ui.IEditorActionBarContributor;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IEditorPart;
import org.eclipse.ui.IEditorSite;
import org.eclipse.ui.IFileEditorInput;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.PartInitException;
import de.velox.*;
import de.velox.editor.entity.*;
import de.velox.editor.views.RenderLayer;
import de.velox.editor.views.SceneView;

public class SceneEditor extends VeloxEditorBase {
	private VRenderFrameAction renderAction = null;
	private final VUpdateManagerCallAction updateAction = new VUpdateManagerCallAction();
	
	private RenderLayer renderLayer = null;
	private RootEntity root = null;
	
	private String fileName = "";
	private String name = "";
	
	public SceneEditor() {
	}

	@Override
	public void doSave(IProgressMonitor monitor) {
		if( fileName == "" ) {
			doSaveAs();
		}
		else {
			saveToFile(fileName);
		}
	}

	@Override
	public void doSaveAs() {
		// get file name from user
		FileDialog fileDialog = new FileDialog(this.getSite().getShell());
		fileDialog.setFileName(fileName);
		
		final String newFileName = fileDialog.open();
		
		if( newFileName != null ) {
			fileName = newFileName;
			
			// save file
			saveToFile(newFileName);
		}
	}
	
	private void setRootEntity(RootEntity newRoot) {
		root = newRoot;

		if( renderAction != null ) {
			root.setRenderAction(renderAction);
		}
		
		if( ! VView.GetInstance().Contains(updateAction) ) {
			updateAction.SetEntity(root.impl());
			VView.GetInstance().Add(updateAction);			
		}
	}
	
	private void saveToFile(String fileName) {
		File file = new File(fileName);
		System.out.println("Saving to file " + fileName 
				+ " (absolute path: " + file.getAbsolutePath());
		
		IVXMLElement xml = v3d.CreateXMLElement("scene");
		root.writeToXML(xml);
		v3d.SaveXMLElementToFileNoVFS(xml, fileName);
		
		//TODO fire property change of dirty flag
	}
	
	private void loadFromFile(String fileName) {
		VXMLElementPtr xml = v3d.GetXMLService().GetRootElement(fileName);
		setRootEntity(new RootEntity(xml.Get()));
	}
	
	private void createNewScene() {
		setRootEntity(new RootEntity(fileName));

		root.Add(new Part("scene"));
	}

	@Override
	public void init(IEditorSite site, IEditorInput input) throws PartInitException {
		if( input instanceof IFileEditorInput ) {
			IFileEditorInput fileInput = (IFileEditorInput)input;
			
			fileName = fileInput.getFile().getLocation().toOSString();
			
			try {
				loadFromFile(fileName);
			}
			catch(RuntimeException e) {
				createNewScene();
//				throw new PartInitException(
//					"Could not load scene: " + e.getMessage(), e);
			}

//			if( fileInput.exists() ) {
//				loadFromFile(fileName);
//			}
//			else {
//				createNewScene();
//			}
			
			name = fileInput.getName();
			root.SetName(name);
			setPartName(name);
			
			setInput(input);
			setSite(site);
		}
		else {
			throw new PartInitException("Can only edit file resources");
		}
	}

	@Override
	public boolean isDirty() {
		return true;
	}

	@Override
	public boolean isSaveAsAllowed() {
		return false;
	}

	@Override
	public void createPartControl(final Composite parent) {
		renderLayer = new RenderLayer(parent);
		renderLayer.addMouseListener(new MouseHandler());
		renderAction = renderLayer.getRenderAction();
		
		IVDevice device = renderAction.GetDevice();
		VMatrix44f viewMatrix = new VMatrix44f();
		viewMatrix.SetTransform(1.0f, 1.0f, -7.0f);
		device.SetMatrix(IVDevice.MatrixMode.ViewMatrix, viewMatrix);
		if( root != null )
			root.setRenderAction(renderAction);
		
		IActionBars bars = getEditorSite().getActionBars();
		
		Action playAction = new Action() {
			private boolean playing = false;
			private IVXMLElement preupdateScene = null;
			
			@Override
			public void run() {
				if( playing ) {
					updateAction.SetUpdateSpeedFactor(.0f);
					this.setText("Play");
					
					restoreScene();
				}
				else {
					updateAction.SetUpdateSpeedFactor(1.0f);
					this.setText("Pause");
					
					saveCurrentScene();
				}
				
				playing = ! playing;
			}
			
			void saveCurrentScene() {
				preupdateScene = v3d.CreateXMLElement(root.GetName());
				root.writeToXML(preupdateScene);
			}
			
			void restoreScene() {
				if( preupdateScene == null )
					return;
				
				root.applySettings(preupdateScene);
				
//				VXMLNodeIterator node = preupdateScene.ChildBegin();
//				while( node.HasNext() ) {
//					final IVXMLElement element = node.Get().ToElement();
//					if( element != null && element.GetName().AsCString().equalsIgnoreCase("entity") ) {
//						root.applySettings(element);
//					}
//				}
			}
		};
		playAction.setText("Play/Pause");
		
		bars.getToolBarManager().add(playAction);
	}

	@Override
	public void dispose() {
		super.dispose();
		
		if( SceneView.getDefaultInstance() != null ) {
			SceneView.getDefaultInstance().setEntity(null);
		}
		
		VView.GetInstance().Remove(updateAction);
	}

	@Override
	public void setFocus() {
		if( SceneView.getDefaultInstance() != null )
			SceneView.getDefaultInstance().setEntity(root);
	}

	private class MouseHandler implements RenderLayer.MouseEventListener
	{
		private VVector3f createVector(float x, float y, float z) {
			VVector3f vec = new VVector3f();
			vec.Set(x, y, z);
			return vec;
		}
		
		private void move(float x, float y, float z) {
			System.out.println("Moved by x=" + x + " y=" + y + "z=" + z);
			
			Entity selectedEntity = SceneView.getDefaultInstance().getActiveEntity();
			
			if( selectedEntity != null ) {
				VRBTransform transform = v3d.GetTransform(selectedEntity.impl());
				VVector3f newPos = transform.GetPosition();
				newPos.Add(createVector(x, y, z));
				transform.SetPosition(newPos);
				v3d.SetTransform(selectedEntity.impl(), transform);
			}
		}
		
		private final float moveScale = 1.0f / 100;
		
		private int lastX = 0;
		private int lastY = 0;
		private boolean leftDown = false;

		public void mouseDown(MouseEvent e) {
			if( e.button == 1 ) {
				leftDown = true;
				
				lastX = e.x;
				lastY = e.y;
			}
		}
		
		public void mouseUp(MouseEvent e) {
			if( e.button == 1 )
				leftDown = false;
		}
		
		public void mouseDoubleClick(MouseEvent e) {
		}
		
		public void mouseMove(MouseEvent e) {
			if( leftDown ) {
				float scale = moveScale;
				if( (e.stateMask & SWT.SHIFT) != 0 )
					scale *= 8;
				
				float dx = (e.x - lastX) * scale;
				float dy = -(e.y - lastY) * scale;
				float dz = 0;
				
				if( (e.stateMask & SWT.ALT)  != 0 ) {
					float t = dy;
					dy = dz;
					dz = t;
				}
				
				if( (e.stateMask & SWT.CONTROL) != 0 ) {
//					camera.RotateX(dy*10);
//					camera.RotateY(-dx*10);
//					camera.RotateZ(dz*10);
				}
				else {
					move(dx, dy, dz);
				}
				
				lastX = e.x;
				lastY = e.y;
			}
		}
	}
}
