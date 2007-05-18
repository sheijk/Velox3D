/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDEFAULTRENDERSTEPPART_2005_10_19_H
#define V3D_VDEFAULTRENDERSTEPPART_2005_10_19_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Scene/IVRenderStepPart.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <V3d/Tags/VTag.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VDefaultRenderStepPart : public IVRenderStepPart
{
public:
	VDefaultRenderStepPart();
	virtual ~VDefaultRenderStepPart();

	virtual void Render(IVGraphicsPart* in_pScene);
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

	std::string GetExcludeTagList() const;
	void SetExcludeTagList(const std::string& newTags);
	std::string GetIncludeTagList() const;
	void SetIncludeTagList(const std::string& newTags);

private:
	vbool IsShapeToBeRendered(const IVGraphicsPart& shape) const;

	graphics::VColor4f m_BackgroundColor;

	std::vector<tags::VTag> m_IncludeTags;
	vbool m_bIncludeAll;
	std::vector<tags::VTag> m_ExcludeTags;

	vfloat32 m_fNearPlane;
	vfloat32 m_fFarPlane;
	vfloat32 m_fFOV;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VDefaultRenderStepPart, v3d::scene::IVRenderStepPart);
//-----------------------------------------------------------------------------
#endif // V3D_VDEFAULTRENDERSTEPPART_2005_10_19_H

