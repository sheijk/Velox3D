#ifndef V3D_VRESOURCEID_H
#define V3D_VRESOURCEID_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource/VResourceDataPtr.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VResource;

/**
 * A proxy to an existing resource
 *
 * @author sheijk
 */
class VResourceId
{
public:
	VResourceId(VResource*);

	VResource* operator->();
	VResource& operator*();

private:
	VResource* m_pResource;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VRESOURCEID_H
