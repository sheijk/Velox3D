#ifndef V3D_VRESIZABLEGEOMETRY_2004_04_10_H
#define V3D_VRESIZABLEGEOMETRY_2004_04_10_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics.h>
#include <V3dLib/Graphics/Geometry/VDynamicGeometryData.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

template<typename VertexStructure>
class VResizeableGeometryData : public VDynamicGeometryData<VertexStructure>
{
public:
	void ResizeVertexBuffer(vuint in_nSize)
	{
		VDynamicGeometryData<VertexStructure>::ResizeVertexBuffer(in_nSize);
	}

	void ResizeIndexBuffer(vuint in_nSize)
	{
		VDynamicGeometryData<VertexStructure>::ResizeIndexBuffer(in_nSize);
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VRESIZABLEGEOMETRY_2004_04_10_H
