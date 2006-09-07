/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSPHEREMESHPART_2005_12_31_H
#define V3D_VSPHEREMESHPART_2005_12_31_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/VMeshPartBase.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Draws a simple sphere using glutSphere
 *
 * @author sheijk
 */
class VSphereMeshPart : public VMeshPartBase
{
public:
	VSphereMeshPart(vfloat32 in_fRadius = 1.0f, vuint in_nDetail = 20);

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:
	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);
	
	vfloat32 m_fRadius;
	vuint m_nDetail;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VSphereMeshPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VSPHEREMESHPART_2005_12_31_H

