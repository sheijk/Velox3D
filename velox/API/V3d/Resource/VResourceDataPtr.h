/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VRESOURCEDATAPTR_H
#define V3D_VRESOURCEDATAPTR_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

#include <V3d/Resource/VTypedResourceData.h>

#include <V3d/Core/SmartPtr/VGuards.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VResource;

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
	VResourceDataPtr(const std::string& in_strResourceName);

	DataType* operator->() const;
	DataType& operator*() const;

	/** Return the resource this data object belongs to */
	VResource* GetEnclosingResource();
	const VResource* GetEnclosingResource() const;

	/** Returns the name of the enclosing resource or "" if it is 0 */
	std::string GetResourceName() const;

	VTypeInfo GetTypeId() { return m_pData->GetTypeId(); }

	vbool operator==(void* ptr) const;
	vbool operator!=(void* ptr) const;

	vbool operator==(const VResourceDataPtr<DataType>& other) const;
	vbool operator!=(const VResourceDataPtr<DataType>& other) const;
private:
	TypedDataPtr m_pData;
};

template<typename T>
VResourceDataPtr<const T> GetResourceData(VStringParam in_strResourceName);

template<typename T>
VResourceDataPtr<T> GetMutableResourceData(VStringParam in_strResourceName);

//-----------------------------------------------------------------------------
template<typename T>
vbool VResourceDataPtr<T>::operator==(void* ptr) const
{
	return m_pData == ptr;
}

template<typename T>
vbool VResourceDataPtr<T>::operator!=(void* ptr) const
{
	return m_pData != ptr;
}

template<typename T>
vbool VResourceDataPtr<T>::operator==(const VResourceDataPtr<T>& other) const
{
	if( m_pData != 0 && other.m_pData != 0 )
		return m_pData->GetData() == other.m_pData->GetData();
	else if( m_pData == 0 && other.m_pData == 0 )
		return true;
	else
		return false;
}

template<typename T>
vbool VResourceDataPtr<T>::operator!=(const VResourceDataPtr<T>& other) const
{
	return ! (*this == other);
}

template<typename T>
struct VResDataAccessorUtil
{
    VResourceDataPtr<T> operator()(const std::string& in_ResName) const
	{
		return typename VResourceId(in_ResName.c_str())->GetMutableData<T>();
	}
};

template<typename T>
struct VResDataAccessorUtil<const T>
{
	VResourceDataPtr<const T> operator()(const std::string& in_ResName) const
	{
		return VResourceId(in_ResName.c_str())->GetData<T>();
	}
};

template<typename DataType>
VResourceDataPtr<DataType>::VResourceDataPtr(const std::string& in_strResourceName)
{
	*this = VResDataAccessorUtil<DataType>()(in_strResourceName);
}

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
	if( m_pData )
		return m_pData->GetData();
	else
		return 0;
}

template<typename DataType>
DataType& VResourceDataPtr<DataType>::operator*() const
{
	return * operator->();
}

template<typename DataType>
VResource* VResourceDataPtr<DataType>::GetEnclosingResource() { 
	if( m_pData != 0 )
		return m_pData->GetEnclosingResource();
	else
		return 0;
}

template<typename DataType>
const VResource* VResourceDataPtr<DataType>::GetEnclosingResource() const 
{ 
	if( m_pData != 0 )
		return m_pData->GetEnclosingResource();
	else
		return 0;
}

template<typename DataType>
std::string VResourceDataPtr<DataType>::GetResourceName() const
{
	if( GetEnclosingResource() != 0 )
		return GetEnclosingResource()->GetQualifiedName();
	else
		return "";
}

template<typename T>
VResourceDataPtr<const T> GetResourceData(VStringParam in_strResourceName)
{
	//return VResourceId(in_strResourceName)->GetData<T>();
	return VResourceDataPtr<const T>(in_strResourceName);
}

template<typename T>
VResourceDataPtr<T> GetMutableResourceData(VStringParam in_strResourceName)
{
	//return VResourceId(in_strResourceName)->GetMutableData<T>();
	return VResourceDataPtr<T>(in_strResourceName);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VRESOURCEDATAPTR_H

