/**
 *  VOpenGLMesh.h
 *  Implementation of the base class VOpenGLMesh
 *  Created on:      25-Nov-2003 23:12:05
 *  Original author: insane
 */
//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLMESH_H
#define V3D_VOPENGLMESH_H
//-----------------------------------------------------------------------------
#include <v3d/Graphics/IVMesh.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VOpenGLMesh : public IVMesh 
{
public:

	VOpenGLMesh();
	virtual ~VOpenGLMesh();

	enum GlTypes
	{
		VertexBuffer = 1,
		DisplayList,
		VertexMode
	};

	GlTypes m_Type;

};

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------


#endif // V3D_VOPENGLMESH_H