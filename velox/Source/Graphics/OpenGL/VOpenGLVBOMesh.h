//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLVBOMESH_H
#define V3D_VOPENGLVBOMESH_H
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
* VBO rendering implementation
* @author ins
*/

class VOpenGLVBOMesh : public VMeshBase
{
	typedef VVector<vfloat32, 3> Vertex;

	VMeshDescription::ByteDataRef m_TriangleData;
	VMeshDescription::ByteDataRef m_ColorData;
	VMeshDescription::ByteDataRef m_TexCoordData;

	vbool m_bColors;
	vbool m_bTexCoords;

	GLint m_PrimitiveType;
	GLuint m_ArrayID;

public:

	VOpenGLVBOMesh(
		const VMeshDescription& in_Descr,
		IVMaterial* in_pMaterial
		);

	virtual ~VOpenGLVBOMesh();

	virtual void Render();
};


//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------


#endif // V3D_VOPENGLVVBOMESH_H