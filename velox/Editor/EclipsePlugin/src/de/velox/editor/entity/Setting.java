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

public class Setting {
	private final String name;
	private String value;
	
	private final Part part;
	
//	private LinkedList<Setting> childs = new LinkedList<Setting>();
	
	public Setting(Part part, String name, String value) {
		this.part = part;
		this.name = name;
		this.value = value;
	}

	public String GetName() {
		return name;
	}

	public String GetValue() {
		return value;
	}

	public void SetValue(String newValue) {
		value = newValue;
		
		part.updateSetting(this);
	}
	
	public String toString() {
		return name + " = " + value;
	}
	
//	public LinkedList<Setting> getChildSettings() {
//		return childs;
//	}
}

