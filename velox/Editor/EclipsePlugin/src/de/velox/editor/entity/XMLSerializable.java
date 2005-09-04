/*
 * Created on Jul 16, 2005
 */
package de.velox.editor.entity;

import de.velox.IVXMLElement;

public interface XMLSerializable {
	void writeToXML(IVXMLElement outElement);
}
