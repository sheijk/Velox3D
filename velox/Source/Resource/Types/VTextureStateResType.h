/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VTEXTURESTATERESTYPE_2004_11_06_H
#define V3D_VTEXTURESTATERESTYPE_2004_11_06_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Image/VImage.h>
#include <V3d/Resource.h>
#include <V3d/Graphics/IVRenderContext.h>
#include "../../Graphics/OpenGL/VTextureState.h"
#include "../../Graphics/OpenGL/Textures/VBaseTexture.h"
#include "../../Graphics/OpenGL/Textures/VTexture2D.h"

#include <vector>
#include <map>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VTextureStateResType : public resource::IVResourceType
{
	typedef std::map<VTypeInfo, GLenum> TextureTargetMap;

	std::vector<VTypeInfo> m_ManagedTypes;
	TextureTargetMap m_TextureTargets;

	GLenum GetTextureTarget(VTypeInfo in_Type) const;

	vbool Create2DTexture(resource::VResource* in_pResource, const VTypeInfo& in_Type);
	vbool CreateCubeTexture(resource::VResource* in_pResource, const VTypeInfo& in_Type);

public:
	VTextureStateResType();
	virtual ~VTextureStateResType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();
	virtual VRangeIterator<VTypeInfo> ManagedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		VTypeInfo in_Type);

	virtual vbool AllowMutableAccess(
		const VTypeInfo& in_TypeInfo, 
		const resource::VResource* in_Resource) const;

	virtual void NotifyChange(const VTypeInfo& in_Type, 
		resource::VResource* in_pResource);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATERESTYPE_2004_11_06_H

