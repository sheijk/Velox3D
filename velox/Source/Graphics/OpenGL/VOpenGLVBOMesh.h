//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLVBOMESH_H
#define V3D_VOPENGLVBOMESH_H
//-----------------------------------------------------------------------------
#include <v3d/Math/VVector.h>
#include <v3d/Graphics/VMeshDescription.h>

#include "../DeviceBase/VMeshBase.h"
#include <map>

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
	
public:

	typedef std::map<VMeshDescription::ByteBufferHandle, GLuint> HandleVBOMap;

	VOpenGLVBOMesh(
		const VMeshDescription& in_Descr,
		IVMaterial* in_pMaterial
		); 

	virtual ~VOpenGLVBOMesh();

	virtual void Render();

private: 
	typedef VVector<vfloat32, 3> Vertex;
	typedef std::pair<VMeshDescription::ByteBufferHandle, GLuint> HandleVBOPair;

	VMeshDescription::ByteDataRef m_TriangleData;
	VMeshDescription::ByteDataRef m_ColorData;
	VMeshDescription::ByteDataRef m_TexCoordData;
	VMeshDescription::ByteDataRef m_IndexData;

	vbool m_bColors;
	vbool m_bTexCoords;
	vbool m_bIndex;

	GLint m_PrimitiveType;
	
	//store all buffer id's. they can be equal
	GLuint m_VertexVBOID;  
	GLuint m_ColorVBOID;
	GLuint m_TexCoordVBOID;
	GLuint m_IndexVBOID;

	GLuint GetVertexBuffer(VMeshDescription::ByteBufferHandle in_hHandle);

	static HandleVBOMap s_VBOMap;

};


//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------
 

#endif // V3D_VOPENGLVVBOMESH_H