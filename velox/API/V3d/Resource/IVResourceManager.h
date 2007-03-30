/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVRESOURCEMANAGER_2004_11_06_H
#define V3D_IVRESOURCEMANAGER_2004_11_06_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Resource/VResourceId.h>
#include <V3d/Resource/IVResourceType.h>

#include <V3d/Core/VNamedObject.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>
#include <V3d/Core.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * The resource manager. Maintains a hyrarchical tree of resources similar
 * to a file system. Each resource may have arbitrary sub resources. Data
 * may be attached to resources. A resource can have data of multiple types
 * attached, but only one object of each type. For instance you might attach
 * a VFileName, a VImage and a VOpenGLTextureName object to the same resource
 * Path names use '/' as the delimeter
 *
 * @author sheijk
 */
class IVResourceManager : public VNamedObject
{
public:
	/** Creates a new named resource if it did not exist previously */
	virtual VResourceId CreateResource(VStringParam in_strName) = 0;

	/** Returns a resource by it's fully qualified name */
	virtual VResourceId GetResourceByName(VStringParam in_strName) = 0;

	virtual vbool ExistsResource(VStringParam in_strName) = 0;

	/** 
	 * Returns a resource for internal usage. It will have a randomly generated
	 * name containing in_strUsageHint and will be placed in an unspecified
	 * path
	 */
	virtual VResourceId CreateRandomNamedResource(VStringParam in_strUsageHint) = 0;

	/** Register a resource type which may automatically be generated */
	virtual void RegisterResourceType(VSharedPtr<IVResourceType> in_pResType) = 0;

	/** Please ignore this function - thank you ;) */
	virtual void DumpResourceInfo() const = 0;

	/**
	 * Tell all resource managers about the data change so they can update
	 * other data in the same resource appropriately
	 */
	virtual void NotifyChange(VResource* in_pResource, VTypeInfo in_Type) = 0;

	virtual ~IVResourceManager() {}

protected:
	IVResourceManager(VStringParam in_strName) : VNamedObject(in_strName, 0) {}
};

typedef VServicePtr<IVResourceManager> VResourceManagerPtr;
//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
template<>
inline v3d::resource::IVResourceManager* 
	v3d::QueryService<v3d::resource::IVResourceManager>()
{
	return QueryObject<v3d::resource::IVResourceManager>("resource.manager");
}
//-----------------------------------------------------------------------------
#endif // V3D_IVRESOURCEMANAGER_2004_11_06_H

