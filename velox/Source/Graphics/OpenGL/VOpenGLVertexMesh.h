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

	VMeshDescription::FloatDataRef m_TriangleData;

public:
	VOpenGLVertexMesh(const VMeshDescription& in_Descr);
	virtual ~VOpenGLVertexMesh();

	virtual void Render();	
};

class VStupidRenderMethod : public IVRenderMethod
{
	virtual VOpenGLVertexMesh* CreateMesh(VMeshDescription& in_MeshDescr);
};

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------


#endif // V3D_VOPENGLVERTEXMESH_H