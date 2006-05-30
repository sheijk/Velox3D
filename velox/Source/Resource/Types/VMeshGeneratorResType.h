#ifndef V3D_VMESHGENERATORRESTYPE_2005_09_07_H
#define V3D_VMESHGENERATORRESTYPE_2005_09_07_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3dLib/Graphics/Generators/IVMeshGenerator.h>
#include <V3d/Resource.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Executes a mesh generator in the same resource to create a mesh
 *
 * @see IVMeshGenerator
 *
 * @author sheijk
 */
class VMeshGeneratorResType : public resource::IVResourceType
{
	std::vector<VTypeInfo> m_ManagedTypes;

	vbool GenerateVertexBuffer(resource::VResource* in_pResource);
	vbool GenerateMeshDescription(resource::VResource* in_pResource);
public:
	VMeshGeneratorResType();
	virtual ~VMeshGeneratorResType();

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
#endif // V3D_VMESHGENERATORRESTYPE_2005_09_07_H
