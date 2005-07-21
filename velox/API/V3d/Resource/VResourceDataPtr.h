#ifndef V3D_VRESOURCEDATAPTR_H
#define V3D_VRESOURCEDATAPTR_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

#include <V3d/Resource/VTypedResourceData.h>

#include <v3d/Core/SmartPtr/VGuards.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A simple proxy for typed resource data. Will be created by VResource when
 * accessing it's data
 *
 * @author sheijk
 */
template<typename DataType>
class VResourceDataPtr
{
	typedef VTypedResourceData<DataType>* TypedDataPtr;

public:
	VResourceDataPtr();
	VResourceDataPtr(TypedDataPtr in_pData);

	DataType* operator->() const;

	DataType& operator*() const;

private:
	TypedDataPtr m_pData;
};

template<typename T>
VResourceDataPtr<const T> GetResourceData(VStringParam in_strResourceName)
{
	return VResourceId(in_strResourceName)->GetData<T>();
}

template<typename DataType>
vbool Valid(const VResourceDataPtr<const DataType>& ptr)
{
	return (&*ptr) != 0;
}

//-----------------------------------------------------------------------------

template<typename DataType>
VResourceDataPtr<DataType>::VResourceDataPtr()
{
	m_pData = 0;
}

template<typename DataType>
VResourceDataPtr<DataType>::VResourceDataPtr(TypedDataPtr in_pData)
{
	m_pData = in_pData;
}

template<typename DataType>
DataType* VResourceDataPtr<DataType>::operator->() const
{
	return m_pData->GetData();
}

template<typename DataType>
DataType& VResourceDataPtr<DataType>::operator*() const
{
	return * m_pData->GetData();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VRESOURCEDATAPTR_H
