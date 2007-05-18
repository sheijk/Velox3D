/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VFRUSTUMVISPART_2006_09_28_H
#define V3D_VFRUSTUMVISPART_2006_09_28_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Scene/VMeshPartBase.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VFrustumVisPart : public VMeshPartBase
{
public:
	VFrustumVisPart();
	virtual ~VFrustumVisPart();

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

private:
	vfloat32 CalcD() const;

	vfloat32 m_fFOV;
	vfloat32 m_fZNear;
	vfloat32 m_fZFar;
	vfloat32 m_fLineDist;
	vfloat32 m_fAspectRatio;
	vfloat32 m_fXYOffset;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::VFrustumVisPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VFRUSTUMVISPART_2006_09_28_H

