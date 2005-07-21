#ifndef V3D_VTYPEDRESOURCEDATA_H
#define V3D_VTYPEDRESOURCEDATA_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

#include <v3d/Core/SmartPtr/VGuards.h>

#include <V3d/Resource/VResourceData.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Represents typed resource data. Is contained within an enclosing resource
 * and provides type safe access to it's data
 *
 * @author sheijk
 */
template<typename DataType>
class VTypedResourceData : public VResourceData
{
public:
	VTypedResourceData(
		VSharedPtr<DataType> in_pData, 
		VResource* in_pEnclosingResource);
	virtual ~VTypedResourceData();

	DataType* GetData();

	virtual VTypeInfo GetTypeId() const;

private:
	VSharedPtr<DataType> m_pData;
};

//-----------------------------------------------------------------------------

template<typename DataType>
VTypedResourceData<DataType>::VTypedResourceData(
	VSharedPtr<DataType> in_pData, 
	VResource* in_pEnclosingResource)
	: 
	VResourceData(in_pEnclosingResource)
{
	m_pData = in_pData;
}

template<typename DataType>
VTypedResourceData<DataType>::~VTypedResourceData()
{
}

template<typename DataType>
DataType* VTypedResourceData<DataType>::GetData()
{
	return m_pData.Get();
}

template<typename DataType>
VTypeInfo VTypedResourceData<DataType>::GetTypeId() const
{
	return GetTypeInfo<DataType>();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VTYPEDRESOURCEDATA_H
