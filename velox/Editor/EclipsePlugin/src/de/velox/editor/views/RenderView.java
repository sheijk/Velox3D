/*
 * Created on Jun 23, 2005
 */
package de.velox.editor.views;

import org.eclipse.jface.action.Action;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.IActionBars;
import org.eclipse.ui.part.ViewPart;

import de.velox.VView;

public class RenderView extends VeloxViewBase {
	private int windowHandle = 0;
//	private VView renderView = null;
	
	@Override
	public void createPartControl(Composite in_Parent) {
//		windowHandle = in_Parent.handle;
//		
//		renderView = new VView(windowHandle);
//		
//		// add buttons to start and stop rendering
//		IActionBars actionBar = getViewSite().getActionBars();
//		
//		Action startRenderAction = new Action()
//		{
//		   	 public void run()
//		     {
//		   		 renderView.StartRendering();
//		     }
//		};
//		
//		startRenderAction.setText("Start");
//		startRenderAction.setToolTipText("Start rendering to the view");
//		actionBar.getToolBarManager().add(startRenderAction);
// 		
//		//create Velox3D End Rendering Button
//		Action stopRenderAction = new Action()
//		{
//		   	 public void run()
//		     {
//		   		 renderView.StopRendering();
//		     }
//		};
//		
//		stopRenderAction.setText("Stop");
//		stopRenderAction.setToolTipText("Stop rendering to the view");
//		actionBar.getToolBarManager().add(stopRenderAction);
		
	}

	@Override
	public void setFocus() {
	}
}
