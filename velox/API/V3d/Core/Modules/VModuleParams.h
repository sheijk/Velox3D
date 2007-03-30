/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMODULEPARAMS_H
#define V3D_VMODULEPARAMS_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
class VObjectRegistry;
class IVMemLogger;

struct VModuleParams
{
	VObjectRegistry* pObjectRegistry;
	IVMemLogger* pMemLogger;
	//vuint moduleId;
//	IVMemoryManager* pMemoryManager;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMODULEPARAMS_H

