/**
*  VOpenGLVertexMesh
*  Implementation of the class VOpenGLVertexMesh
*  Created on:      25-Nov-2003 23:12:05
*  Original author: insane
*/
//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLVERTEXMESH_H
#define V3D_VOPENGLVERTEXMESH_H
//-----------------------------------------------------------------------------
#include <v3d/Graphics/OpenGL/VOpenGLMesh.h>
#include <v3d/Math/VVector.h>
//-----------------------------------------------------------------------------
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VOpenGLVertexMesh : public VOpenGLMesh
{
private:

	

public:
	
	typedef VVector<vfloat32, 3> Vertex;

	VOpenGLVertexMesh();
	virtual ~VOpenGLVertexMesh();

	std::vector<Vertex> m_VertexList;



};

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------


#endif // V3D_VOPENGLVERTEXMESH_H