//TODO: add file creation date to file guard
#ifndef V3D_VGLVERTEXSTREAMRESTYPE_2005_02_03_H
#define V3D_VGLVERTEXSTREAMRESTYPE_2005_02_03_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
//TODO: insert documentation here
 */
class VGLVertexStreamResType : public resource::IVResourceType
{
	std::vector<VTypeInfo> m_ManagedTypes;
public:
	VGLVertexStreamResType();
	virtual ~VGLVertexStreamResType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		VTypeInfo in_Type);

	virtual void NotifyChange(const VTypeInfo& in_Type, 
		resource::VResource* in_pResource);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VGLVERTEXSTREAMRESTYPE_2005_02_03_H
