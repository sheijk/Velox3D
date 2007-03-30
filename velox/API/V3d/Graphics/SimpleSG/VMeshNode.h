/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMESHNODE_H
#define V3D_VMESHNODE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Resource/VResourceDataPtr.h>
#include "VNodeBase.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A scenegraph node containing a renderable mesh
 *
 * @author sheijk
 */
class VMeshNode : public VNodeBase
{
public:
	VMeshNode(resource::VResourceDataPtr<IVMesh> in_hMesh);

	virtual void ApplyTransformation(Matrix44f* io_pMatrix);
	virtual void SetAbsoluteTransformation(const Matrix44f& in_Matrix);

protected:
	virtual void RemoveThis(IVDrawList* in_pDrawList);
	virtual void CullThis(IVDrawList* in_pDrawList, IVCamera*);

private:
	vbool m_bInDrawList;
	//IVDevice::MeshHandle m_hMesh;
	VSharedPtr<math::VMatrix44f> m_pAbsTransform;
	VModelMesh m_Model;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMESHNODE_H

