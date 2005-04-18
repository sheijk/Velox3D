#ifndef V3D_VMATERIAL_2005_04_16_H
#define V3D_VMATERIAL_2005_04_16_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/IVMaterial.h>

#include <vector>
#include <list>

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
};

/**
 * @author sheijk
 */
class VMaterial : public IVMaterial
{
	std::vector<VRenderStateList> m_Passes;
	
public:
	VMaterial(const std::vector<VRenderStateList>& in_Passes);
	virtual ~VMaterial();

	virtual vuint PassCount() const;
	virtual const IVPass& GetPass(vuint in_nNum) const;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VMATERIAL_2005_04_16_H
