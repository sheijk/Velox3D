#ifndef V3D_VRESOURCE_H
#define V3D_VRESOURCE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource/VResourceData.h>
#include <V3d/Resource/VTypedResourceData.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <V3d/Resource/VResourceDataPtr.h>
#include <V3d/Resource/ResourceExceptions.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>

#include <vector>
#include <string>
#include <map>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A resource in the resource manager. May have an arbitrary number of sub
 * resources and attached data. The data is identified by it's type, thus
 * of each type only one data instance may be attached
 *
 * @author sheijk
 */
class VResource
{
public:
	VResource(const std::string in_strName, VResource* in_pParent = 0);
	virtual ~VResource();

	/** Return the name of the resource (without it's path) */
	std::string GetName() const;

	/** Return the fully qualified (including it's path) name */
	std::string GetQualifiedName() const;

	/** Creates a new sub resource if no one with the same name exist yet */
	VResource* AddSubResource(const std::string& in_strChildName);

	/** Creates a sub resource generating an unused name */
	VResource* AddRandomNamedSubResource();

	/** Find a sub resource with the given name, 0 if no one found */
	VResource* GetSubResource(const std::string& in_strChildName);

	/** Get an iterator to access all child resources */
	VRangeIterator<VResource> ChildIterator();

	VRangeIterator<const VResource> ChildIterator() const;

	/** 
	 * Find a resource by it's (relative) path
	 * Paths starting with '/' will be treated as absolute paths. All other paths
	 * will be treated as relative to the current element. You may use '..' to
	 * refer to the parent element.
	 * Path example: /absolute/path/resname or relative/path/../res
	 */
	VResource* GetResourceByPath(const std::string& in_strChildName);

	/** Print debug info about content to v3d::vout */
	void DumpInfo(const std::string& in_strPrefix) const;

	/**
	 * Adds new data to the resource. The data can only be added if no other
	 * data of the same type has been added previously. The resource will
	 * take over ownership of the data and will maintain it's lifecycle. Thus
	 * you should not delete the added data yourself
	 */
	template<typename DataType>
	void AddData(DataType* in_pData);

	template<typename DataType>
	void AddDynamicTypedData(DataType* in_pData);

	/**
	 * Returns the data of type DataType attached to the resource if it exists.
	 * Will throw an exception if the data does not exist
	 *
	 * @throws v3d::resource::VDataNotFoundException
	 */
	template<typename DataType>
	VResourceDataPtr<const DataType> GetData();

	/*
	 * Returns true if data of the given type is present
	 */
	template<typename DataType>
	vbool ContainsData();

	vbool ContainsData(VResourceData::TypeId in_Type);

private:
	typedef std::vector< VSharedPtr<VResource> > ResourceContainer;
	typedef std::map< VResourceData::TypeId, VSharedPtr<VResourceData> >
		DataMap;

	void SetParent(VResource* in_pParent);
	const VResource* GetParent() const;
	VResource* GetParent();
	VResource* GetRootResource();

	VResourceData* GetData(VResourceData::TypeId in_Type);

	void AddData(
		VResourceData::TypeId in_Type, 
		VSharedPtr<VResourceData> in_pData);

	std::string m_strName;
	ResourceContainer m_SubResources;
	DataMap m_Data;
	VResource* m_pParent;
};

//-----------------------------------------------------------------------------
template<typename DataType>
void VResource::AddDynamicTypedData(DataType* in_pData)
{
	// get type id
	VResourceData::TypeId type = VResourceData::TypeId(in_pData);

	// create container
	VSharedPtr< VTypedResourceData<DataType> > pContainer(
		new VTypedResourceData<DataType>(VSharedPtr<DataType>(in_pData), this));

	// and store it
	AddData(type, pContainer);
}

template<typename DataType>
void VResource::AddData(DataType* in_pData)
{
	// get type id
	VResourceData::TypeId type = VResourceData::TypeId::Create<DataType>();

	// create container
	VSharedPtr< VTypedResourceData<DataType> > pContainer(
		new VTypedResourceData<DataType>(VSharedPtr<DataType>(in_pData), this));

	// and store it
	AddData(type, pContainer);
}

template<typename DataType>
VResourceDataPtr<const DataType> VResource::GetData()
{
	// get type id
	VResourceData::TypeId type = VTypeId::Create<DataType>();

	VResourceData* pUntypedData = GetData(type);

	VTypedResourceData<const DataType>* pResData = 
		reinterpret_cast< VTypedResourceData<const DataType>* >(pUntypedData);

	return VResourceDataPtr<const DataType>(pResData);
}

template<typename DataType>
vbool VResource::ContainsData()
{
	// get type id
	VResourceData::TypeId type = VTypeId::Create<DataType>();

	// look for type id
	return ContainsData(type);
}

//template<typename DataType>
//VResourceData::TypeId VResource::GetTypeId()
//{
//	return VResourceData::TypeId::Create<DataType>();
//}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VRESOURCE_H
