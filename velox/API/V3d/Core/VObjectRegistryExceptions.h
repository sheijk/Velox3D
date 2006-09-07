/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VOBJECTREGISTRYEXCEPTION_H
#define V3D_VOBJECTREGISTRYEXCEPTION_H
//------------------------------------------------------------------------
#include <v3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

class VObjectRegistryException : public VException
{
public:
	VObjectRegistryException(
		VStringParam in_Error, 
		VStringParam in_File, 
		int in_nLine);
};

//-----------------------------------------------------------------------------
} // namespace v3d
//------------------------------------------------------------------------
#endif // V3D_VOBJECTREGISTRYEXCEPTION_H

