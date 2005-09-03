/*
 * Created on Jun 23, 2005
 */
package de.velox.editor.views;

import org.eclipse.jface.action.Action;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.IActionBars;

import de.velox.*;
import de.velox.editor.entity.*;

public class RenderView extends VeloxViewBase {
//	private int windowHandle;
//	private VRenderFrameAction renderAction;

//	private Entity scene = new Entity("root");
//	private Entity graphics = new Entity("graphics");
//	private IVShooting shooting = null;
	
	private RenderLayer renderLayer;
	
	public RenderView() {
//		scene.Add(new Part("scene"));
//		scene.Add(new Part("shooting", new VPartPtr(shooting)));
//		scene.Add(graphics);
	}
	
	class MyFrameAction extends IVFrameAction {
		@Override
		public void Init() {
			System.out.println("MyFrameAction::Init()");
		}

		@Override
		public void Shutdown() {
			System.out.println("MyFrameAction::Shutdown()");
		}

		@Override
		public void UpdateFrame() {
		}
	}

	@Override
	public void createPartControl(Composite in_Parent) {
		renderLayer = new RenderLayer(in_Parent);
		
		VView.GetInstance().Add(new MyFrameAction());
//		windowHandle = in_Parent.handle;
//		
//		renderAction = new VRenderFrameAction(windowHandle);
//		VView.GetInstance().Add(renderAction);

		/*
		// add buttons to start and stop rendering
		IActionBars actionBar = getViewSite().getActionBars();
		
		Action startRenderAction = new Action()
		{
		   	 public void run()
		     {
//		   		 renderView.StartRendering();
		     }
		};
		
		startRenderAction.setText("Start");
		startRenderAction.setToolTipText("Start rendering to the view");
		actionBar.getToolBarManager().add(startRenderAction);
 		
		//create Velox3D End Rendering Button
		Action stopRenderAction = new Action()
		{
		   	 public void run()
		     {
//		   		 renderView.StopRendering();
		     }
		};
		
		stopRenderAction.setText("Stop");
		stopRenderAction.setToolTipText("Stop rendering to the view");
		actionBar.getToolBarManager().add(stopRenderAction);
		*/
	}

	@Override
	public void setFocus() {
	}
}
