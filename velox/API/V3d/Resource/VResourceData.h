#ifndef V3D_VRESOURCEDATA_H
#define V3D_VRESOURCEDATA_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VResourceData
{
public:
	typedef const void* TypeId;

	virtual ~VResourceData();

	virtual TypeId GetTypeId() const = 0;

	template<typename T>
	static TypeId GetTypeId();

protected:
	VResourceData();

	vuint GetReferenceCount() const;

private:
	vuint m_nReferenceCount;
};

//-----------------------------------------------------------------------------

template<typename T>
VResourceData::TypeId VResourceData::GetTypeId()
{
	return reinterpret_cast<TypeId>(typeid(T).name());
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VRESOURCEDATA_H
