#ifndef V3D_VSTLIterDerefAdaptor_H
#define V3D_VSTLIterDerefAdaptor_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/IVIterator.h>

//-----------------------------------------------------------------------------
namespace v3d {
	//-----------------------------------------------------------------------------

//TODO: testen

/**
 * IterType::value_type must be TargetType*
 */
template<typename TargetType, typename IterType>
class VSTLIterDerefAdaptor 
	: public IVIterator<TargetType>
{
public:
	typedef typename TargetType ValueType;

	VSTLIterDerefAdaptor(const IterType& in_Iter);
	virtual ~VSTLIterDerefAdaptor();

	virtual vbool Proceed();
	virtual vbool MoveBack();
	virtual vbool HasSubject();
	virtual ValueType& Get() const;

private:
	IterType m_Iter;
};

//-----------------------------------------------------------------------------
#include "VSTLIterDerefAdaptor.inl"
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLIterDerefAdaptor_H
