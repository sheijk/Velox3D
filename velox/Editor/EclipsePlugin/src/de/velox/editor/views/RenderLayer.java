/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

package de.velox.editor.views;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.ControlEvent;
import org.eclipse.swt.events.ControlListener;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.events.MouseMoveListener;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Widget;

import de.velox.IVDevice;
import de.velox.IVInputManager;
import de.velox.IVSynchronizedAction;
import de.velox.VCamera;
import de.velox.VRenderFrameAction;
import de.velox.VView;

public class RenderLayer /* extends Canvas <- hilft nicht */ {
	private final int windowHandle;
	private final IVDevice device;
	private final VRenderFrameAction renderAction;
	private final Control parent;
	private final VCamera camera = new VCamera();
	private IVInputManager inputManager = null;
	
	static boolean mainRenderLayerInitialized = false;
//	static RenderLayer mainWindowRenderLayer = null;

	public RenderLayer(final Control parent) {
		if( ! mainRenderLayerInitialized ) {
			mainRenderLayerInitialized = true;
//			VRenderFrameAction.InitRendering( parent.getShell().handle );
			VView.Init( parent.getShell().handle );
			
//			mainWindowRenderLayer = new RenderLayer( parent.getShell() );
		}
		
		windowHandle = parent.handle;
		renderAction = new VRenderFrameAction(windowHandle);
//		VView.GetInstance().Add(renderAction);
		renderAction.RegisterSelf();
		device = renderAction.GetDevice();

		camera.GetPosition().SetX(1.0f);
		camera.GetPosition().SetY(1.0f);
		camera.GetPosition().SetZ(2.0f);
		
		applyCamera();
		
		parent.addControlListener(new ControlListener() {
			public void controlResized(ControlEvent e) {
				int left = parent.getLocation().x;
				int top = parent.getLocation().y;
				int right = left + parent.getSize().x;
				int bottom = top + parent.getSize().y;
				
				renderAction.SetArea(left, top, right, bottom);
//				int width = parent.getSize().x;
//				int height = parent.getSize().y;
				
//				renderAction.setSize(width, height);
			}
		
			public void controlMoved(ControlEvent e) {
			}
		});
		
		parent.addDisposeListener(new DisposeListener() {
			public void widgetDisposed(DisposeEvent e) {
//				VView.GetInstance().Remove(renderAction);
//				VView.GetInstance().ExecSynchronized(new IVSynchronizedAction());
				renderAction.UnregisterSelf();
			}
		});
		
//		parent.addListener(SWT.MouseWheel, new Listener() {
//			public void handleEvent(Event event) {
//				System.out.println("MouseWheel event");
//			}
//		});
		
		this.parent = parent;
	}
	
	// needs to be called before the window gets closed, otherwise the program
	// might crash when the renderAction tries to make the context of the
	// deleted window current
	public void windowClosed() {
		renderAction.UnregisterSelf();
//		VView.GetInstance().Remove(renderAction);
	}
	
	public IVInputManager getInputManager() {
		//TODO: dinput device kann nicht erstellt werden...
//		if( inputManager == null ) {
//			inputManager = de.velox.v3d.CreateInputManager(windowHandle);
//		}
		
		return inputManager;
	}
	
	public void addMouseListener(MouseEventListener mouseHandler) {
		parent.addMouseListener(mouseHandler);
		parent.addMouseMoveListener(mouseHandler);
	}
	
	private void applyCamera() {
		if( device != null ) {
//			viewMatrix.SetTransform(-cameraPositon[0], -cameraPositon[1], -cameraPositon[2]);
		
//			device.SetMatrix(IVDevice.MatrixMode.ViewMatrix, viewMatrix);
			camera.ApplyTo(device);
//			device.SetMatrix(IVDevice.MatrixMode.ViewMatrix, camera.GetMatrix());
		}
	}

	public IVDevice getDevice() {
		return device;
	}

	public VRenderFrameAction getRenderAction() {
		return renderAction;
	}

	public int getWindowHandle() {
		return windowHandle;
	}
	
	public static interface MouseEventListener 
		extends MouseMoveListener, MouseListener 
	{
	}
}	


