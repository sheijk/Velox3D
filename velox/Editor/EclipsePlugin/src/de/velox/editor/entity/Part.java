/*
 * Created on Jul 7, 2005
 */
package de.velox.editor.entity;

import java.util.Iterator;
import java.util.LinkedList;
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
		
		VPartAndId partAndId = v3d.CreatePart(xmlElement);
		impl = partAndId.GetPart();
		this.type = partAndId.GetId();
		
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
				
//		VXMLNodeIterator node = xml.ChildBegin();
//		while( node.HasNext() ) {
//			IVXMLElement childElement = node.Get().ToElement();
//			if( childElement != null ) {
//				VXML
//			}
//			
//			node.Next();
//		}
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
			dependency.SetTypeInfo(impl.GetDependencyInfo(depNum).GetTypeInfo());
			dependency.SetCondition(impl.GetDependencyInfo(depNum).GetCondition());
			
			dependencies.add(dependency);
		}
	}
	
	public Setting getSetting(String name) {
		for(Setting s : this.settings) {
			if( s.GetName().equalsIgnoreCase(name) )
				return s;
		}
		
		return null;
	}
	
	void updateSetting(Setting setting) {
		// send part an update message
		VMessage msg = new VMessage();
		msg.AddProperty("type", "update");
		msg.AddProperty("name", setting.GetName());
		msg.AddProperty("value", setting.GetValue());
		
		if( valid(impl) ) {
			try {
				impl.Send(msg);
				updateSettingsFromPart();
			}
			catch(Throwable e) {
				System.err.println(e.getMessage());
				e.printStackTrace(System.err);
			}
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

		final StringBuffer tagList = new StringBuffer();
		VTagIterator tagIter = tags();
		while( tagIter.HasNext() ) {
			final String tagName = tagIter.Get().GetName();
			tagList.append(" " + tagName);
			tagIter.Next();
		}
		
		outElement.AddAttribute("tags", new VStringValue(tagList.toString()));
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

	public VPartPtr GetPart() {
		return impl;
	}
	
	public VTagIterator tags() {
		return impl.Tags();
	}
	
	public void AttachTag(String id) {
		impl.AttachTag(v3d.GetTagRegistry().GetTagWithName(id));
	}
	
	public void RemoveTag(String id) {
		impl.RemoveTag(v3d.GetTagRegistry().GetTagWithName(id));
	}
}
