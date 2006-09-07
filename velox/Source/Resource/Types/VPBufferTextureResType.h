/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VPBUFFERTEXTURERESTYPE_H
#define V3D_VPBUFFERTEXTURERESTYPE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Image/VImage.h>
#include <V3d/Resource.h>
#include <V3d/Graphics/IVRenderContext.h>
#include "../../Graphics/OpenGL/Context/VOffscreenContextBase.h"
#include "../../Graphics/OpenGL/VPBufferTexture.h"
#include "../../Graphics/OpenGL/VOpenGLDevice.h"

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
*/
class VPBufferTextureResType : public resource::IVResourceType
{ 
	std::vector<VTypeInfo> m_ManagedTypes;

public:
	VPBufferTextureResType();
	virtual ~VPBufferTextureResType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		VTypeInfo in_Type);

	virtual void NotifyChange(const VTypeInfo& in_Type, 
		resource::VResource* in_pResource);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VPBUFFERTEXTURERESTYPE_H

