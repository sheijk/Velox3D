//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLINDEXMESH_H
#define V3D_VOPENGLINDEXMESH_H
//-----------------------------------------------------------------------------
#include <v3d/Math/VVector.h>
#include <v3d/Graphics/VMeshDescription.h>

#include "../DeviceBase/VRenderMethodRegistry.h"

#include <windows.h>
#include <gl/gl.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Simplest rendering method. Renders using glBegin, glVertex.. etc
 *
 * @author ins 
 */
class VOpenGLIndexMesh : public VBaseMesh
{
	typedef VVector<vfloat32, 3> Vertex;

	VMeshDescription::ByteDataRef m_TriangleData;
	VMeshDescription::ByteDataRef m_ColorData;
	VMeshDescription::ByteDataRef m_TexCoordData;
	VMeshDescription::ByteDataRef m_IndexData;

	GLint m_PrimitiveType;

public:
	VOpenGLIndexMesh(const VMeshDescription& in_Descr);
	virtual ~VOpenGLIndexMesh();

	virtual void Render();	
};


//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------


#endif // V3D_VOPENGLINDEXMESH_H