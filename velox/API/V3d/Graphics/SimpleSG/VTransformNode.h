/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VTRANSFORMNODE_H
#define V3D_VTRANSFORMNODE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Math/VMatrix.h>
#include "VNodeBase.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Does a simple matrix transformation. Use this for translation, rotation
 * etc.
 *
 * @author sheijk
 */
class VTransformNode : public VNodeBase
{
	math::VMatrix44f m_Transform;

public:
	VTransformNode(const math::VMatrix44f& in_Transform);

	virtual void ApplyTransformation(math::VMatrix44f* io_pMatrix);
	virtual void SetAbsoluteTransformation(const math::VMatrix44f& in_Matrix);

	math::VMatrix44f& GetTransformation()
	{
		return m_Transform;
	}
protected:
	virtual void RemoveThis(IVDrawList* in_pDrawList);
	virtual void CullThis(IVDrawList* in_pDrawList, IVCamera*);
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTRANSFORMNODE_H

