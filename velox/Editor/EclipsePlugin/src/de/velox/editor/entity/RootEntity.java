package de.velox.editor.entity;

import de.velox.IVShooting;
import de.velox.IVXMLElement;
import de.velox.VPartPtr;
import de.velox.VRenderFrameAction;
import de.velox.v3d;

public class RootEntity extends Entity {
	private VRenderFrameAction renderAction = null;
	private IVShooting shooting = null;
	
	public RootEntity(String name) {
		super(name);
	}

	public RootEntity(IVXMLElement xml) {
		super(xml);
	}
	
	public void setRenderAction(VRenderFrameAction ra) {
		if( renderAction == null ) {
			renderAction = ra;
			
			shooting = v3d.CreateShooting(renderAction.GetDevice());
			renderAction.SetShooting(shooting);
			super.Add(new Part("shooting", new VPartPtr(shooting)));
		}
	}
	
	@Override
	public void Add(Part newPart) {
		if( valid(newPart.GetPart()) && ! newPart.GetId().equalsIgnoreCase("shooting") ) {
			super.Add(newPart);
		}
	}

}