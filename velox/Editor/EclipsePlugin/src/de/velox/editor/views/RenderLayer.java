package de.velox.editor.views;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.ControlEvent;
import org.eclipse.swt.events.ControlListener;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.events.MouseMoveListener;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;

import de.velox.IVDevice;
import de.velox.VCamera;
import de.velox.VRenderFrameAction;
import de.velox.VView;

public class RenderLayer {
	private final int windowHandle;
	private final IVDevice device;
	private final VRenderFrameAction renderAction;

	private final VCamera camera = new VCamera();
//	private final VMatrix44f viewMatrix = new VMatrix44f();

//	private final float[] cameraPositon = new float[3];

	public RenderLayer(final Composite parent) {
//		super(parent, style);
		
		windowHandle = parent.handle;
		renderAction = new VRenderFrameAction(windowHandle);
		VView.GetInstance().Add(renderAction);
		device = renderAction.GetDevice();

		camera.GetPosition().SetX(1.0f);
		camera.GetPosition().SetY(1.0f);
		camera.GetPosition().SetZ(2.0f);
//		cameraPositon[0] = 1.0f;
//		cameraPositon[1] = 1.0f;
//		cameraPositon[2] = 2.0f;
		
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
		
		parent.addListener(SWT.MouseWheel, new Listener() {
			public void handleEvent(Event event) {
				System.out.println("MouseWheel event");
			}
		});
		
		MouseHandler mouseHandler = new MouseHandler();
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
	
	private class MouseHandler implements MouseMoveListener, MouseListener
	{
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
//				System.out.print("moved by x=" + e.x + " y=" + e.y);
				
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
				
//				System.out.println(" dx=" + dx + " dy=" + dy);

				if( (e.stateMask & SWT.CONTROL) != 0 ) {
					camera.RotateX(dy*10);
					camera.RotateY(-dx*10);
					camera.RotateZ(dz*10);
				}
				else {
					camera.Strafe(dx);
					camera.MoveUp(dy);
					camera.MoveForward(dz);
//					camera.Move(dx, dy, dz);
				}
//				cameraPositon[0] += dx;
//				cameraPositon[1] += dy;
//				cameraPositon[2] += dz;
				
				applyCamera();
				
				lastX = e.x;
				lastY = e.y;
			}
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
}
