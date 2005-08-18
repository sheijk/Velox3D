#ifndef V3D_VRENDERSTATELIST_2005_08_17_H
#define V3D_VRENDERSTATELIST_2005_08_17_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVMaterial.h>
#include <V3d/Graphics/IVRenderState.h>

#include <list>
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VRenderStateList : public IVPass
{
	std::vector<const IVRenderState*> m_States;

public:
	typedef std::list<const IVRenderState*> RenderStateList;
	VRenderStateList(std::list<const IVRenderState*>& in_States);

	virtual vuint StateCount() const;

	virtual const IVRenderState& GetState(vuint in_nPriority) const;

protected:
	void SetState(IVRenderState* in_pRenderState);

private:
	void ClearState(vuint in_nPriority);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VRENDERSTATELIST_2005_08_17_H
