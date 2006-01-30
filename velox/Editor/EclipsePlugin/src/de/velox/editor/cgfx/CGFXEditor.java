package de.velox.editor.cgfx;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.Timer;
import java.util.TimerTask;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.eclipse.core.resources.IMarker;
import org.eclipse.core.resources.IResource;
import org.eclipse.jface.action.Action;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.SashForm;
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.IActionBars;
import org.eclipse.ui.IFileEditorInput;
import org.eclipse.ui.editors.text.TextEditor;

import de.velox.IVDevice;
import de.velox.VMatrix44f;
import de.velox.VRenderFrameAction;
import de.velox.VResourceId;
import de.velox.v3d;
import de.velox.editor.entity.Entity;
import de.velox.editor.entity.Part;
import de.velox.editor.entity.RootEntity;
import de.velox.editor.views.RenderLayer;
import de.velox.editor.views.SceneView;

public class CGFXEditor extends TextEditor {
	private RootEntity testScene = null;
	
	private ColorManager colorManager;

	private final class CompileTimer extends Timer {
		private static final int INTERVAL_MS = 1000;
		
		private int secondsUntilNextCompile = -1;
		private String src = null;

		public CompileTimer() {
			scheduleAtFixedRate(new TimerTask() {
				public void run() {
					if( secondsUntilNextCompile == 0 ) {
						getEditorSite().getShell().getDisplay().syncExec(new Runnable() {
							public void run() {
								compileEffect(src);
							}
						});
					}
					
					if( secondsUntilNextCompile >= 0 )
						--secondsUntilNextCompile;
				}
			}, INTERVAL_MS, INTERVAL_MS);
		}
		
		public void initiateRecompile() {
			secondsUntilNextCompile = 1;
			src = getSourceCode();
		}
	};
	
	private CompileTimer delayedCompileTimer = new CompileTimer();

	public CGFXEditor() {
		super();
		colorManager = new ColorManager();
		setSourceViewerConfiguration(new ViewConfig(colorManager));
		setDocumentProvider(new DocumentProvider());
		
		try {
			v3d.Initialize();
		} catch (Exception e) {
			e.printStackTrace(System.err);
		}
	}
	
	@Override
	protected void createActions() {
		super.createActions();
	
		IActionBars bars = getEditorSite().getActionBars();
		
		compileAction.setText("Compile");
		
		bars.getToolBarManager().add(compileAction);
	}

	public void dispose() {
		colorManager.dispose();
		super.dispose();
	}

	@Override
	public void createPartControl(Composite parent) {
		SashForm sash = new SashForm(parent, SWT.NONE);
		sash.setOrientation(SWT.VERTICAL);
		
		Composite top = new Composite(sash, SWT.NONE);
		top.setLayout(new FillLayout());
		super.createPartControl(top);

		Composite renderComposite = new Composite(sash, SWT.NONE);
		RenderLayer renderLayer = new RenderLayer(renderComposite);
		VRenderFrameAction	renderAction = renderLayer.getRenderAction();
		
		IVDevice device = renderAction.GetDevice();
		VMatrix44f viewMatrix = new VMatrix44f();
		viewMatrix.SetTransform(1.0f, 1.0f, -7.0f);
		device.SetMatrix(IVDevice.MatrixMode.ViewMatrix, viewMatrix);
		
		// create a test material
		String source = INITIAL_SOURCE;
//		VResource matResource = v3d.GetResourceManager().GetResourceByName("/").AddRandomNamedSubResource();
		VResourceId matResource = v3d.GetResourceManager().CreateResource(getResourceName());
		v3d.setTextFile(matResource.__deref__(), source);
		if( ! v3d.replaceCGFXSource(matResource.__deref__(), source) ) {
			System.err.println("Could not replace source for cgfx material");
		}
		
		// create a simple scene to show the effect
		testScene = new RootEntity("testScene");
		testScene.setRenderAction(renderAction);
		testScene.Add(new Part("v3d::scene::VNaiveSceneManagerPart"));
		Entity plane = new Entity("plane");
		testScene.Add(plane);

		plane.Add(new Part("v3d::entity::VRigidBodyPart"));
		Part planeMesh = new Part("v3d::scene::VPlaneMeshPart");
		plane.Add(planeMesh);
		planeMesh.getSetting("material").SetValue(getResourceName());
		
		Entity orientation = new Entity("orientation");
		orientation.Add(new Part("v3d::entity::VRigidBodyPart"));
		orientation.Add(new Part("v3d::scene::VOrientationGridPart"));
		testScene.Add(orientation);
		
		testScene.Activate();
		
		getSourceViewer().getTextWidget().addModifyListener(new ModifyListener() {
			public void modifyText(ModifyEvent e) {
				// try to recompile source after each keystroke
				delayedCompileTimer.initiateRecompile();
			}
		});

		setFocus();
	}

