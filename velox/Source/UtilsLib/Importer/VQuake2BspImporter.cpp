#include "VQuake2BspImporter.h"
#include "VStreamReader.h"
#include <v3d/VFS/IVFileSystem.h>
#include <v3d/Core/VObjectRegistry.h>
#include <memory.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d{
namespace util{
namespace importer{
//-----------------------------------------------------------------------------

VQuake2BspImporter::VQuake2BspImporter()
{
	m_pModels		    = NULL;
	m_pPlanes			= NULL;
	m_pNodes			= NULL;
	m_pLeaves			= NULL;
	m_pBrushes			= NULL;
	m_pBrushSides		= NULL;
	m_pAreas			= NULL;
	m_pAreaPortals	    = NULL;
	m_pPortals			= NULL;
	m_pVertices		    = NULL;
	m_pEdges			= NULL;
	m_pFaces			= NULL;
	m_pTextureInfo	    = NULL;
	m_pTextureList	    = NULL;
	
	m_pVisibility	    = NULL;
	m_pBrushList		= NULL;
	m_pFaceList		    = NULL;
	m_pEdgeList	    	= NULL;
	//m_pLightmaps		= NULL;
	m_pEntities 		= NULL;
	m_pCacheVertices	= NULL;
	m_pCacheEdges		= NULL;
	m_pCacheFaces		= NULL;
	m_pClipNodes		= NULL;
	m_pRawData			= NULL;
	m_pIndexList        = NULL;
	
	m_iNumModels   = m_iNumPlanes      = m_iNumNodes        =
	m_iNumLeaves   = m_iNumBrushes     = m_iNumBrushSides   =
	m_iNumAreas    = m_iNumPortalAreas = m_iNumFaces        =
	m_iNumEdges    = m_iNumVertices    = m_iNumTextureInfo  =
	m_iNumTextures = m_iNumPortals     = m_iNumEntities     =
	m_iNumFaceElements                 = 0;
};
//-----------------------------------------------------------------------------

vbool VQuake2BspImporter::Create(VStringParam sFilename, VStringParam sTexturePath)
{
	QBspHeader*	    header;
	Lump*			lump;

	vint			iSize;

	// query vfs
	vfs::IVFileSystem& fileSys = *QueryObject<vfs::IVFileSystem>("vfs.fs");

	// open file
	vfs::IVFileSystem::FileStreamPtr fileStream = 
		fileSys.OpenFile(sFilename, vfs::VReadAccess);

	VStreamReader StreamReader(fileStream.Get());


	iSize = StreamReader.GetSizeOfBuffer();
	m_pRawData = new vbyte[iSize];

	memcpy(m_pRawData, (vbyte*)StreamReader.GetStreamBuffer(), sizeof(vbyte)* iSize);

	header	= (QBspHeader*)m_pRawData;

	if(header->m_iVersion != BSPVERSION)
	{
		Destroy();
		return false;
	}
	
	//create all neccassary pointers

	lump			= &header->m_pLumps[LUMP_VERTICES];
	m_pVertices		= (VVertex3f*)(m_pRawData + lump->m_iFileOffset);
	m_iNumVertices	= lump->m_iFileLength / sizeof(VVertex3f);

	lump			= &header->m_pLumps[LUMP_EDGES];
	m_pEdges		= (Edge*)(m_pRawData + lump->m_iFileOffset);
	m_iNumEdges		= lump->m_iFileLength / sizeof(Edge);

	lump			= &header->m_pLumps[LUMP_FACES];
	m_pFaces		= (Face*)(m_pRawData + lump->m_iFileOffset);
	m_iNumFaces		= lump->m_iFileLength / sizeof(Face);

	lump			= &header->m_pLumps[LUMP_MODELS];
	m_pModels		= (Model*)(m_pRawData + lump->m_iFileOffset);
	m_iNumModels	= lump->m_iFileLength / sizeof(Model);

	lump			= &header->m_pLumps[LUMP_PLANES];
	m_pPlanes		= (Plane*)(m_pRawData + lump->m_iFileOffset);
	m_iNumPlanes	= lump->m_iFileLength / sizeof(Plane);

	lump			= &header->m_pLumps[LUMP_NODES];
	m_pNodes		= (Node*)(m_pRawData + lump->m_iFileOffset);
	m_iNumNodes		= lump->m_iFileLength / sizeof(Node);

	lump			= &header->m_pLumps[LUMP_LEAVES];
	m_pLeaves		= (Leaf*)(m_pRawData + lump->m_iFileOffset);
	m_iNumLeaves	= lump->m_iFileLength / sizeof(Leaf);

	lump			= &header->m_pLumps[LUMP_BRUSHES];
	m_pBrushes		= (Brush*)(m_pRawData + lump->m_iFileOffset);
	m_iNumBrushes	= lump->m_iFileLength / sizeof(Brush);

	lump			= &header->m_pLumps[LUMP_BRUSHSIDES];
	m_pBrushSides	= (BrushSide*)(m_pRawData + lump->m_iFileOffset);
	m_iNumBrushSides= lump->m_iFileLength / sizeof(BrushSide);

	lump			= &header->m_pLumps[LUMP_AREAS];
	m_pAreas		= (Area*)(m_pRawData + lump->m_iFileOffset);
	m_iNumAreas		= lump->m_iFileLength / sizeof(Area);

	lump			= &header->m_pLumps[LUMP_AREAPORTALS];
	m_pAreaPortals	= (PortalArea*)(m_pRawData + lump->m_iFileOffset);
	m_iNumPortalAreas= lump->m_iFileLength / sizeof(PortalArea);

	
	lump			= &header->m_pLumps[LUMP_VISIBILITY];
	m_pVisibility	= (Visibility*)(m_pRawData + lump->m_iFileOffset);

	lump			= &header->m_pLumps[LUMP_LEAFFACES];
	m_pFaceList		= (vword*)(m_pRawData + lump->m_iFileOffset);

	lump			= &header->m_pLumps[LUMP_LEAFBRUSHES];
	m_pBrushList	= (vword*)(m_pRawData + lump->m_iFileOffset);

	lump			= &header->m_pLumps[LUMP_SURFEDGES];
	m_pEdgeList		= (vint*)(m_pRawData + lump->m_iFileOffset);

	
	lump			= &header->m_pLumps[LUMP_TEXINFO];
	m_pTextureInfo	= (TextureInfo*)(m_pRawData + lump->m_iFileOffset);
	m_iNumTextureInfo= lump->m_iFileLength / sizeof(TextureInfo);

	m_pTextureList	= new vword[m_iNumTextureInfo];
	if(!m_pTextureList)
	{
		Destroy();
		return false;
	}

	lump			= &header->m_pLumps[LUMP_LIGHTING];
	//lightmap_data	= (byte*)(m_pRawData + lump->m_iFileOffset);

	lump			= &header->m_pLumps[LUMP_ENTITIES];
	//MakeEntities()

 	for (vint i = 0; i < m_iNumPortalAreas; i++)
	{
		if(m_pAreaPortals[i].m_iPortalID > m_iNumPortals)
		m_iNumPortals = m_pAreaPortals[i].m_iPortalID;
	}
	
	//Num_portals++; //what we do here??

	m_pPortals = new Portal[m_iNumPortals];
	if(!m_pPortals)
	{
		Destroy();
		return false;
	}

	for(vint i = 0; i < m_iNumPortals; i++)
		m_pPortals[i].m_bIsOpen = 0;

	m_pCacheVertices = new CacheVertex[m_iNumVertices];
	if(!m_pCacheVertices)
	{
		Destroy();
		return false;
	}

	for(vint i = 0; i < m_iNumVertices; i++)
		m_pCacheVertices[i].m_iTimeStamp = -1;

	m_pCacheEdges = new CacheEdge[m_iNumEdges];
	if(!m_pCacheEdges)
	{
		Destroy();
		return false;
	}

	for(vint i = 0; i < m_iNumEdges; i++)
		m_pCacheEdges[i].m_iTimeStamp = -1;

	m_pCacheFaces = new CacheFace[m_iNumFaces];
	if(!m_pCacheFaces)
	{
		Destroy();
		return false;
	}

	//for(i = 0; i < Num_faces; i++)
	//	make_cachefaces(i);

	//lightmaps = new lightmap_c[Num_faces];

	//load_textures(texpath);
	//load_lightmaps(lightmap_data);
	//LoadSky();
	//MakeClipNodes();

	GetFaceElements();
	CreateIndexListBuffer();
	
	return true;
}
//-----------------------------------------------------------------------------

void VQuake2BspImporter::Destroy(void)
{
	vint i;

	if (m_pClipNodes)
	{
		delete[] m_pClipNodes;
		m_pClipNodes = NULL;
	}
	
	for(i=0; i<6; i++)
		delete[] m_Sky.m_pRaw[i];
		
	//if(m_pTextures)
	//	delete [] textures;
		
	if (m_pTextureList)
		delete [] m_pTextureList;

	if (m_pEntities)
		delete [] m_pEntities;

	if (m_pCacheFaces)
		delete [] m_pCacheFaces;

	if (m_pCacheEdges)
		delete [] m_pCacheEdges;

	if (m_pCacheVertices)
		delete [] m_pCacheVertices;

	if (m_pPortals)
		delete [] m_pPortals;
	
	//if (lightmaps)
	//	delete [] lightmaps;

// Free m_pRawData stuff
	if (m_pRawData)
		delete [] m_pRawData;
		

}

/*void VQuake2BspImporter::make_cachefaces(int idx)
{
	face_c			*face;
	plane_c			*plane;
	texinfo_c		*texinfo;
	edge_c			*edge;
	vertex_c		*vertex;
	cache_face_c	*info;
	float			u,v;
	float			min_u, min_v;
	float			max_u, max_v;
	int				i,j,temp1,temp2;
	
	face	= &faces[idx];
	info	= &cache_faces[idx];
	plane	= &planes[face->plane_num];
	texinfo	= &texture_info[face->texinfo];

	min_u = min_v = (float)BOGUS;
	max_u = max_v = -(float)BOGUS;

	for(j = 0; j < face->num_edges; j++)
	{
		i = face->first_edge+j;
		i = edge_list[i];
		
		if (i < 0) i=-i;
		
		edge=&edges[i];

		// first vertex

		vertex = &vertices[edge->v[0]];
		
		
		u = Vec_DotProduct(vertex->Points,texinfo->vecs[0]) + texinfo->vecs[0][3];	//add offset
		v = Vec_DotProduct(vertex->Points,texinfo->vecs[1]) + texinfo->vecs[1][3];	//add offset
			
		
		min_u=min(u,min_u);
		min_v=min(v,min_v);
		max_u=max(u,max_u);
		max_v=max(v,max_v);

		// second vertex

		vertex = &vertices[edge->v[1]];
		
		u =Vec_DotProduct(vertex->Points,texinfo->vecs[0]) + texinfo->vecs[0][3];	//add offset
		v =Vec_DotProduct(vertex->Points,texinfo->vecs[1]) + texinfo->vecs[1][3];	//add offset

		min_u=min(u,min_u);
		min_v=min(v,min_v);
		max_u=max(u,max_u);
		max_v=max(v,max_v);
		
	}

	// compute u extents
	temp1=(int)floor(min_u/16.0f);
	temp2=(int)ceil(max_u/16.0f);

	info->min_u  = temp1<<4;
	info->size_u = (temp2-temp1)<<4;

	// compute v extents
	temp1=(int)floor(min_v/16.0f);
	temp2=(int)ceil(max_v/16.0f);

	info->min_v	 = temp1<<4;
	info->size_v = (temp2-temp1)<<4;


	info->cache_offset = 0;

	if (!texinfo->flags)
	{
		if (info->size_u>240)
			info->size_u=240;
		if (info->size_v>240)
			info->size_v=240;
	}

}

bool VQuake2BspImporter::load_textures(char *pathname)
{

	bool b_exists = false;
	char name[64];
	tga_c *temp_tga = NULL;
	texture_c *temp_textures = NULL;

	if(!(temp_tga =  new tga_c[Num_texinfo]))
		return false;

	if(!(temp_textures =  new texture_c[Num_texinfo]))
		return false;
	

	for (long i = 0; i < Num_texinfo; i++)
	{
		for (long j = 0; j < Num_textures; j++)
		{
			if(!stricmp(texture_info[i].texture_name, temp_textures[j].name))
			{
				b_exists = true;
				break;
			}
		}

		if(!b_exists)
		{
			strcpy(name, pathname);
			strcat(name, texture_info[i].texture_name);
			strcat(name, ".tga");					//FIXME:: only tga support!!!

			temp_tga[Num_textures].Load(name);
			temp_textures[Num_textures].create(&temp_tga[Num_textures]);
			strcpy(temp_textures[Num_textures].name, texture_info[i].texture_name);
			Num_textures++;
		}
		
		b_exists = false;
	}
		
	textures = temp_textures;
		
	for (i = 0; i < Num_faces; i++)
		for (long j = 0; j < Num_textures; j++)
			if(!stricmp(texture_info[faces[i].texinfo].texture_name, textures[j].name))
			{
				texture_list[i] = (unsigned int)j;
				break;
			}
	
			return true;
}

VQuake2BspImporter::lightmap_c::lightmap_c(void)
{
	width = height = 0;
	mid_u = mid_v = 0;
}


void VQuake2BspImporter::lightmap_c::load_lightmap(byte *data, int Width, int Height, float u, float v)
{
	width	= Width;
	height	= Height;

	mid_u	= u;
	mid_v   = v;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);	
	
}

void VQuake2BspImporter::load_lightmaps(byte *data)
{

	float u,v;
	float max_u,max_v;
	float min_u,min_v;
	int vertex;
	int i,j;

	texinfo_c	*texinfo;

	for(i = 0; i< Num_faces; i++)
	{
		texinfo = &texture_info[faces[i].texinfo];

		max_u = max_v = (float)-BOGUS;
		min_u = min_v = (float)BOGUS;
		
		for (j = faces[i].first_edge; j < faces[i].first_edge + faces[i].num_edges; j++)
		{
			if(edge_list[j] < 0)
				vertex = edges[abs(edge_list[j])].v[1];
			else
				vertex = edges[abs(edge_list[j])].v[0];

			u = Vec_DotProduct(vertices[vertex].Points,texinfo->vecs[0]) + texinfo->vecs[0][3];	//add offset
			v = Vec_DotProduct(vertices[vertex].Points,texinfo->vecs[1]) + texinfo->vecs[1][3];	//add offset
		

			min_u=min(u,min_u);
			min_v=min(v,min_v);
			max_u=max(u,max_u);
			max_v=max(v,max_v);
			
		}

		lightmaps[i].load_lightmap(&data[faces[i].light_offset], (unsigned long)ceil(max_u/16.0f) - (unsigned long)floor(min_u/16.0f) +1,
			(unsigned long)ceil(max_v/16.0f) - (unsigned long)floor(min_v/16.0f) +1, (min_u + max_u)/2.0f, (min_v + max_v)/2.0f);
	}

}*/
//-----------------------------------------------------------------------------

void VQuake2BspImporter::GetFaceElements()
{
	m_iNumFaceElements = 0;

	for (vint i = 0; i < m_iNumFaces; i++)
	{
		m_iNumFaceElements += m_pFaces[i].m_iNumEdges;
	}
}
//-----------------------------------------------------------------------------

void VQuake2BspImporter::CreateIndexListBuffer()
{
	m_pIndexList = new vuint[m_iNumFaceElements];
	vuint iCount = 0;
	
	for (vint i = 0; i < m_iNumFaces; i++)
	{
		for(vint y = m_pFaces[i].m_iFirstEdge;
			y < m_pFaces[i].m_iFirstEdge + m_pFaces[i].m_iNumEdges;
			y++)
		{
			if(m_pEdgeList[y] < 0)
				m_pIndexList[iCount] = m_pEdges[abs(m_pEdgeList[y])].v[1];			
			else
				m_pIndexList[iCount] = m_pEdges[abs(m_pEdgeList[y])].v[0];			

			iCount++;
		}

	}
}

//-----------------------------------------------------------------------------
} // namespace importetr
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------
	