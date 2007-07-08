/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/VNaiveSceneManagerPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter/VSTLRangeDerefPolicy.h>

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VNaiveSceneManagerPart::VNaiveSceneManagerPart()
{
	m_bVisibleShapesDirty = false;
}

/**
 * d'tor
 */
VNaiveSceneManagerPart::~VNaiveSceneManagerPart()
{
}

void VNaiveSceneManagerPart::UpdateAndCull(const graphics::IVCamera& in_Camera)
{
	using namespace std;

	m_VisibleShapes.clear();

	// update all graphics parts and create list of visible shapes
	for(GraphicsPartList::iterator child = m_Childs.begin(); 
		child != m_Childs.end(); ++child)
	{
		(*child)->UpdateAndCull(in_Camera);

		VRangeIterator<const IVShapePart> shape = (*child)->GetVisibleMeshes();
		while( shape.HasNext() )
		{
			m_VisibleShapes.insert(&*shape);
			++shape;
		}
	}

	m_bVisibleShapesDirty = false;
}

VRangeIterator<const IVShapePart> VNaiveSceneManagerPart::GetVisibleMeshes() const
{
	if( ! m_bVisibleShapesDirty )
	{
		return CreateDerefBeginIterator<const IVShapePart>(m_VisibleShapes);
	}
	else
	{
		V3D_THROW(VException, 
			"Need to call UpdateAndCull after adding/removing meshes" );
	}
}

void VNaiveSceneManagerPart::Add(IVGraphicsPart* in_pChild)
{
	m_Childs.insert(in_pChild);
	m_bVisibleShapesDirty = true;
}

void VNaiveSceneManagerPart::Remove(IVGraphicsPart* in_pChild)
{
	m_Childs.erase(in_pChild);
	m_bVisibleShapesDirty = true;
}

V3D_REGISTER_PART_PARSER(VNaiveSceneManagerPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

