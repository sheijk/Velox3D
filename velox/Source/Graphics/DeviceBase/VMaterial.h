#ifndef V3D_VMATERIAL_2005_04_16_H
#define V3D_VMATERIAL_2005_04_16_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Core/SmartPtr/VSharedPtr.h>
#include <v3d/Graphics/IVMaterial.h>
#include "VRenderStateList.h"

#include <vector>
#include <list>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VMaterial : public IVMaterial
{
public:
	typedef std::vector< VSharedPtr<VRenderStateList> > PassList;

	VMaterial(const PassList& in_Passes);
	virtual ~VMaterial();

	virtual vuint PassCount() const;
	virtual const IVPass& GetPass(vuint in_nNum) const;

	//virtual void SetParameter(ParamHandle in_Param, vfloat32 in_Value) const;
	//virtual void SetParameter(ParamHandle in_Param, VVector4f in_Value) const;

	virtual VRangeIterator<IVParameter> Parameters();
	virtual IVParameter* GetParameterByName(
		const std::string& in_strName);

private:
	PassList m_Passes;
	typedef std::list<IVParameter*> ParameterContainer;
	ParameterContainer m_Parameters;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VMATERIAL_2005_04_16_H
