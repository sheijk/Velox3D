/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//-------------------------------------------------------------------------
#ifndef V3D_VOPENGLVBORENDERINGMETHOD_H
#define V3D_VOPENGLVBORENDERINGMETHOD_H
//-------------------------------------------------------------------------
#include <V3d/Graphics/VMeshDescription.h>
#include "../DeviceBase/VRenderMethodRegistry.h"
#include "VOpenGLVBOMesh.h"
//-------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------


/**
 * @author ins
 * @version 1.0
 * @created 23-Dez-2003 18:03:00
 */

class VOpenGLVBOMesh;

class VOpenGLVBORenderMethod : public IVRenderMethod 
{
public:
	
	/**
	 * @param creates VBOMesh out of a Mesh description
	 */
	virtual VMeshBase* CreateMesh(
		const VMeshDescription& in_MeshDescr,
		MeshCreationFlags in_Flags,
		IVMaterial* in_pMaterial
		);

};

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------
#endif // V3D_VOGLVBORENDERINGMETHOD_H
