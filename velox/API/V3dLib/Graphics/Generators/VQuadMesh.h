#ifndef V3D_VQUADMESH_2004_06_18_H
#define V3D_VQUADMESH_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/VMeshDescription.h>
#include <V3dLib/Graphics/Geometry/VGeometryData.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

template<typename VertexStructure>
class VQuadMesh : public VGeometryData<VertexStructure>
{
public:
	VQuadMesh(vfloat32 in_fSize = 1.0f) :
		VGeometryData<VertexStructure>(VMeshDescription::Quads, 4, 0)
	{
		VertexBuffer& vertices(GetVertexBuffer());
		vertices[0].position = VVector3f(-in_fSize, -in_fSize, 0);
		vertices[1].position = VVector3f(-in_fSize,  in_fSize, 0);
		vertices[2].position = VVector3f( in_fSize,  in_fSize, 0);
		vertices[3].position = VVector3f( in_fSize, -in_fSize, 0);
	}
private:
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VQUADMESH_2004_06_18_H
