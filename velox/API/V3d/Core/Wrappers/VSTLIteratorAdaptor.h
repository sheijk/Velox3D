#ifndef V3D_VSTLITERATORADAPTOR_H
#define V3D_VSTLITERATORADAPTOR_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/IVIterator.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

//TODO: testen
//TODO: 2ter templ. param fuer ValueType, der IterType::value_type als Standard hat

/**
 * Template wrapper for stl iterators. Should work with any STL compliant
 * iterator.
 * Requires an interator conforming to the STL iterator conventions
 */
template<typename IterType, typename TargetType = typename IterType::value_type>
class VSTLIteratorAdaptor 
	: public IVIterator<TargetType>
{
public:
	VSTLIteratorAdaptor(const IterType& in_Iter);
	virtual ~VSTLIteratorAdaptor();

	virtual vbool Proceed();
	virtual vbool MoveBack();
	virtual vbool HasSubject();
	virtual ValueType& Get() const;

private:
	IterType m_Iter;
};

//-----------------------------------------------------------------------------
#include "VSTLIteratorAdaptor.inl"
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLITERATORADAPTOR_H
