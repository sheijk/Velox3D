/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VARROWMESHPART_2005_10_15_H
#define V3D_VARROWMESHPART_2005_10_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Scene/VMeshPartBase.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Renders an arrow oriented along the z-axis with it's tip at z=1.
 * Can be used to show the orientation of a VRBTransform, will point along
 * view direction
 *
 * @author sheijk
 */
class VArrowMeshPart : public VMeshPartBase
{
public:
	VArrowMeshPart();
	VArrowMeshPart(const graphics::VColor4f& in_Color);

	void SetColor(const graphics::VColor4f& in_Color);
	void SendGeometry(graphics::IVDevice& in_Device) const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:
	graphics::VColor4f m_Color;
	vfloat32 m_fSize;

	static void sendCircleVertices(vfloat32 z1);

	static void sendCircleVertices(vfloat32 z1, vfloat32 z2, bool normals);

protected:
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VArrowMeshPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VARROWMESHPART_2005_10_15_H

