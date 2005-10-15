#ifndef V3D_VRESOURCEMANAGER_H
#define V3D_VRESOURCEMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

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
	virtual VResourceId GetResourceByName(VStringParam in_strName);
	virtual void RegisterResourceType(VSharedPtr<IVResourceType> in_pResType);

	/** Print info about all resources to v3d::vout */
	virtual void DumpResourceInfo() const;

	/**
	 * Get a list of registered resource types which can produce the given type 
	 */
	std::vector<IVResourceType*> GetResourceTypes(VTypeInfo in_Type);

private:
	typedef std::multimap<VTypeInfo, VSharedPtr<IVResourceType> > TypeMap;

	VResource m_RootResource;
	TypeMap m_ManagedTypes;
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
