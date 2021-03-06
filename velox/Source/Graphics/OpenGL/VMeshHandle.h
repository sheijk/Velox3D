/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMESHHANDLE_2004_11_07_H
#define V3D_VMESHHANDLE_2004_11_07_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVDevice.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VMeshBase;

/**
 */
class VMeshHandle
{
public:
	VMeshHandle(VMeshBase* in_hBuffer);
	virtual ~VMeshHandle();

	VMeshBase* GetGLMesh() const;

private:
	VMeshBase* m_pMesh;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VMESHHANDLE_2004_11_07_H

