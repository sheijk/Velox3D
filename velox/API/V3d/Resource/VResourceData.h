#ifndef V3D_VRESOURCEDATA_H
#define V3D_VRESOURCEDATA_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VResource;

/**
 * Represents data containend within a resource
 * Abstract base class fuer VTypedResource which contains the concrete data
 *
 * @author sheijk
 */
class VResourceData
{
public:
	virtual ~VResourceData();

	/** Returns an id representing the resource data's type */
	virtual VTypeInfo GetTypeId() const = 0;

	/** Get the resource this data is contained in */
	VResource* GetEnclosingResource();
	const VResource* GetEnclosingResource() const;

protected:
	VResourceData(VResource* in_pResource);

	vuint GetReferenceCount() const;

private:
	/** Number of references to date */
	vuint m_nReferenceCount;
	/** The resource the data is contained in */
	VResource* m_pResource;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VRESOURCEDATA_H
