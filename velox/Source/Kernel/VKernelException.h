/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VKERNELEXCEPTION_H
#define V3D_VKERNELEXCEPTION_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VException.h>

#include <string>

//-----------------------------------------------------------------------------
namespace v3d {
namespace kernel {
//-----------------------------------------------------------------------------

	V3D_DECLARE_EXCEPTION(VKernelException, VException);
	V3D_DECLARE_EXCEPTION(VKernelIniException, VKernelException);

//-----------------------------------------------------------------------------
} // namespace kernel
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VKERNELEXCEPTION_H

