//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLINDEXMESH_H
#define V3D_VOPENGLINDEXMESH_H
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
 * @author ins/sheijk
 */
class VOpenGLIndexMesh : public VMeshBase
{
	typedef VVector<vfloat32, 3> Vertex;

	VMeshDescription m_MeshDescription;
	//VMeshDescription::ByteDataRef m_TriangleData;
	//VMeshDescription::ByteDataRef m_ColorData;
	//VMeshDescription::ByteDataRef m_TexCoordData;
	//VMeshDescription::ByteDataRef m_IndexData;

	GLint m_PrimitiveType;

public:
	VOpenGLIndexMesh(
		const VMeshDescription& in_Descr,
		std::vector<IVMaterial*> in_Materials
		);

	virtual ~VOpenGLIndexMesh();

	virtual void Render();	
};


//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------


#endif // V3D_VOPENGLINDEXMESH_H