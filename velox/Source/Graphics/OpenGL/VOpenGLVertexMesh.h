//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLVERTEXMESH_H
#define V3D_VOPENGLVERTEXMESH_H
//-----------------------------------------------------------------------------
#include <v3d/Math/VVector.h>
#include <v3d/Graphics/VMeshDescription.h>

#include "../DeviceBase/VRenderMethodRegistry.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Simplest rendering method. Renders using glBegin, glVertex.. etc
 *
 * @author sheijk
 */
class VOpenGLVertexMesh : public VBaseMesh
{
	typedef VVector<vfloat32, 3> Vertex;

	VMeshDescription::ByteDataRef m_TriangleData;
	VMeshDescription::ByteDataRef m_ColorData;

public:
	VOpenGLVertexMesh(const VMeshDescription& in_Descr);
	virtual ~VOpenGLVertexMesh();

	virtual void Render();
};


//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------


#endif // V3D_VOPENGLVERTEXMESH_H