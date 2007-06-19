/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

/*
 * Created on Jul 7, 2005
 */
package de.velox.editor.entity;

import java.util.Iterator;
import java.util.LinkedList;
import de.velox.*;

public class Part extends Node {
	private Entity owner = null;
	
	public Part(String type) {
		super(v3d.CreatePart(type));
	}
	
	public Part(String type, VNodePtr impl)
	{
		super(type, impl);
	}
	
	public Part(VNodePtr partImpl) {
		super(partImpl);
	}
	
	public void applySettings(IVXMLElement xml) {
		final String xmlType = xml.GetAttribute("type").GetValue().ToString();
		if( ! xmlType.equalsIgnoreCase(GetType()) )
			return;
		
		VXMLAttributeIterator attrib = xml.AttributeBegin();
		while( attrib.HasNext() ) {
			final String name = attrib.Get().GetName().AsCString();
			final String value = attrib.Get().GetValue().ToString();
			
			if( name.equalsIgnoreCase("tags") ) {
				String[] tagNames = value.split(" ");
				for(String tag : tagNames) {
					if( tag.length() > 0 && !tag.equals(" ") )
						AttachTag(tag);
				}
			}
			else {
				Setting setting = new Setting(this, name, value);
				updateSetting(setting);
			}
			
			attrib.Next();
		}
	}
		
	public VMessage Send(VMessage inMessage) {
		VMessage reply = new VMessage();
		impl.Send(inMessage, reply);
		return reply;
	}
	
	public void synchronize() {
		updateSettingsFromPart();		
	}
	
	public String GetType() {
		return type;
	}
	
	public Entity getOwner() {
		return owner;
	}
	
	void setOwner(Entity newOwner) {
		owner = newOwner;
	}
	
//	public void writeToXML(IVXMLElement outElement) {
//		outElement.SetName("part");
//		
//		outElement.AddAttribute("type", new VStringValue(GetType()));
//		
//		// add all settings
//		Iterator<Setting> settingIter = settings.iterator();
//		while( settingIter.hasNext() ) {
//			Setting s = settingIter.next();
//			
//			outElement.AddAttribute(s.GetName(), new VStringValue(s.GetValue()));
//		}
//
//		final StringBuffer tagList = new StringBuffer();
//		VTagIterator tagIter = tags();
//		while( tagIter.HasNext() ) {
//			final String tagName = tagIter.Get().GetName();
//			tagList.append(" " + tagName);
//			tagIter.Next();
//		}
//		
//		outElement.AddAttribute("tags", new VStringValue(tagList.toString()));
//	}
	
	public String toString() {
		String description = "(P) " + GetId();
		
		LinkedList<String> tags = new LinkedList<String>();
		
		if( valid(impl) ) {
			if( impl.GetState() != VNode.State.Active )
				tags.add("unready");
		}
		else {
			tags.add("impl invalid");
		}
		
		if( tags.size() > 0 ) {
			description += "(";
			boolean first = true;
			
			Iterator<String> tagIter = tags.iterator();
			while(tagIter.hasNext()) {
				if( ! first )
					description += ", ";
				else
					description += " ";
				
				description += tagIter.next();			
			}
			
			description += ")";
		}
		
		return description;	
	}

	public VNodePtr GetPart() {
		return impl;
	}
}

