#include <v3d/Core/VObjectRegistry.h>
#include <v3d/VFS/IVFileSystem.h>
#include <V3dLib/Utils/VStreamReader.h>
#include <v3dLib/Graphics/Importer/VQ3BspImporter.h>

#include <memory.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace utils{
//-----------------------------------------------------------------------------

using namespace v3d::graphics;


VQ3BspImporter::VQ3BspImporter()
{
	m_iNumVertices = 0;
	m_iNumTextures = 0;
	m_iNumLightmaps = 0;
	m_iNumFaces	 = 0;

	m_pFaces = 0;
	m_pVertices = 0;
	m_pTextures = 0;
	m_pRawData = 0;

}

VQ3BspImporter::~VQ3BspImporter()
{
	Delete();
}

vbool VQ3BspImporter::LoadQ3Level(VStringParam in_sFilename)
{
	// query vfs
	vfs::IVFileSystem& fileSys = *QueryObject<vfs::IVFileSystem>("vfs.fs");
	vfs::IVFileSystem::FileStreamPtr fileStream;

	fileStream = fileSys.OpenFile(in_sFilename, vfs::VReadAccess);

	utils::VStreamReader StreamReader(fileStream.Get());
    
	// alloc memory to hold complete set of level in memory
	m_pRawData = new vbyte[StreamReader.GetSizeOfBuffer()];

	memcpy(m_pRawData, (vbyte*)StreamReader.GetStreamBuffer(), StreamReader.GetSizeOfBuffer());

	if(m_pRawData == 0)
	{
		V3D_THROW(VException, "Bad mem copy.");
		Delete();
		return false;
	}

	BSPHeader* header = (BSPHeader*)m_pRawData;

	if(header->iVersion != BSPVERSIONS)
	{
		V3D_THROW(VException, "Wrong BSP versions type.");
		Delete();
		return false;
	}

	BSPLump* lumps = 0;
    
	lumps = (BSPLump*)(m_pRawData + sizeof(BSPHeader));

	// add all relevant information out of the mem

	m_iNumVertices = lumps[VERTICES].iLength / sizeof(BSPVertex);
	m_iNumFaces    = lumps[FACES].iLength / sizeof(BSPFace);
	m_iNumTextures = lumps[TEXTURES].iLength / sizeof(BSPTexture);
	m_iNumLightmaps= lumps[LIGHTMAPS].iLength / sizeof(BSPLightmap);

	m_pVertices    = (BSPVertex*)(m_pRawData + lumps[VERTICES].iOffset);
	m_pFaces	   = (BSPFace*)(m_pRawData + lumps[FACES].iOffset);
	m_pTextures	   = (BSPTexture*)(m_pRawData + lumps[TEXTURES].iOffset);
	m_pLightmaps   = (BSPLightmap*)(m_pRawData + lumps[LIGHTMAPS].iOffset);


	//SwapAxis();
	return true;

}

void VQ3BspImporter::Delete()
{
	if(m_pRawData)
		delete m_pRawData;
}

void VQ3BspImporter::SwapAxis()
{
	float temp;

	// Swap axis because quake 3 uses z to up (hehe sheijk :)) )


	for(int i =0; i < m_iNumVertices; i++)
	{
		temp = -m_pVertices[i].Vertex.y;
		m_pVertices[i].Vertex.y = m_pVertices[i].Vertex.z;
		m_pVertices[i].Vertex.z = temp;

		// we also need to negate the 2. of the uv coordinate tupel

		m_pVertices[i].TextureCoord.v = -m_pVertices[i].TextureCoord.v;
	}
}
//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
