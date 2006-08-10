#include <V3d/Graphics/Importer/Base/VImportedBufferDescription.h>
#include <V3d/Graphics/VVertexFormat.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::graphics;

VImportedBufferDescription::VImportedBufferDescription(
	vuint nVertexCount,
	vuint nIndicesCount,
	vuint nTextureCoordCount1,
	vuint nTextureCoordCount2,
	vuint nNormalCount
	)
{
	this->nVertexCount = nVertexCount;
	this->nIndicesCount = nIndicesCount;
	this->nNormalCount = nNormalCount;
	this->nTextureCoordCount1 = nTextureCoordCount1;
	this->nTextureCoordCount2 = nTextureCoordCount2;

	pIndexBuffer = 0;
	pVertexBuffer = 0;
	pTexCoordBuffer1 = 0;
	pTexCoordBuffer2 = 0;
	pNormalBuffer = 0;

	pIndexBufferArray = 0;
	pVertexBufferArray = 0;
	pTextureCoordsBufferArray1 = 0;
	pTextureCoordsBufferArray2 = 0;
	pNormalBufferArray = 0;

	m_pVertexBufferFormat = 0;
	m_pNormalBufferFormat = 0;
	m_pTexCoordBufferFormat1 = 0;
	m_pTexCoordBufferFormat2 = 0;
	m_pIndexBufferFormat = 0;
}

VImportedBufferDescription::~VImportedBufferDescription()
{
	delete m_pIndexBufferFormat;
	delete m_pTexCoordBufferFormat1;
	delete m_pTexCoordBufferFormat2;
	delete m_pVertexBufferFormat;
	delete m_pNormalBufferFormat;
}

VImportedBufferDescription::BufferHandle
VImportedBufferDescription::GetVertexBuffer()
{
	if(pVertexBuffer)
		return pVertexBuffer;
	else
		V3D_THROW(VException, "vertex buffer is not valid");
}

VImportedBufferDescription::BufferHandle
VImportedBufferDescription::GetIndexBuffer()
{
	if(pIndexBuffer)
		return pIndexBuffer;
	else
		V3D_THROW(VException, "index buffer is not valid");
}

VImportedBufferDescription::BufferHandle
VImportedBufferDescription::GetTexCoordBuffer1()
{
	if(pTexCoordBuffer1)
		return pTexCoordBuffer1;
	else
		V3D_THROW(VException, "texcoord buffer 1 is not valid");
}

VImportedBufferDescription::BufferHandle
VImportedBufferDescription::GetTexCoordBuffer2()
{
	if(pTexCoordBuffer2)
		return pTexCoordBuffer2;
	else
		V3D_THROW(VException, "texcoord buffer 2 is not valid");
}

VImportedBufferDescription::BufferHandle
VImportedBufferDescription::GetNormalBuffer()
{
	if(pNormalBuffer)
		return pNormalBuffer;
	else
		V3D_THROW(VException, "normal buffer is not valid");
}

vuint VImportedBufferDescription::GetVertexCount()
{
	return nVertexCount;
}

vuint VImportedBufferDescription::GetIndicesCount()
{
	return nIndicesCount;
}

vuint VImportedBufferDescription::GetNormalCount()
{
	return nNormalCount;
}

vuint VImportedBufferDescription::GetTexCoordCount1()
{
	return nTextureCoordCount1;
}

vuint VImportedBufferDescription::GetTexCoordCount2()
{
	return nTextureCoordCount2;
}

void VImportedBufferDescription::SetIndexArray(vuint* indexArray)
{
	if(!indexArray)
		V3D_THROW(VException, "invalid index array");
	pIndexBufferArray = indexArray;
}

void VImportedBufferDescription::SetVertexArray(vfloat32* vertexArray)
{
	if(!vertexArray)
		V3D_THROW(VException, "invalid vertex array");
	pVertexBufferArray = vertexArray;
}

void VImportedBufferDescription::SetTexCoordArray1(vfloat32* texcoordArray)
{
	if(!texcoordArray)
		V3D_THROW(VException, "invalid texcood array");
	pTextureCoordsBufferArray1 = texcoordArray;
}

void VImportedBufferDescription::SetTexCoordArray2(vfloat32* texcoordArray)
{
	if(!texcoordArray)
		V3D_THROW(VException, "invalid texcoord array");
	pTextureCoordsBufferArray2 = texcoordArray; 
}

void VImportedBufferDescription::SetNormalArray(vfloat32* normalArray)
{
	if(!normalArray)
		V3D_THROW(VException, "invalid normal array");
	pNormalBufferArray = normalArray;
}

void VImportedBufferDescription::CreateBuffer()
{
	if(nVertexCount && pVertexBufferArray != 0)
	{
	
		m_pVertexBufferFormat = new VVertexFormat(
			VVertexFormat::Coordinates,
			nVertexCount,
			0);

		pVertexBuffer = new VVertexBuffer(
			pVertexBufferArray,
			nVertexCount * 3,
			*m_pVertexBufferFormat);
	}

	if(nIndicesCount && pIndexBufferArray != 0)
	{
		m_pIndexBufferFormat = new VVertexFormat(
			VVertexFormat::Indices,
			0,
			nIndicesCount
			);

		m_pIndexBufferFormat->SetIndexFormat(
			VDataFormat(
			0,
			nIndicesCount,
			0));

		pIndexBuffer = new VVertexBuffer(
			pIndexBufferArray,
			nIndicesCount,
			*m_pIndexBufferFormat);
	}

	if(nTextureCoordCount1 && pTextureCoordsBufferArray1 != 0)
	{
		m_pTexCoordBufferFormat1 = new VVertexFormat(
			VVertexFormat::TexCoords, 0, 0);
		
		m_pTexCoordBufferFormat1->SetTexCoordFormat(
			0,	VDataFormat(0, nTextureCoordCount1,	2));

		pTexCoordBuffer1 = new VVertexBuffer(
			pTextureCoordsBufferArray1,
			nTextureCoordCount1 * 2,
			*m_pTexCoordBufferFormat1);
	}

	if(nTextureCoordCount2 && pTextureCoordsBufferArray2 != 0)
	{
		m_pTexCoordBufferFormat2 = new VVertexFormat(
			VVertexFormat::TexCoords, 0, 0);

		m_pTexCoordBufferFormat2->SetTexCoordFormat(
			1,	VDataFormat(0, nTextureCoordCount2,	2));

		pTexCoordBuffer1 = new VVertexBuffer(
			pTextureCoordsBufferArray2,
			nTextureCoordCount2,
			*m_pTexCoordBufferFormat2);
	}

	//TODO: implmenet normal --ins
}

graphics::VVertexFormat* VImportedBufferDescription::GetVertexBufferFormat()
{
	return m_pVertexBufferFormat;
}

graphics::VVertexFormat* VImportedBufferDescription::GetIndexBufferFormat()
{
	return m_pIndexBufferFormat;
}

graphics::VVertexFormat* VImportedBufferDescription::GetTexCoordBufferFormat1()
{
	return m_pTexCoordBufferFormat1;
}

graphics::VVertexFormat* VImportedBufferDescription::GetTexCoordBufferFormat2()
{
	return m_pTexCoordBufferFormat2;
}

graphics::VVertexFormat* VImportedBufferDescription::GetNormalBufferFormat()
{
	return m_pNormalBufferFormat;
}

vuint* VImportedBufferDescription::GetIndexBufferArray()
{
	return pIndexBufferArray;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
