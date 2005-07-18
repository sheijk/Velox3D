/*
 * Created on Jul 7, 2005
 */
package de.velox.editor.entity;

public class Setting {
	private String name;
	private String value;
	
	public Setting(String name, String value) {
		this.name = name;
		this.value = value;
	}

	public String GetName() {
		return name;
	}

	public String GetValue() {
		return value;
	}

	public void SetName(String out_name) {
		name = out_name;
	}

	public void SetValue(String out_value) {
		value = out_value;
	}
}
