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
	class TypeId
	{
	public:
		template<typename T>
		static TypeId Create()
		{
			return TypeId(typeid(T).name());
		}

		vbool operator<(const TypeId& other) const;
		vbool operator==(const TypeId& other) const;
		vbool operator!=(const TypeId& other) const;

	private:
		TypeId(const vchar* in_strName);

		const vchar* m_strName;
	};
	//typedef const void* TypeId;

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
	return TypeId::Create<T>();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VRESOURCEDATA_H
