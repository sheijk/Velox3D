/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VSHOWSELECTIONPART_2007_08_06_H
#define V3D_VSHOWSELECTIONPART_2007_08_06_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/VMeshPartBase.h>

#include <V3d/Graphics/Geometry/VColor4f.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VShowSelectionPart : public VMeshPartBase
{
public:
	VShowSelectionPart();
	virtual ~VShowSelectionPart();

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

	graphics::VColor4f m_Color;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VShowSelectionPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VSHOWSELECTIONPART_2007_08_06_H

