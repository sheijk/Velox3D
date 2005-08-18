#ifndef V3D_IVSTATECATEGORY_H
#define V3D_IVSTATECATEGORY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/IVRenderState.h>
#include <v3d/Graphics/VEffectDescription.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
class IVRenderState;

class IVStateCategory
{
public:
	virtual IVRenderState* CreateState(const VRenderPass& in_Pass) = 0;
	virtual vuint GetPriority() const { return m_nPriority; }

protected:
	void SetPriority(vuint in_nPriority) { m_nPriority = in_nPriority; }

private:
	vuint m_nPriority;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVSTATECATEGORY_H
