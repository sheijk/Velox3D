#ifndef V3D_VRENDERSTATELIST_H
#define V3D_VRENDERSTATELIST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/IVMaterial.h>

#include <vector>
#include <list>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VRenderStateList : public IVMaterial
{
public:
	typedef std::list<const IVRenderState*> RenderStateList;

private:
	std::vector<const IVRenderState*> m_States;
	//	RenderStateList m_States;
public:
	VRenderStateList(RenderStateList& in_States) :
		m_States(in_States.begin(), in_States.end())
	{
	}

	virtual vuint StateCount() const
	{
		return (vuint)m_States.size();
	}

	virtual const IVRenderState& GetState(vuint in_nPriority) const
	{
		return * m_States[in_nPriority];
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VRENDERSTATELIST_H
