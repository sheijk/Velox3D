/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VRESOURCEMANAGER_H
#define V3D_VRESOURCEMANAGER_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Resource/IVResourceManager.h>
#include <V3d/Resource/VResource.h>

#include <map>
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VResourceManager : public IVResourceManager
{
public:
	VResourceManager(VStringParam in_strName);
	virtual ~VResourceManager();

	virtual VResourceId CreateResource(VStringParam in_strName);
	virtual VResourceId CreateRandomNamedResource(VStringParam in_strUsageHint);
	virtual VResourceId GetResourceByName(VStringParam in_strName);
	virtual vbool ExistsResource(VStringParam in_strName);
	virtual void RegisterResourceType(VSharedPtr<IVResourceType> in_pResType);
	virtual void NotifyChange(VResource* in_pResource, VTypeInfo in_Type);

	/** Print info about all resources to v3d::vout */
	virtual void DumpResourceInfo() const;

	/**
	 * Get a list of registered resource types which can produce the given type 
	 */
	std::vector<IVResourceType*> GetResourceTypes(VTypeInfo in_Type);

	IVResourceType* GetResourceManager(const VTypeInfo& in_Type);

private:
	typedef std::multimap<VTypeInfo, VSharedPtr<IVResourceType> > CreatorMap;
	typedef std::map<VTypeInfo, VSharedPtr<IVResourceType> > ManagerMap;

	VResource m_RootResource;
	// root for randomly named resources
	VResource* m_pRandomRoot;
	CreatorMap m_TypeCreators;
	ManagerMap m_TypeManagers;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
template<>
inline v3d::resource::VResourceManager* 
	v3d::QueryService<v3d::resource::VResourceManager>()
{
	return QueryObject<v3d::resource::VResourceManager>("resource.manager");
}
//-----------------------------------------------------------------------------
#endif // V3D_VRESOURCEMANAGER_H

