#ifndef V3D_VTYPEDRESOURCEDATA_H
#define V3D_VTYPEDRESOURCEDATA_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Core/SmartPtr/VGuards.h>

#include <V3d/Resource/VResourceData.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
template<typename DataType>
class VTypedResourceData : public VResourceData
{
public:
	VTypedResourceData(VSharedPtr<DataType> in_pData);
	virtual ~VTypedResourceData();

	DataType* GetData();

	virtual TypeId GetTypeId() const;

private:
	VSharedPtr<DataType> m_pData;
};

//-----------------------------------------------------------------------------

template<typename DataType>
VTypedResourceData<DataType>::VTypedResourceData(VSharedPtr<DataType> in_pData)
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
VResourceData::TypeId VTypedResourceData<DataType>::GetTypeId() const
{
	return VResourceData::GetTypeId<DataType>();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VTYPEDRESOURCEDATA_H
