#ifndef V3D_VCGFXSTATE_2005_08_17_H
#define V3D_VCGFXSTATE_2005_08_17_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "../IVOpenGLRenderState.h"
#include <V3d/Graphics/IVStateCategory.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VCGFXPass;

class VCGFXStateCategory : public IVStateCategory
{
public:
	VCGFXStateCategory();
	IVRenderState* CreateState(const VRenderPass& in_Pass);
	void SetPriority(vuint n) { IVStateCategory::SetPriority(n); }
};

/**
 */
class VCGFXState : public IVRenderState
{
public:
	VCGFXState(VCGFXPass* in_pPass);
	virtual ~VCGFXState();

	virtual void Apply() const;
	virtual const IVStateCategory* GetCategory() const;

	static void SetStateCategory(IVStateCategory* in_pCategory);
private:
	static IVStateCategory* s_pCategory;

	static VCGFXPass* s_pLastPass;
	VCGFXPass* m_pPass;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VCGFXSTATE_2005_08_17_H