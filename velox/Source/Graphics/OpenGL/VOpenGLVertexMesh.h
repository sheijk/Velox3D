//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLVERTEXMESH_H
#define V3D_VOPENGLVERTEXMESH_H
//-----------------------------------------------------------------------------
#include <v3d/Math/VVector.h>
#include <v3d/Graphics/VMeshDescription.h>

#include "../DeviceBase/VMeshBase.h"

#include <windows.h>
#include <gl/gl.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Simplest rendering method. Renders using glBegin, glVertex.. etc
 *
 * @author sheijk
 */
class VOpenGLVertexMesh : public VMeshBase
{
	typedef VVector<vfloat32, 3> Vertex;

	VMeshDescription::ByteDataRef m_TriangleData;
	VMeshDescription::ByteDataRef m_ColorData;
	VMeshDescription::ByteDataRef m_TexCoordData;

	vbool m_bColors;
	vbool m_bTexCoords;

	GLint m_PrimitiveType;

public:
	VOpenGLVertexMesh(
		const VMeshDescription& in_Descr,
		IVMaterial* in_pMaterial
		);

	virtual ~VOpenGLVertexMesh();

	virtual void Render();
};


//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------


#endif // V3D_VOPENGLVERTEXMESH_H