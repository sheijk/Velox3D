#ifndef V3D_VRESOURCEDATA_H
#define V3D_VRESOURCEDATA_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VResource;

/**
 * Represents data containend within a resource
 * Abstract base class fuer VTypedResource which contains the concrete data
 *
 * @author sheijk
 */
class VResourceData
{
public:
	class TypeId
	{
	public:
		template<typename T>
		static inline TypeId Create();

		vbool operator<(const TypeId& other) const;
		vbool operator==(const TypeId& other) const;
		vbool operator!=(const TypeId& other) const;

	private:
		TypeId(const vchar* in_strName);

		const vchar* m_strName;
	};

	virtual ~VResourceData();

	/** Returns an id representing the resource data's type */
	virtual TypeId GetTypeId() const = 0;

	/** Get the resource this data is contained in */
	VResource* GetEnclosingResource() const;

	/** Returns the type id for a resource of the type T */
	template<typename T>
	static TypeId GetTypeId();

protected:
	VResourceData(VResource* in_pResource);

	vuint GetReferenceCount() const;

private:
	/** Number of references to date */
	vuint m_nReferenceCount;
	/** The resource the data is contained in */
	VResource* m_pResource;
};

//-----------------------------------------------------------------------------

template<typename T>
VResourceData::TypeId VResourceData::GetTypeId()
{
	return TypeId::Create<T>();
}

template<typename T>
static VResourceData::TypeId VResourceData::TypeId::Create()
{
	return TypeId(typeid(T).name());
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VRESOURCEDATA_H
