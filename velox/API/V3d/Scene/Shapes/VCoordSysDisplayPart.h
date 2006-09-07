/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCOORDSYSDISPLAYPART_2005_10_15_H
#define V3D_VCOORDSYSDISPLAYPART_2005_10_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/VMeshPartBase.h>
#include <V3d/Graphics/Geometry/VColor4f.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Displays three lines showing the x,y,z axis using lines with length 1
 * x - red, y - green, z - blue
 *
 * @author sheijk
 */
class VCoordSysDisplayPart : public scene::VMeshPartBase
{
public:
	VCoordSysDisplayPart(vfloat32 in_fBrightness = 1.0f);

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	graphics::VColor4f m_XColor;
	graphics::VColor4f m_YColor;
	graphics::VColor4f m_ZColor;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VCoordSysDisplayPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VCOORDSYSDISPLAYPART_2005_10_15_H

