package de.velox.editors;

import java.io.File;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.FileDialog;
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
		root = new RootEntity(xml.Get());
		if( renderAction != null ) {
			root.setRenderAction(renderAction);
		}
	}
	
	private void createNewScene() {
		root = new RootEntity(fileName);
		if( renderAction != null ) {
			root.setRenderAction(renderAction);
		}

		root.Add(new Part("scene"));
		
//		Entity entity = new Entity("obj");
//		entity.Add(new Part("model"));
//		entity.Add(new Part("body"));
//		root.Add(entity);
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
				System.err.println("Could not load scene: " + e);
				createNewScene();
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
	public void createPartControl(Composite parent) {
//		SashForm splitter = new SashForm(parent, SWT.DEFAULT);

//		Composite preview = new Composite(splitter, SWT.DEFAULT);

		renderLayer = new RenderLayer(parent);
		renderAction = renderLayer.getRenderAction();
//		renderAction = new VRenderFrameAction(preview.handle);
//		VView.GetInstance().Add(renderAction);
		
		IVDevice device = renderAction.GetDevice();
		VMatrix44f viewMatrix = new VMatrix44f();
		viewMatrix.SetTransform(1.0f, 1.0f, -7.0f);
		device.SetMatrix(IVDevice.MatrixMode.ViewMatrix, viewMatrix);
		if( root != null )
			root.setRenderAction(renderAction);
	}

	@Override
	public void setFocus() {
		if( SceneView.getDefaultInstance() != null )
			SceneView.getDefaultInstance().setEntity(root);
	}

	public class ActionBarContributor implements IEditorActionBarContributor {
		public void init(IActionBars bars, IWorkbenchPage page) {
		}
	
		public void setActiveEditor(IEditorPart targetEditor) {
		}

		public void dispose() {
		}
	}
}
