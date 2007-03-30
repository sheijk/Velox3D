/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VLegalOperations.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

VLegalOperations::VLegalOperations(
	vbool read, vbool write, vbool setpos, vbool getpos)
{
	m_bAllowRead = read;
	m_bAllowWrite = write;
	m_bAllowPositioning = setpos;
	m_bAllowGetPosition = getpos;
}

vbool VLegalOperations::AllowRead() const
{
	return m_bAllowRead;
}

vbool VLegalOperations::AllowWrite() const
{
	return m_bAllowWrite;
}

vbool VLegalOperations::AllowPositioning() const
{
	return m_bAllowPositioning;
}

vbool VLegalOperations::AllowGetPosition() const
{
	return m_bAllowGetPosition;
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

