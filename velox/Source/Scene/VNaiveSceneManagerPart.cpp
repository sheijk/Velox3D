#include <V3d/Scene/VNaiveSceneManagerPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter/VSTLRangeDerefPolicy.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VNaiveSceneManagerPart::VNaiveSceneManagerPart()
{
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

	for(ShapeList::iterator shape = m_Shapes.begin(); shape != m_Shapes.end(); ++shape)
	{
		(*shape)->UpdateAndCull(in_Camera);
	}
}

VRangeIterator<const IVShapePart> VNaiveSceneManagerPart::GetVisibleMeshes() const
{
	return CreateDerefBeginIterator<const IVShapePart>(m_Shapes);
}

void VNaiveSceneManagerPart::Add(IVShapePart* in_pShape)
{
	m_Shapes.insert(in_pShape);
}

void VNaiveSceneManagerPart::Remove(IVShapePart* in_pShape)
{
	m_Shapes.erase(in_pShape);
}

void VNaiveSceneManagerPart::Activate()
{
}

void VNaiveSceneManagerPart::Deactivate()
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
