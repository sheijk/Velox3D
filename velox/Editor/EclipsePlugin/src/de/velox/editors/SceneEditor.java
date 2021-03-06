/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

package de.velox.editors;

import java.io.File;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.jface.action.Action;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.FocusEvent;
import org.eclipse.swt.events.FocusListener;
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
import de.velox.editor.SyncAction;
import de.velox.editor.entity.*;
import de.velox.editor.views.RenderLayer;
import de.velox.editor.views.SceneView;

public class SceneEditor extends VeloxEditorBase {
	private Composite parent = null;
	private VRenderFrameAction renderAction = null;
	private final VUpdateManagerCallAction updateAction = new VUpdateManagerCallAction();
	
	private RenderLayer renderLayer = null;
	private RootEntity root = null;
	
	private String fileName = "";
	/** true if the content of this file has not been loaded, yet.
	 * This will be set in loadFile if createPartControl has not been called yet
	 * (loading a file will require the opengl context to be created
	 */
	private boolean needsLoading = false;
	private String name = "";
	
	public SceneEditor() {
		try {
			v3d.Initialize();
		} catch (Exception e) {
			e.printStackTrace(System.err);
		}
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

		if( renderAction != null && root != null ) {
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
		
		final IVXMLElement xml = v3d.CreateXMLElement("scene");
		
		VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
			@Override public void Run() throws RuntimeException {
//				root.synchronize();
//				root.writeToXML(xml);
				if( root.impl() != null ) {
					root.impl().Save( xml );
				}
			}
		});
		
		v3d.SaveXMLElementToFileNoVFS(xml, fileName);
		
		//TODO fire property change of dirty flag
	}

	private static class Reference<T> {
		private T value = null;

		public Reference() {}
		
		public Reference(T value) {
			this.value = value;
		}
		
		public T get() { return value; }
		public void set(T newValue) { value = newValue; }
	};

	@SuppressWarnings("unused")
	private void showMessage(String message) {
		MessageDialog.openInformation(
			parent.getShell(),
			"Scene Editor",
			message);
	}
	
//	VNodePtr selectedEntity = null;
//	private final VTag EDITOR_INTERNAL_TAG = v3d.GetTagRegistry().GetTagWithName("v3d-editor-internal");
//	VNodePtr markerNode = createMarkerNode();
	
