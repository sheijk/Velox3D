#include <v3d/Core/VObjectRegistry.h>
#include <v3d/VFS/IVFileSystem.h>
#include <V3dLib/Utils/VStreamReader.h>
#include <v3dLib/Graphics/Importer/VQ3BSPImporter.h>

#include <memory.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils{
//-----------------------------------------------------------------------------

using namespace v3d::graphics;

VQ3BSPImporter::VQ3BSPImporter()
{
	m_iNumVertices	= 0;
	m_iNumTextures	= 0;
	m_iNumLightmaps = 0;
	m_iNumFaces		= 0;
	m_iNumNodes		= 0;
	m_iNumLeafs		= 0;
	m_iNumLeafFaces = 0;
	m_iNumPlanes	= 0;
        
	m_pFaces		= 0;
	m_pVertices		= 0;
	m_pTextures		= 0;
	m_pNodes		= 0;
	m_pLeaf			= 0;
	m_pLeafFaces	= 0;
	m_pPlanes		= 0;
	m_pRawData		= 0;
}

VQ3BSPImporter::~VQ3BSPImporter()
{
	m_iNumVertices = 0;
	m_iNumTextures = 0;
	m_iNumLightmaps = 0;
	m_iNumFaces	 = 0;

	m_pFaces	 = 0;
	m_pVertices  = 0;
	m_pTextures	 = 0;
	m_pNodes	 = 0;
	m_pLeafFaces = 0;
	m_pPlanes	 = 0;
			
	DeleteRawData();
}

vbool VQ3BSPImporter::Create(VStringParam in_sFilename)
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
		DeleteRawData();
		return false;
	}

	BSPHeader* header = (BSPHeader*)m_pRawData;

	if(header->iVersion != BSPVERSIONS)
	{
		V3D_THROW(VException, "Wrong BSP versions type.");
		DeleteRawData();
		return false;
	}

	BSPLump* lumps = 0;
    
	lumps = (BSPLump*)(m_pRawData + sizeof(BSPHeader));

	// add all relevant information out of the mem

	m_iNumVertices = lumps[VERTICES].iLength / sizeof(BSPVertex);
	m_iNumFaces    = lumps[FACES].iLength / sizeof(BSPFace);
	m_iNumTextures = lumps[TEXTURES].iLength / sizeof(BSPTexture);
	m_iNumLightmaps= lumps[LIGHTMAPS].iLength / sizeof(BSPLightmap);
	m_iNumNodes	   = lumps[NODES].iLength / sizeof(BSPNode);
	m_iNumLeafs	   = lumps[LEAFS].iLength / sizeof(BSPLeaf);
	m_iNumLeafFaces= lumps[LEAFFACES].iLength / sizeof(vint);
	m_iNumPlanes   = lumps[PLANES].iLength /  sizeof(BSPPlane);

	m_pVertices    = (BSPVertex*)(m_pRawData + lumps[VERTICES].iOffset);
	m_pFaces	   = (BSPFace*)(m_pRawData + lumps[FACES].iOffset);
	m_pTextures	   = (BSPTexture*)(m_pRawData + lumps[TEXTURES].iOffset);
	m_pLightmaps   = (BSPLightmap*)(m_pRawData + lumps[LIGHTMAPS].iOffset);
	m_pNodes	   = (BSPNode*)(m_pRawData + lumps[NODES].iOffset);
	m_pLeaf		   = (BSPLeaf*)(m_pRawData + lumps[LEAFS].iOffset);
	m_pLeafFaces   = (vint*)(m_pRawData + lumps[LEAFFACES].iOffset);
	m_pPlanes	   = (BSPPlane*)(m_pRawData+ lumps[PLANES].iOffset);

	if(lumps[VISIBILITYDATA].iLength)
	{
		m_PVSData.iNumClusters = *(m_pRawData + lumps[VISIBILITYDATA].iOffset);
		m_PVSData.iClusterbytes= *(m_pRawData
			+ lumps[VISIBILITYDATA].iOffset
			+ sizeof(vint));

		m_PVSData.pCluster = 
			(m_pRawData
			+ lumps[VISIBILITYDATA].iOffset
			+ 2* sizeof(vint)
			);
        

	}

    

	//SwapAxis();
	return true;

}

void VQ3BSPImporter::DeleteRawData()
{
	if(m_pRawData)
		delete m_pRawData;
}

void VQ3BSPImporter::SwapAxis()
{
	float temp;

	// Swap axis because quake 3 uses z to up (hehe sheijk :)) )
	//TODO: planes 2

	for(int i =0; i < m_iNumVertices; i++)
	{
		temp = -m_pVertices[i].Vertex.y;
		m_pVertices[i].Vertex.y = m_pVertices[i].Vertex.z;
		m_pVertices[i].Vertex.z = temp;

		// we also need to negate the 2. of the uv coordinate tupel

		m_pVertices[i].TextureCoord.v = -m_pVertices[i].TextureCoord.v;
	}
}

vint VQ3BSPImporter::GetVertexCount()
{
	return m_iNumVertices;
}
vint VQ3BSPImporter::GetFaceCount()
{
	return m_iNumFaces;
}
vint VQ3BSPImporter::GetTextureCount()
{
	return m_iNumTextures;
}
vint VQ3BSPImporter::GetLightmapCount()
{
	return m_iNumLightmaps;
}

VQ3BSPImporter::BSPVertex* VQ3BSPImporter::GetVertexPointer()
{
	return m_pVertices;
}

VQ3BSPImporter::BSPFace* VQ3BSPImporter::GetFacePointer()
{
	return m_pFaces;
}

VQ3BSPImporter::BSPTexture* VQ3BSPImporter::GetTexturePointer()
{
	return m_pTextures;
}
VQ3BSPImporter::BSPLightmap* VQ3BSPImporter::GetLightmapPointer()
{
	return m_pLightmaps;
}

vint VQ3BSPImporter::GetNodeCount()
{
	return m_iNumNodes;
}
VQ3BSPImporter::BSPNode* VQ3BSPImporter::GetNodePointer()
{
	return m_pNodes;
}

vint VQ3BSPImporter::GetLeafCount()
{
	return m_iNumLeafs;
}

VQ3BSPImporter::BSPLeaf* VQ3BSPImporter::GetLeafPointer()
{
	return m_pLeaf;
}

vint VQ3BSPImporter::GetLeafFaceCount()
{
	return m_iNumLeafFaces;
}

vint* VQ3BSPImporter::GetLeafFacePointer()
{
	return m_pLeafFaces;
}

VQ3BSPImporter::BSPPlane* VQ3BSPImporter::GetPlanePointer()
{
	return m_pPlanes;
}

vint VQ3BSPImporter::GetPlaneCount()
{
	return m_iNumPlanes;
}

VQ3BSPImporter::BSPPVS* VQ3BSPImporter::GetPVSData()
{
	return &m_PVSData;
}
//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
