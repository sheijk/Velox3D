//TODO: correct file guard
#ifndef V3D_VDataProviderPool_H
#define V3D_VDataProviderPool_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVDataProviderPool.h>

#include <map>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
//TODO: insert documentation here
*/
class VDataProviderPool : public IVDataProviderPool
{
	typedef std::map<std::string, IVDataProvider*> DataProviderMap;

	DataProviderMap m_DataProviders;

public:
	VDataProviderPool(VStringParam in_strName);
	virtual ~VDataProviderPool();

	virtual vbool RegisterDataProvider(IVDataProvider* in_pDP);
	virtual void UnregisterDataProvider(IVDataProvider* in_pDP);
	virtual IVDataProvider& GetDataProvider(VStringParam in_strType) const;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDataProviderPool_H
