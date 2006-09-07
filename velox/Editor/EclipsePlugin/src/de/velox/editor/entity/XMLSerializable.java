/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

/*
 * Created on Jul 16, 2005
 */
package de.velox.editor.entity;

import de.velox.IVXMLElement;

public interface XMLSerializable {
	void writeToXML(IVXMLElement outElement);
}

