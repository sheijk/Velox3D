#ifndef V3D_IVDataProviderPool_H
#define V3D_IVDataProviderPool_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VNamedObject.h>
#include <v3d/VFS/IVDataProvider.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Manages a list of IVDataProviders. Data Providers can be registered and
 * unregistered. Returns the right data provider for a given data source
 * "type"
 */
class IVDataProviderPool : public VNamedObject
{
public:
	IVDataProviderPool(VStringParam in_strName) 
		: VNamedObject(in_strName, 0 )
	{}

	virtual ~IVDataProviderPool() {};

	/** adds a data provider to available data providers */
    virtual vbool RegisterDataProvider(IVDataProvider* in_pDP) = 0;

	/** removes a data provider from list of data providers */
	virtual void UnregisterDataProvider(IVDataProvider* in_pDP) = 0;

	/** returns the data provider for resource type in_strType */
    virtual IVDataProvider& GetDataProvider(VStringParam in_strType) const = 0;

	// Range<IVDataProviderIter> DataProviders() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDataProviderPool_H
