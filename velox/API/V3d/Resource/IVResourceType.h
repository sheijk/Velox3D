/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVRESOURCETYPE_2004_11_06_H
#define V3D_IVRESOURCETYPE_2004_11_06_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource/VResourceData.h>
#include <V3d/Resource/VResourceId.h>

#include <V3d/Core/RangeIter/VRangeIterator.h>
#include <V3d/Core/RangeIter/VEmptyPolicy.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A managed resource type. Provides functionality to create resource data
 * of a specific type on request and to decide when to unload it.
 *
 * Needs to be registered to the resource manager: 
 * <code>
 * VServicePtr<IVResourceManager>()->RegisterResourceType(..)
 * </code>
 *
 * @author sheijk
 */
class IVResourceType
{
public:
	/**
	 * Returns the types which this type can add to a resource using Generate()
	 */
	virtual VRangeIterator<VTypeInfo> CreatedTypes() = 0;

	/** 
	 * Generates a data object of the given type and adds it to the given
	 * resource. Returns true if successful
	 *
	 * Attention: if this call fails no data may be added to the resource
	 * system at all. 
	 */
    virtual vbool Generate(VResource* in_pResource, VTypeInfo in_Type) = 0;

	/**
	 * Returns the types which this resource will manage. Managing means to
	 * decide whether mutable access is legal and update resource data if
	 * other resource data in the same resource changed (on NotifyChange)
	 */
	virtual VRangeIterator<VTypeInfo> ManagedTypes()
	{
		return CreateEmptyIterator<VTypeInfo>();
	}

	/** 
	 * False means the resource data may only be accessed as const.
	 * True means it VResource->GetMutableData<T>() is legal for the given
	 * resource and type 
	 */
	virtual vbool AllowMutableAccess(
		const VTypeInfo& in_TypeInfo, const VResource* in_Resource) const
	{
		return false;
	}

	virtual vbool AllowLocking(
		const VTypeInfo& in_TypeInfo, const VResource* in_Resource) const 
	{
		return false;
	}

	/**
	 * Tell the resource type that data inside the given resource of type
	 * in_Type changed. The resource type will need to update the resources
	 * it manages
	 */
	virtual void NotifyChange(
		const VTypeInfo& in_Type, VResource* in_pResource) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_IVRESOURCETYPE_2004_11_06_H

