/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLVBOMESH_H
#define V3D_VOPENGLVBOMESH_H
//-----------------------------------------------------------------------------
#include <V3d/Math/VVector.h>
#include <V3d/Graphics/VMeshDescription.h>

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

	typedef std::map<VMeshDescription::BufferHandle, GLuint> HandleVBOMap;

	VOpenGLVBOMesh(
		const VMeshDescription& in_Descr,
		IVMaterial* in_pMaterial
		); 

	virtual ~VOpenGLVBOMesh();

	virtual void Render();

private: 
	typedef VVector<vfloat32, 3> Vertex;
	typedef std::pair<VMeshDescription::BufferHandle, GLuint> HandleVBOPair;

	VDataFormat m_CoordinateFormat;
	VDataFormat m_ColorFormat;
	VDataFormat m_TexCoordFormat;
	VDataFormat m_IndexFormat;
//	VMeshDescription::ByteDataRef m_TriangleData;
//	VMeshDescription::ByteDataRef m_ColorData;
//	VMeshDescription::ByteDataRef m_TexCoordData;
//	VMeshDescription::ByteDataRef m_IndexData;

	vbool m_bColors;
	vbool m_bTexCoords;
	vbool m_bIndex;

	GLint m_PrimitiveType;
	
	//store all buffer id's. they can be equal
	GLuint m_VertexVBOID;  
	GLuint m_ColorVBOID;
	GLuint m_TexCoordVBOID;
	GLuint m_IndexVBOID;

	GLuint GetVertexBuffer(VMeshDescription::BufferHandle in_hHandle);

	static HandleVBOMap s_VBOMap;

};


//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------
 

#endif // V3D_VOPENGLVVBOMESH_H