	@Override
	public void setFocus() {
		super.setFocus();
		
		if( SceneView.getDefaultInstance() != null && testScene != null )
			SceneView.getDefaultInstance().setEntity(testScene);
	}
	
	private String getSourceCode() {
		return getSourceViewer().getTextWidget().getText();
	}

	private VResourceId getV3dResource() {
		return v3d.GetResourceManager().GetResourceByName(getResourceName());
	}
	
	private String getResourceName() {
		return ((IFileEditorInput)getEditorInput()).getFile().getFullPath().toString();
	}
	
	private void compileEffect(String src) {
		try {
			// write string to file
			File tempFile = File.createTempFile("v3d_cgfx", ".tmp.cg");
			PrintStream tempStream = new PrintStream(new FileOutputStream(tempFile));
			tempStream.print(src);
			tempStream.close();
			
			Process cgc = Runtime.getRuntime().exec(new String[] {
					"cgc.exe", "-noentry", "-fx",
					tempFile.getAbsolutePath() });

			BufferedReader processOutput = new BufferedReader(new InputStreamReader(cgc.getInputStream()));

			IResource resource = ((IFileEditorInput)getEditorInput()).getFile();
			
			resource.deleteMarkers(IMarker.PROBLEM, false, IResource.DEPTH_ONE);
			
			String line;
			while((line = processOutput.readLine()) != null) {
				Pattern pattern = Pattern.compile("(.*)\\(([0-9]*)\\) : error ([A-Z][0-9]{4}: .*)");
				Matcher matcher = pattern.matcher(line);
				if( matcher.matches() && matcher.groupCount() >= 3 ) {
					//String errorFile = matcher.group(1);
					final String errorFile = this.getResourceName();
					final int errorLine = Integer.parseInt(matcher.group(2));
					final String errorMessage = matcher.group(3);
					
					System.out.println("[" + errorFile + ":" + errorLine
							+ "] " + errorMessage);

					final IMarker m = resource.createMarker(IMarker.PROBLEM);
					m.setAttribute(IMarker.MESSAGE, errorMessage);
					m.setAttribute(IMarker.LINE_NUMBER, errorLine);
					m.setAttribute(IMarker.SEVERITY, IMarker.SEVERITY_ERROR);
					m.setAttribute(IMarker.PRIORITY, IMarker.PRIORITY_NORMAL);
				}
			}

			if( cgc.exitValue() == 0 ) {
				final boolean succeeded = v3d.replaceCGFXSource(
						getV3dResource().__deref__(), src);
				
				if( ! succeeded ) {
					System.err.println("Could not compile cgfx source");
				}
			}
			else {
				System.err.println("cgc returned error");
			}
			
		} catch (Exception e) {
			e.printStackTrace(System.err);
		}
	}

	private static final String INITIAL_SOURCE =
		"technique defaultT {" +
		"	pass p0 {" +
		"	}" +
		"}";

	private final Action compileAction = new Action() {
		@Override
		public void run() {
			compileEffect(getSourceCode());
//			final String src = getSourceCode();
//			
//			final boolean succeeded = v3d.replaceCGFXSource(
//				getResource().__deref__(), src);
//			
//			if( succeeded ) {
//				this.setText("Compile");
//			}
//			else {
//				this.setText("Compile(x)");
//			}

//				MessageBox box = new MessageBox(getEditorSite().getShell());
//				box.setMessage("lala msg");
//				box.setText("lalala txt");
//				box.open();
		}
	};
}
