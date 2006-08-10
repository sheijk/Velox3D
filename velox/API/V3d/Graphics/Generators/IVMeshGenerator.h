#ifndef V3D_IVMESHGENERATOR_2005_09_07_H
#define V3D_IVMESHGENERATOR_2005_09_07_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/VMeshDescription.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

V3D_DECLARE_EXCEPTION(VMeshGenException, VException);

class VVertexBuffer;

/**
 * Interface for a class which can procedurally generate meshes
 */
class IVMeshGenerator
{
public:
	virtual ~IVMeshGenerator() {}

	virtual VVertexBuffer* CreateVertexBuffer() const = 0;
	virtual VVertexBuffer* CreateIndexBuffer() const = 0;
	virtual VMeshDescription::GeometryType GetGeometryType() const = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO(v3d::graphics::IVMeshGenerator);

//-----------------------------------------------------------------------------
#endif // V3D_IVMESHGENERATOR_2005_09_07_H
