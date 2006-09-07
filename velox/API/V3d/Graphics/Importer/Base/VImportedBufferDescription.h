/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//TODO: add file creation date to file guard
#ifndef V3D_VIMPORTEDBUFFERDESCRIPTION_2005_05_15_H
#define V3D_VIMPORTEDBUFFERDESCRIPTION_2005_05_15_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VVertexBuffer.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * common imported buffer type
 */
class VImportedBufferDescription
{
public:

	typedef graphics::VVertexBuffer* BufferHandle;

	VImportedBufferDescription(
		vuint nVertexCount,
		vuint nIndicesCount,
		vuint nTextureCoordCount1 = 0,
		vuint nTextureCoordCount2 = 0,
		vuint nNormalCount = 0
		);

	virtual ~VImportedBufferDescription();
	
	void CreateBuffer();

	BufferHandle GetVertexBuffer();
	BufferHandle GetIndexBuffer();
	BufferHandle GetTexCoordBuffer1();
	BufferHandle GetTexCoordBuffer2();
	BufferHandle GetNormalBuffer();
	
	graphics::VVertexFormat* GetVertexBufferFormat();
	graphics::VVertexFormat* GetNormalBufferFormat();
	graphics::VVertexFormat* GetIndexBufferFormat();
	graphics::VVertexFormat* GetTexCoordBufferFormat1();
	graphics::VVertexFormat* GetTexCoordBufferFormat2();


	vuint GetVertexCount();
	vuint GetIndicesCount();
	vuint GetTexCoordCount1();
	vuint GetTexCoordCount2();
	vuint GetNormalCount();


	void SetVertexArray(vfloat32* vertexArray);
	void SetIndexArray(vuint* indexArray);
	void SetNormalArray(vfloat32* normalArray);
	void SetTexCoordArray1(vfloat32* texcoordArray);
	void SetTexCoordArray2(vfloat32* texCoordArray);

	vuint* GetIndexBufferArray();

private:

	vuint nVertexCount;
	vuint nIndicesCount;
	vuint nTextureCoordCount1;
	vuint nTextureCoordCount2;
	vuint nNormalCount;
    		
	vuint* pIndexBufferArray;
	vfloat32* pVertexBufferArray;
	vfloat32* pTextureCoordsBufferArray1;
	vfloat32* pTextureCoordsBufferArray2;
	vfloat32* pNormalBufferArray;

	BufferHandle pVertexBuffer;
	BufferHandle pIndexBuffer;
	BufferHandle pNormalBuffer;
	BufferHandle pTexCoordBuffer1;
	BufferHandle pTexCoordBuffer2;

	graphics::VVertexFormat* m_pVertexBufferFormat;
	graphics::VVertexFormat* m_pIndexBufferFormat;
	graphics::VVertexFormat* m_pNormalBufferFormat;
	graphics::VVertexFormat* m_pTexCoordBufferFormat1;
	graphics::VVertexFormat* m_pTexCoordBufferFormat2;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VImportedBufferDescription_2005_05_15_H

