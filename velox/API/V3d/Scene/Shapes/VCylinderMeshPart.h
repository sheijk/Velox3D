/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VCYLINDERMESHPART_2006_01_20_H
#define V3D_VCYLINDERMESHPART_2006_01_20_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Scene/VMeshPartBase.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <glew/glew.h>
#include <gl/glut.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Renders a cylinder mesh
 * @author: ins
 */
class VCylinderMeshPart : public VMeshPartBase
{
public:
	VCylinderMeshPart();
	VCylinderMeshPart(const graphics::VColor4f& in_Color);
	VCylinderMeshPart(
		vfloat32 in_fTopRadius,
		vfloat32 in_fButtonRadius,
		vfloat32 in_Height,
		int in_iSlices,
		int in_iStacks);
	~VCylinderMeshPart();

	void SetColor(const graphics::VColor4f& in_Color);
	void SendGeometry(graphics::IVDevice& in_Device) const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

private:
	graphics::VColor4f m_Color;
	vfloat32 m_fTopRadius;
	vfloat32 m_fButtonRadius;
	vfloat32 m_fHeight;
	int m_iSlices;
  	int m_iStacks;
	GLUquadricObj* pGluObject;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VCylinderMeshPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif //V3D_VCYLINDERMESHPART_2006_01_20_H