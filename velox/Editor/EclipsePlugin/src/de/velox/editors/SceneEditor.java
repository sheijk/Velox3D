package de.velox.editors;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.SashForm;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.IActionBars;
import org.eclipse.ui.IEditorActionBarContributor;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IEditorPart;
import org.eclipse.ui.IEditorSite;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.PartInitException;
import de.velox.*;
import de.velox.editor.entity.*;
import de.velox.editor.views.RenderLayer;
import de.velox.editor.views.SceneView;

public class SceneEditor extends VeloxEditorBase {
	private VRenderFrameAction renderAction = null;
	private RenderLayer renderLayer = null;
	private Entity root = null;
	private IVShooting shooting = null;
	
	private String fileName = "";
	
	public SceneEditor() {
		root = new Entity(fileName);
		root.Add(new Part("scene"));
		
		Entity entity = new Entity("obj");
		entity.Add(new Part("model"));
		root.Add(entity);
	}
	
	@Override
	public void doSave(IProgressMonitor monitor) {
		System.out.println("SceneEditor.doSave");
	}

	@Override
	public void doSaveAs() {
		System.out.println("SceneEditor.doSaveAs");
	}

	@Override
	public void init(IEditorSite site, IEditorInput input) throws PartInitException {
		System.out.println("SceneEditor.init");
		
		fileName = input.getName();
		root.SetName(fileName);
		
		setInput(input);
		setSite(site);
	}

	@Override
	public boolean isDirty() {
		System.out.println("SceneEditor.isDirty");
		return false;
	}

	@Override
	public boolean isSaveAsAllowed() {
		System.out.println("SceneEditor.isSaveAsAllowed");
		return false;
	}

	@Override
	public void createPartControl(Composite parent) {
		System.out.println("SceneEditor.createPartControl");

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
		
		shooting = v3d.CreateShooting(renderAction.GetDevice());
		Part shootingPart = new Part("shooting", new VPartPtr(shooting));
		root.Add(shootingPart);
		renderAction.SetShooting(shooting);
	}

	@Override
	public void setFocus() {
		System.out.println("SceneEditor.setFocus");
		
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
