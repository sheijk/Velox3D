//-----------------------------------------------------------------------------
#ifndef V3D_QUAKE2BSPIMPORTER_H
#define V3D_QUAKE2BSPIMPORTER_H
//-----------------------------------------------------------------------------
#include <v3d/utils/Graphics/VPlane3f.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace utils{
namespace importer{
//-----------------------------------------------------------------------------

using v3d::utils::graphics::VPlane3f;
using v3d::utils::graphics::VVector3f;

#define BSPVERSION	38

#define MAX_LIGHTMAPS		4
#define MIP_LEVELS			4
#define MAX_MAP_TEXTURES	1024
#define	MAX_MAP_MODELS		1024
#define	MAX_MAP_BRUSHES		8192
#define	MAX_MAP_ENTITIES	2048
#define	MAX_MAP_ENTSTRING	0x40000
#define	MAX_MAP_TEXINFO		8192
#define	MAX_MAP_AREAS		256
#define	MAX_MAP_AREAPORTALS	1024
#define	MAX_MAP_PLANES		65536
#define	MAX_MAP_NODES		65536
#define	MAX_MAP_BRUSHSIDES	65536
#define	MAX_MAP_LEAFS		65536
#define	MAX_MAP_VERTS		65536
#define	MAX_MAP_FACES		65536
#define	MAX_MAP_LEAFFACES	65536
#define	MAX_MAP_LEAFBRUSHES 	65536
#define	MAX_MAP_PORTALS		65536
#define	MAX_MAP_EDGES		128000
#define	MAX_MAP_SURFEDGES	256000
#define	MAX_MAP_LIGHTING	0x200000
#define	MAX_MAP_VISIBILITY	0x100000

#define	LUMP_ENTITIES		0
#define	LUMP_PLANES		1
#define	LUMP_VERTICES		2
#define	LUMP_VISIBILITY		3
#define	LUMP_NODES		4
#define	LUMP_TEXINFO		5
#define	LUMP_FACES		6
#define	LUMP_LIGHTING		7
#define	LUMP_LEAVES		8
#define	LUMP_LEAFFACES		9
#define	LUMP_LEAFBRUSHES	10
#define	LUMP_EDGES		11
#define	LUMP_SURFEDGES		12
#define	LUMP_MODELS		13
#define	LUMP_BRUSHES		14
#define	LUMP_BRUSHSIDES		15
#define	LUMP_POP		16
#define	LUMP_AREAS		17
#define	LUMP_AREAPORTALS	18
#define	HEADER_LUMPS		19

#define		BOGUS		  3.4E38
#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))


/*
 * A bsp importer currently not loading textures
 * @author ins
 */

class VQuake2BspImporter
{
public:

	class Edge
	{
	public:
		vushort v[2];
	};
	
	class Plane
	{
	public:
		VPlane3f m_Plane;
		int m_iType;
	};

	class Face
	{
	public:
		vushort	m_iPlaneID;
		vshort	m_iSide;
		vint	m_iFirstEdge;
		vshort	m_iNumEdges;
		vshort	m_iTextureInfo;
		vbyte	m_pStyles[MAX_LIGHTMAPS];
		vint	m_iLightOffset;
	};

	class TextureInfo
	{
	public:

		vfloat32 m_pVectors[2][4];	//s/t;
		vint m_iFlags;
		vint m_iValue;
		vchar m_pTextureName[32];
		vint m_iNextTextureInfo;	//for animations
	};

	class Sky
	{
	public:
		vbyte*  m_pRaw[6];
		vint	m_pCacheOffsets[6];
		vint	m_iWidth;
		vint    m_iHeight;
	};

	class BrushSide
	{
	public:
		vushort m_iPlaneID;
		vshort m_TextureInfo;
	};

	class Brush
	{
	public:

		vint m_iFirstSide;
		vint miNumSides;
		vint m_iContents;
	};

	class Node
	{
	public:
		vint m_iPlaneID;
		vint m_pChildren[2];

		vshort m_pMin[3];		//for frustum culling
		vshort m_pMax[3];

		vushort	m_iFirstFace;
		vushort m_iNumFaces;
	};

	class Leaf
	{
	public:

		vint m_iContents;
		vshort m_iCluster;
		vshort m_iArea;
		vshort m_pMin[3];
		vshort m_pMax[3];

		vushort m_iFirstLeaf;
		vushort m_iNumLeafFaces;
		vushort m_iFirstLeafBrush;
		vushort m_iNumLeafBrushes;
	};

