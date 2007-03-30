/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//TODO: correct file guard
#ifndef V3D_VIOSTREAM_H
#define V3D_VIOSTREAM_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Utils/IVStringStream.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/** a std::cout style output stream. outputs to the velox console */
extern utils::IVStringStream& vout;

/** equivalent to std::endl */
extern const char* vendl;

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VIOSTREAM_H

