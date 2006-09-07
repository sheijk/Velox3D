/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

package de.velox.editor.entity;

import de.velox.IVShooting;
import de.velox.IVXMLElement;
import de.velox.VPartPtr;
import de.velox.VRenderFrameAction;
import de.velox.v3d;

public class RootEntity extends Entity {
	private static final String SHOOTING_PART_ID = "shooting";
	
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
			super.Add(new Part(SHOOTING_PART_ID, new VPartPtr(shooting)));
		}
	}
	
	@Override
	public void Add(Part newPart) {
		if( valid(newPart.GetPart()) && ! newPart.GetId().equalsIgnoreCase(SHOOTING_PART_ID) ) {
			super.Add(newPart);
		}
	}

}

