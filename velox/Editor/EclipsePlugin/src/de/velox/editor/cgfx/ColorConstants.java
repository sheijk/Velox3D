/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

package de.velox.editor.cgfx;

import org.eclipse.swt.graphics.RGB;

public interface ColorConstants {
	RGB CGFX_COMMENT = new RGB(0, 128, 0);
	RGB CGFX_KEYWORD = new RGB(0, 0, 180);
	RGB CGFX_STATE = new RGB(128, 0, 0);
	RGB CGFX_STRING = new RGB(255, 128, 0);
	RGB CGFX_RESERVED = new RGB(255, 0, 0);
	RGB PROC_INSTR = new RGB(128, 128, 128);
	RGB DEFAULT = new RGB(0, 0, 0);
}

