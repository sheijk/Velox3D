#ifndef V3D_VCGFXMATERIAL_2005_08_18_H
#define V3D_VCGFXMATERIAL_2005_08_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "VCGFXPass.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VCGFXMaterial : public IVMaterial
{
public:
	VCGFXMaterial(VRenderStateList::RenderStateList in_DefaultStates, const std::string& in_strSource);

	virtual vuint PassCount() const;
	virtual const IVPass& GetPass(vuint in_nNum) const;

	void ApplyAutoParameters();

private:
	enum AutoParameterType
	{
		APModelViewProjectionMatrix
	};

	struct AutoParameter
	{
		CGparameter param;
		AutoParameterType type;
	};

	std::vector<AutoParameter> m_AutoParameters;

	static CGcontext s_Context;

	std::vector< VSharedPtr<VCGFXPass> > m_Passes;
	CGeffect m_Effect;
	CGtechnique m_Technique;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO_WITHPARENT(v3d::graphics::VCGFXMaterial, v3d::graphics::IVMaterial);
//-----------------------------------------------------------------------------
#endif // V3D_VCGFXMATERIAL_2005_08_18_H
