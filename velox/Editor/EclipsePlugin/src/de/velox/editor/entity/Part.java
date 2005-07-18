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
	
//	private TreeMap<String, String> settings = new TreeMap<String, String>();
	private LinkedList<Setting> settings = new LinkedList<Setting>();
	
	private VPartPtr impl = null;
	
	public Part(String type) {
		this.type = type;
	}
	
	public Iterator<String> SettingNameIterator() {
		return new Iterator<String>() {
			private Iterator<Setting> impl = settings.iterator();
			
			public boolean hasNext() {
				return impl.hasNext();
			}

			public String next() {
				return impl.next().GetName();
			}

			public void remove() {
			}
		};
//		return settings.keySet().iterator();
	}
	
	public void SetSetting(String name, String value) {
		settings.add(new Setting(name, value));
//		settings.put(name, value);
	}
	
	public Iterator<Setting> settingsIterator() {
		return settings.iterator();
	}
	
//	public String GetSetting(String name) {
//		if( settings.containsKey(name) ) {
//			return settings.get(name);
//		}
//		else {
//			return null;
//		}
//	}

	public String GetType() {
		return type;
	}

	public void SetType(String out_type) {
		type = out_type;
	}
	
	public void ToXML(IVXMLElement outElement) {
		outElement.SetName("part");
		
		outElement.AddAttribute("type", new VStringValue(GetType()));
		
		// add all settings
		Iterator<Setting> settingIter = settings.iterator();
		while( settingIter.hasNext() ) {
			Setting s = settingIter.next();
			
			outElement.AddAttribute(s.GetName(), new VStringValue(s.GetValue()));
		}
	}
	
	VPartPtr GetPart() {
		return impl;
	}
}