//	private VNodePtr createMarkerNode() {
//		VNodePtr root = v3d.CreatePart("v3d::entity::VEntity");
//		VNodePtr rigidBody = v3d.CreatePart("v3d::entity::VRigidBodyPart");
//		root.Add( rigidBody );
//		VNodePtr markerPart = v3d.CreatePart( "v3d::scene::VShowSelectionPart" );
//		root.Add( markerPart );
//		markerPart.AttachTag( EDITOR_INTERNAL_TAG );
//		
//		return root;
//	}

	private void loadFromFile(final String fileName) throws LoadSceneException {
		// we need a valid opengl context
		if( renderLayer != null ) {
			final Reference<RootEntity> rootEntity = new Reference<RootEntity>();
			final Reference<VXMLElementPtr> xml = new Reference<VXMLElementPtr>();
			final Reference<String> errorMessage = new Reference<String>();
			
			VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
				@Override public void Run() throws RuntimeException {
					try {
						xml.set( v3d.GetXMLService().GetRootElement(fileName) );
						rootEntity.set(new RootEntity(xml.get().Get()));
					}
					catch(Throwable t) {
						System.err.println("Error when loading scene: " + t.getMessage());
						t.printStackTrace(System.err);
						errorMessage.set( t.getMessage() );
					}
				}
			});
			
			if( rootEntity.get() != null ) {
				setRootEntity( rootEntity.get() );
				
				name = generateDisplayName(fileName);
				root.SetName(name);
				setPartName(name);
				
				VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
					@Override public void Run() throws RuntimeException {
//						rootEntity.get().impl().Add( markerNode );
						
						// activate here, because shooting is created in setRootEntity
						rootEntity.get().Activate();
						rootEntity.get().applySettings(xml.get().Get());
					}
				});
			}
			else {
				showMessage( "Could not open scene " + errorMessage.get() );
				throw new LoadSceneException( errorMessage.get() );
			}
			
			needsLoading = false;
		}
		else {
			needsLoading = true;
			this.fileName = fileName;
		}
	}

	private static String generateDisplayName(final String fileName) {
		Pattern pattern = Pattern.compile(".*[\\/\\\\]([^\\.]+)\\..*");
		Matcher matcher = pattern.matcher(fileName);

		if( matcher.find() )
			return matcher.group(1);
		else
			return fileName;
	}
	
	private void createNewScene() {
		setRootEntity(new RootEntity(fileName));
	}

	@Override
	public void init(IEditorSite site, IEditorInput input) throws PartInitException {
		if( input instanceof IFileEditorInput ) {
			IFileEditorInput fileInput = (IFileEditorInput)input;
			
			fileName = fileInput.getFile().getLocation().toOSString();
			
			try {
				loadFromFile(fileName);
			}
			catch(Throwable e) {
//				createNewScene();
				throw new PartInitException(
					"Could not load scene: " + e.getMessage(), e);
			}
						
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
		this.parent = parent;
		renderLayer = new RenderLayer(parent);
		renderLayer.addMouseListener(new MouseHandler());
		renderAction = renderLayer.getRenderAction();
		
		IVDevice device = renderAction.GetDevice();
		VRBTransform viewTransform = new VRBTransform();
		viewTransform.SetPosition( new VVector3f(1.0f, 1.0f, -7.0f) );
		device.SetViewTransform( viewTransform );
//		VMatrix44f viewMatrix = new VMatrix44f();
//		viewMatrix.SetTransform(1.0f, 1.0f, -7.0f);
//		device.SetMatrix(IVDevice.MatrixMode.ViewMatrix, viewMatrix);

		// delayed loading, if required (see above)
		if( needsLoading == true ) {
			try {
				loadFromFile(fileName);
			} catch (LoadSceneException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		if( root != null )
			root.setRenderAction(renderAction);
	}
	
	@Override
	public void dispose() {
		//TODO: this must happen _earlier_, before the widget (and it's windows
		// resources) are disposed. this happens before this method is called
		// thus causing crashes from time to time. find a notification/.. which
		// will be called before the window is closed, and put this call there
		//TODO: seems to be fixed
		renderLayer.windowClosed();

		super.dispose();
		
		if( SceneView.getDefaultInstance() != null ) {
			SceneView.getDefaultInstance().setEntity( null );
		}
		
		VView.GetInstance().Remove(updateAction);
		
	}

	@Override
	public void setFocus() {
		if( SceneView.getDefaultInstance() != null )
			SceneView.getDefaultInstance().setEntity( root.nodeptr() );
	}

	private static VVector3f createVector(float x, float y, float z) {
		VVector3f vec = new VVector3f();
		vec.Set(x, y, z);
		return vec;
	}
	
	private static final VVector3f X_AXIS = createVector(1, 0, 0);
	private static final VVector3f Y_AXIS = createVector(0, 1, 0);
	private static final VVector3f Z_AXIS = createVector(0, 0, 1);
	private enum Interaction { NONE, MOVE, ROTATE }
	private enum DominantDir { NONE, X, Y, Z }; 
		
	private class MouseHandler implements RenderLayer.MouseEventListener
	{
		
		VVector3f scaled(VVector3f vec, float factor) {
			VVector3f result = new VVector3f(vec);
			result.Scale(factor);
			return result;
		}
		
		private void move(float x, float y, float z) {
//			System.out.println("Moved by x=" + x + " y=" + y + "z=" + z);
			
			Entity selectedEntity = SceneView.getDefaultInstance().getActiveEntity();
			
			if( selectedEntity != null ) {
				VRBTransform transform = v3d.GetTransform(selectedEntity.impl());
				VVector3f newPos = transform.GetPosition();

//				VRBTransform viewrb = new VRBTransform(
//						renderLayer.getDevice().GetMatrix(
//								IVDevice.MatrixMode.ViewMatrix));
//				viewrb.SetXAxis(viewrb.GetXAxis().Normalized());
//				viewrb.SetYAxis(viewrb.GetYAxis().Normalized());
//				viewrb.SetZAxis(viewrb.GetZAxis().Normalized());

				if( dominantDir == DominantDir.NONE ) {
					decideDominantDirection(x, y, z);
				}
				
				if( dominantDir != DominantDir.X )
					x = .0f;
				if( dominantDir != DominantDir.Y )
					y = .0f;
				if( dominantDir != DominantDir.Z )
					z = .0f;

				newPos.Add( scaled(transform.GetXAxis(), -x) );
				newPos.Add( scaled(transform.GetYAxis(), y) );
				newPos.Add( scaled(transform.GetZAxis(), z) );
//				newPos.Add(createVector(x, y, z));
				
				transform.SetPosition(newPos);
				v3d.SetTransform(selectedEntity.impl(), transform);
			}
		}

		private void decideDominantDirection(float x, float y, float z) {
			final float absx = Math.abs(x);
			final float absy = Math.abs(y);
			final float absz = Math.abs(z);
			
			if( absx > absy && absx > absz ) {
				dominantDir = DominantDir.X;
			}
			if( absy > absx && absy > absz ) {
				dominantDir = DominantDir.Y;
			}
			if( absz > absx && absz > absy ) {
				dominantDir = DominantDir.Z;
			}
		}
		
		private void rotate(float angle, VVector3f axis) {
			Entity selectedEntity = SceneView.getDefaultInstance().getActiveEntity();
			
			if( selectedEntity != null ) {
				VRBTransform transform = v3d.GetTransform(selectedEntity.impl());
				transform.Rotate(angle, axis);
				v3d.SetTransform(selectedEntity.impl(), transform);
			}
		}
		
		private static final int MB_LEFT = 1;
		private static final int MB_RIGHT = 3;
				
		
		private final float moveScale = 1.0f / 100;
		private final float rotationScale = 1.0f;
		
		private int lastX = 0;
		private int lastY = 0;
		private boolean leftDown = false;
		private boolean rightDown = false;

		private DominantDir dominantDir = DominantDir.NONE;
		
		public void mouseDown(MouseEvent e) {
			dominantDir = DominantDir.NONE;
			
			if( e.button == MB_LEFT ) {
				leftDown = true;			
			}
			else if( e.button == MB_RIGHT ) {
				rightDown = true;
				System.out.println("right mouse released");
			}
			else {
				System.out.println("pressed button number " + e.button);
			}
			
			lastX = e.x;
			lastY = e.y;
		}
		
		public void mouseUp(MouseEvent e) {
			if( e.button == MB_LEFT )
				leftDown = false;
			else if( e.button == MB_RIGHT )
				rightDown = false;
		}
		
		public void mouseDoubleClick(MouseEvent e) {
		}
		
		public void mouseMove(MouseEvent e) {
			Interaction action = Interaction.NONE;
			float scale = 1.0f;
			
//			final boolean controlDown = (e.stateMask & SWT.CONTROL) != 0;
			final boolean shiftDown = (e.stateMask & SWT.SHIFT) != 0;
			final boolean altDown = (e.stateMask & SWT.ALT) != 0;
			
			float dx = (e.x - lastX) * scale;
			float dy = -(e.y - lastY) * scale;
			float dz = 0;
			
			lastX = e.x;
			lastY = e.y;
			
			if( leftDown ) {
				action = Interaction.MOVE;
			}
			else if( rightDown ) {
				action = Interaction.ROTATE;
			}
			
			if( action == Interaction.MOVE ) {
				scale *= moveScale;
				
				if( shiftDown )
					scale *= 8;
		
				if( altDown ) {
					float t = dy;
					dy = dz;
					dz = t;
				}
				
				move(dx, dy, dz);
			}
			else if( action == Interaction.ROTATE ) {
				scale *= rotationScale;
				
				if( shiftDown )
					scale *= .1f;
				
				if( altDown ) {
					dz = dy;
					dx = 0.0f;
					dy = 0.0f;
				}
				
				if( dominantDir == DominantDir.NONE ) {
					decideDominantDirection(dx, dy, dz);
				}
				
				if( dominantDir == DominantDir.X ) {
					dy = 0.0f;
					dz = 0.0f;
				}
				else if( dominantDir == DominantDir.Y ) {
					dx = 0.0f;
					dz = 0.0f;
				}
				else if( dominantDir == DominantDir.Z ) {
					dx = 0.0f;
					dy = 0.0f;
				}
				
				Entity selectedEntity = SceneView.getDefaultInstance().getActiveEntity();
				
				if( selectedEntity != null ) {
					VRBTransform transform = v3d.GetTransform(selectedEntity.impl());
				
					rotate(dy * scale, transform.GetXAxis());
					rotate(-dx * scale, transform.GetYAxis());
					rotate(dz * scale, transform.GetZAxis());
				}
			}
		}
	}

	private boolean playing = false;
	private IVXMLElement preupdateScene = null;

	private void saveCurrentScene() {
		preupdateScene = v3d.CreateXMLElement(root.GetName());
		root.writeToXML(preupdateScene);
	}
	
	public void restoreScene() {
		if( preupdateScene == null )
			return;

		root.applySettings(preupdateScene);
	}

	public void toggleRunScene() {
		VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
			@Override
			public void Run() throws RuntimeException {
				if( playing ) {
					updateAction.SetUpdateSpeedFactor(.0f);
					
//					restoreScene();
				}
				else {
					updateAction.SetUpdateSpeedFactor(1.0f);
					
					saveCurrentScene();
				}
				
				playing = ! playing;
			}
		});
	}

	public void enableInput() {
		VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
			@Override public void Run() throws RuntimeException {
				renderAction.SetIgnoreInput(false);
			}
		});
	}

	private static class LoadSceneException extends Exception {
		public LoadSceneException() {
			super();
		}

		public LoadSceneException(String arg0) {
			super(arg0);
		}
	}
}

