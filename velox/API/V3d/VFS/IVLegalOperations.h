/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVLEGALOPERATIONS_H
#define V3D_IVLEGALOPERATIONS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Returns information about which functions may be performed on a
 * IVStream
 */
class IVLegalOperations
{
public:
	virtual ~IVLegalOperations() {};

	/** Returns whether reading from the stream is allowed */
	virtual vbool AllowRead() const = 0;
	
	/** Returns wheter writing to stream is allowed */
	virtual vbool AllowWrite() const = 0;

	/** Returns whether changing the read/write position is allowed */
	virtual vbool AllowPositioning() const = 0;

	/** Returns whether the read/write pos can be retrieved */
	virtual vbool AllowGetPosition() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVLEGALOPERATIONS_H


