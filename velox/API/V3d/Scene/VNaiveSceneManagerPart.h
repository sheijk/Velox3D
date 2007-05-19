/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VNAIVESCENEMANAGERPART_2005_09_22_H
#define V3D_VNAIVESCENEMANAGERPART_2005_09_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVSceneManagerPart.h>
#include <V3d/Entity/VUnconnectedPart.h>

#include <set>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A naive scene manager which simply stores all it's shapes in a flat list
 * and does not do any culling
 *
 * @author sheijk
 */
class VNaiveSceneManagerPart : public entity::VUnconnectedPartAdapter<IVSceneManagerPart>
{
public:
	VNaiveSceneManagerPart();
	virtual ~VNaiveSceneManagerPart();

	virtual void UpdateAndCull(const graphics::IVCamera& in_Camera);
	virtual VRangeIterator<const IVShapePart> GetVisibleMeshes() const;

	virtual void Add(IVGraphicsPart* in_pShape);
	virtual void Remove(IVGraphicsPart* in_pShape);

	static std::string GetDefaultId() { return IVGraphicsPart::GetDefaultId(); }
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	typedef	std::set<const IVShapePart*> ShapeList;
	ShapeList m_VisibleShapes;

	typedef std::set<IVGraphicsPart*> GraphicsPartList;
	GraphicsPartList m_Childs;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VNaiveSceneManagerPart, v3d::scene::IVSceneManagerPart);
//-----------------------------------------------------------------------------
#endif // V3D_VNAIVESCENEMANAGERPART_2005_09_22_H