	class Miptex
	{
	public:
		vchar m_pName[32];
		vuint m_iWidth;
		vuint m_iHeight; //TODO check unsigned!!
		vuint m_pOffsets[MIP_LEVELS];
		vchar m_pAnimationName[32];
		vint m_iFlags;
		vint m_iContents;
		vint m_iValue;
	};

	class QBspTexture
	{
	public:
		Miptex* m_pMiptex;
		vint m_pCacheOffsets[4];
	};

	class PortalArea
	{
	public:
		vint m_iPortalID;
		vint m_iOtherPortal;
	};

	class Area
	{
	public:
		vint m_iNumAreaPortals;
		vint m_iFirstAreaPortal;
	};

	class Portal
	{
	public:
		vbyte m_bIsOpen;
	};

	class Visibility
	{
	public:
		vint m_iNumClusters;
		vint m_pBitOffset[8][2];
	};

	class VisibilityInfo
	{
	public:
		vbyte m_pVisClusters[(MAX_MAP_LEAFS+7)>>3];
		vbyte m_pVisAreas[MAX_MAP_AREAS];
	};


	class Model
	{
	public:
		vfloat32 m_pMin[3];
		vfloat32 m_pMax[3];
		vfloat32 m_pOrigin[3];
		vint m_iHeadNode;
		vint m_iFirstFace;
		vint m_iNumFaces;	
	};

	class ClipNode
	{
	public:
		vint m_iType;
		vfloat32 m_pNormal[3];
		vfloat32 m_fDistance;
		vint m_pChildren[2];
		vint m_iPad;
	};

	class Lump
	{
	public:
		vint m_iFileOffset;
		vint m_iFileLength;
	};

	class QBspHeader
	{
	public:
		vint m_iIdent;
		vint m_iVersion;
		Lump m_pLumps[HEADER_LUMPS];
	};

	class CacheVertex
	{
	public:

		vfloat32 m_pVertex[3];
		vint m_iTimeStamp;
	};

	class CacheEdge
	{
	public:

		vint m_iSourceEdgeIndex;
		vint m_iTimeStamp;
	};

	class CacheFace
	{
	public:

		vint m_iMinU;
		vint m_iMinV;
		vint m_iSizeU;
		vint m_iSizeV;
		vint m_iCacheOffset;
	};

	/*class lightmap_c : public texture_c
	{
	public:

		float mid_u, mid_v;

		lightmap_c();

		void load_lightmap(byte *data, int Width, int Height, float u, float v);

	};*/
		
	private:
		//void CreateChaceFaces(vint iIndex);
		//void CreateLightmaps(vbyte* pData);
		//bool CreateTexture(VStringParam sFilename);

		void GetFaceElements();
		void CreateIndexListBuffer();

	public:



	Model*          m_pModels;
	Plane*			m_pPlanes;
	Node*			m_pNodes;
	Leaf*			m_pLeaves;
	Brush*			m_pBrushes;
	BrushSide*	    m_pBrushSides;
	Area*			m_pAreas;
	PortalArea*		m_pAreaPortals;
	Portal*			m_pPortals;
	VVector3f*      m_pVertices;
	Edge* 			m_pEdges;
	Face*			m_pFaces;
	TextureInfo*	m_pTextureInfo;
	vword*			m_pTextureList;
	//texture		*textures;
	Visibility*		m_pVisibility;
	vword*			m_pBrushList;
	vword*			m_pFaceList;
	vint*			m_pEdgeList;
	vbyte*			m_pLightmapData;
	vchar*			m_pEntities;
	CacheVertex*	m_pCacheVertices;
	CacheFace*		m_pCacheFaces;
	CacheEdge*		m_pCacheEdges;					
	//lightmap		*lightmaps;

	ClipNode*		m_pClipNodes;
	Sky				m_Sky;
	vint			m_pModelObjectIndex[MAX_MAP_MODELS];
	vint			m_iNumModels, m_iNumPlanes, m_iNumNodes;
	int				m_iNumLeaves, m_iNumBrushes, m_iNumBrushSides;
	vint			m_iNumAreas, m_iNumPortalAreas, m_iNumFaces;
	vint			m_iNumEdges, m_iNumVertices, m_iNumTextureInfo;
	vint			m_iNumTextures, m_iNumPortals, m_iNumEntities;

	vbyte*			m_pRawData;
	vuint*			m_pIndexList; //sorted indices into vertexbuffer
	vuint			m_iNumFaceElements;

	vbool Create(VStringParam sFilename, VStringParam sTexturePath);
	void  Destroy(void);

	VQuake2BspImporter();
	
};
//-----------------------------------------------------------------------------
} // namespace importetr
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------
#endif V3D_QUAKE2BSPIMPORTER_H