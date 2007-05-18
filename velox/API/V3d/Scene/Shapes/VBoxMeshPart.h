/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VBOXMESHPART_2006_02_23_H
#define V3D_VBOXMESHPART_2006_02_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Scene/VMeshPartBase.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <V3d/Math/VBoundingBox.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Renders a bounding box mesh
 * @author ins
 */
class VBoxMeshPart : public VMeshPartBase
{
public:
	VBoxMeshPart();
	VBoxMeshPart(const graphics::VColor4f& in_Color);
	VBoxMeshPart(const math::VBoundingBox& in_BoundingBox);
	VBoxMeshPart(
		const math::VBoundingBox& in_BoundingBox,
		const graphics::VColor4f& in_Color);

	void SetColor(const graphics::VColor4f& in_Color);
	void SetBoundingBox(const math::VBoundingBox& in_BoungingBox);
	
	void SendGeometry(graphics::IVDevice& in_Device) const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

private:
	math::VVector3f GetMinPoint() const;
	void SetMinPoint(const math::VVector3f& newPoint);
	math::VVector3f GetMaxPoint() const;
	void SetMaxPoint(const math::VVector3f& newPoint);

	graphics::VColor4f m_Color;
	math::VBoundingBox m_BoundingBox;
	vbool m_bWireFrame;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::VBoxMeshPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VBOXMESHPART_2006_02_23_H

