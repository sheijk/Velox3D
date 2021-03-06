/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVACTION_2004_05_05_H
#define V3D_IVACTION_2004_05_05_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

/**
 * A simple parameterless action which may be invoked by the editor. Will be
 * added to the editor menues
 *
 * @author sheijk
 */
class IVAction
{
public:
	/** returns the name to appear in the menu */
	virtual VStringRetVal GetName() = 0;
	
	/** executes the action */
	virtual void Execute() = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_IVACTION_2004_05_05_H

