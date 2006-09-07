/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Core/VObjectRegistryExceptions.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

VObjectRegistryException::VObjectRegistryException(
	VStringParam in_Error, 
	VStringParam in_File, 
	int in_nLine) :
	VException(in_Error, in_File, in_nLine)
{
}

//-----------------------------------------------------------------------------
} // namespace v3d

