/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMESHPART_2005_09_22_H
#define V3D_VMESHPART_2005_09_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/VMeshPartBase.h>

namespace v3d { namespace graphics {
	class IVMesh;
	class IVMaterial;
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VMeshPart : public VMeshPartBase
{
public:
	VMeshPart();

	VMeshPart(
		resource::VResourceDataPtr<const graphics::IVMesh> in_hMesh,
		resource::VResourceDataPtr<const graphics::IVMaterial> in_hMaterial
		);

	VMeshPart(
		const std::string& in_strMeshResource,
		const std::string& in_strMaterialResource
		);

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	resource::VResourceDataPtr<const graphics::IVMesh> m_hMesh;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VMeshPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VMESHPART_2005_09_22_H

