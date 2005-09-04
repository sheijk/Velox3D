/*
 * Created on Jul 7, 2005
 */
package de.velox.editor.entity;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.TreeMap;
import java.util.TreeSet;

import de.velox.*;

public class Part implements XMLSerializable {
	private String type;
	
	private LinkedList<Setting> settings = new LinkedList<Setting>();
	private LinkedList<VPartDependency> dependencies = new LinkedList<VPartDependency>();
	private Entity owner = null;
	
	private VPartPtr impl = null;
	
	public Part(String type) {
		this.type = type;
		
		IVXMLElement xmlElement = v3d.CreateXMLElement("part");
		xmlElement.AddAttribute("type", new VStringValue(type));
		
		impl = v3d.CreatePart(xmlElement);
		
		updateSettingsFromPart();
	}
	
	public Part(String type, VPartPtr impl)
	{
		this.type = type;
		this.impl = impl;
		
		updateSettingsFromPart();
	}
	
	public Part(IVXMLElement xml)
	{
		this(xml.GetAttribute("type").GetValue().ToString());
		settings.clear();
		
		// for each attribute
		VXMLAttributeIterator attrib = xml.AttributeBegin();
		while( attrib.HasNext() ) {
			// get name and value
			final String name = attrib.Get().GetName().toString();
			final String value = attrib.Get().GetValue().ToString();
			
			// store as setting
			Setting setting = new Setting(this, name, value); 
			settings.add(setting);
			
			// send change message to part
			updateSetting(setting);
			
			attrib.Next();
		}
		
		// refresh settings from part
		synchronize();
		
		//TODO: check for differences and warn if any changes detected
	}
	
	public void updateSettingsFromPart() {
		if( ! valid(impl) )
			return;
		
		VMessage requestMessage = new VMessage();
		requestMessage.AddProperty("type", "getSettings");
		
		VMessage answer = new VMessage();
		impl.Send(requestMessage, answer);

		settings.clear();
		
		VStringIter nameIter = answer.PropertyIterator();
		while( nameIter.HasNext() ) {
			settings.add(new Setting(this, nameIter.Get(), answer.Get(nameIter.Get()).ToString()));
			
			nameIter.Next();
		}
		
		// get dependencies
		dependencies.clear();
		for(int depNum = 0; depNum < impl.DependencyCount(); ++depNum) {
			VPartDependency dependency = new VPartDependency();
			dependency.SetId(impl.GetDependencyInfo(depNum).GetId());
			dependency.SetLocation(impl.GetDependencyInfo(depNum).GetLocation());
			
			dependencies.add(dependency);
		}
	}
	
	void updateSetting(Setting setting) {
		// send part an update message
		VMessage msg = new VMessage();
		msg.AddProperty("type", "update");
		msg.AddProperty("name", setting.GetName());
		msg.AddProperty("value", setting.GetValue());
		
		if( valid(impl) ) {
			impl.Send(msg);
		}
	}
	
	public void synchronize() {
		updateSettingsFromPart();		
	}
	
	public Iterator<VPartDependency> dependencyIterator() {
		return dependencies.iterator();
	}
	
//	public Iterator<String> SettingNameIterator() {
//		return new Iterator<String>() {
//			private Iterator<Setting> impl = settings.iterator();
//			
//			public boolean hasNext() {
//				return impl.hasNext();
//			}
//
//			public String next() {
//				return impl.next().GetName();
//			}
//
//			public void remove() {
//			}
//		};
//	}
	
//	public void SetSetting(String name, String value) {
//		settings.add(new Setting(name, value));
//	}
	
	public Iterator<Setting> settingsIterator() {
		return settings.iterator();
	}

	public String GetType() {
		return type;
	}
	
	public String GetId() {
		return type;
	}
	
	public Entity getOwner() {
		return owner;
	}
	
	void setOwner(Entity newOwner) {
		owner = newOwner;
	}
	
	public void writeToXML(IVXMLElement outElement) {
		outElement.SetName("part");
		
		outElement.AddAttribute("type", new VStringValue(GetType()));
		
		// add all settings
		Iterator<Setting> settingIter = settings.iterator();
		while( settingIter.hasNext() ) {
			Setting s = settingIter.next();
			
			outElement.AddAttribute(s.GetName(), new VStringValue(s.GetValue()));
		}
	}
	
	private static boolean valid(VPartPtr ptr) {
		return ptr != null && ptr.Get() != null;
	}
	
	public String toString() {
		String description = "(P) " + GetId();
		
		LinkedList<String> tags = new LinkedList<String>();
		
		if( valid(impl) ) {
			if( ! impl.IsReady() )
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

	VPartPtr GetPart() {
		return impl;
	}
}
