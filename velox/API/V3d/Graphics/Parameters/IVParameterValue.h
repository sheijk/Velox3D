#ifndef V3D_IVPARAMETERVALUE_2005_11_29_H
#define V3D_IVPARAMETERVALUE_2005_11_29_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVParameter;

/**
 */
class IVParameterValue
{
public:
	virtual ~IVParameterValue() {}

	virtual void Apply(const IVParameter& in_Param) const = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_IVPARAMETERVALUE_2005_11_29_H
