package de.velox.editor.views;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.ControlEvent;
import org.eclipse.swt.events.ControlListener;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.events.MouseMoveListener;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;

import de.velox.IVDevice;
import de.velox.IVInputManager;
import de.velox.VCamera;
import de.velox.VRenderFrameAction;
import de.velox.VView;

public class RenderLayer {
	private final int windowHandle;
	private final IVDevice device;
	private final VRenderFrameAction renderAction;
	private final Composite parent;
	private final VCamera camera = new VCamera();
	private IVInputManager inputManager = null;

	public RenderLayer(final Composite parent) {
		windowHandle = parent.handle;
		renderAction = new VRenderFrameAction(windowHandle);
		VView.GetInstance().Add(renderAction);
		device = renderAction.GetDevice();

		camera.GetPosition().SetX(1.0f);
		camera.GetPosition().SetY(1.0f);
		camera.GetPosition().SetZ(2.0f);
		
		applyCamera();
		
		parent.addControlListener(new ControlListener() {
			public void controlResized(ControlEvent e) {
				int width = parent.getSize().x;
				int height = parent.getSize().y;
				
				renderAction.setSize(width, height);
			}
		
			public void controlMoved(ControlEvent e) {
			}
		});
		
		parent.addDisposeListener(new DisposeListener() {
			public void widgetDisposed(DisposeEvent e) {
				VView.GetInstance().Remove(renderAction);
			}
		});
		
		parent.addListener(SWT.MouseWheel, new Listener() {
			public void handleEvent(Event event) {
				System.out.println("MouseWheel event");
			}
		});
		
		this.parent = parent;
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

