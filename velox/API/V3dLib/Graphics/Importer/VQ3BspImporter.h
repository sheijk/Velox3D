#ifndef V3D_VQ3BSPIMPORTER_05_17_2004_H
#define V3D_VQ3BSPIMPORTER_05_17_2004_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3dLib/Graphics/Geometry/VVector3f.h>
#include <v3dLib/Graphics/Geometry/VTexCoord2f.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils{
//-----------------------------------------------------------------------------
//wingdi spackt rum....
#undef PLANES

class VQ3BSPImporter
{
public:
	VQ3BSPImporter();
	~VQ3BSPImporter();


	/**
	 * Loads the given file from disk
	 */

	vbool Create(VStringParam in_sFilename);
	
	/**
	 * Swap axis for normal use 
	 */

	void SwapAxis();

	/**
	 * Getter's for loaded types
	 */

	vint GetVertexCount();
	vint GetFaceCount();
	vint GetTextureCount();
	vint GetLightmapCount();
	vint GetNodeCount();
	vint GetLeafCount();
	vint GetLeafFaceCount();
	vint GetPlaneCount();
	

	enum Settings
	{
		BSPVERSIONS = 46
	};

	enum Lumps
	{
		ENTITIES = 0,				// Stores player/object positions, etc...
		TEXTURES,					// Stores texture information
		PLANES,						// Stores the splitting planes
		NODES,						// Stores the BSP nodes
		LEAFS,						// Stores the leafs of the nodes
		LEAFFACES,					// Stores the leaf's indices into the faces
		LEAFBRUSHES,				// Stores the leaf's indices into the brushes
		MODELS,						// Stores the info of world models
		BRUSHES,					// Stores the brushes info (for collision)
		BRUSHSIDE,					// Stores the brush surfaces info
		VERTICES,					// Stores the level vertices
		MESHVERTICES,				// Stores the model vertices offsets
		SHADERS,					// Stores the shader files (blending, anims..)
		FACES,						// Stores the faces for the level
		LIGHTMAPS,					// Stores the lightmaps for the level
		LIGHTVOLUMES,				// Stores extra world lighting information
		VISIBILITYDATA,				// Stores PVS and cluster info (visibility)
		MAXLUMPS					// A constant to store the number of lumps
	};

	struct BSPVertex
	{
		graphics::VVector3f Vertex;
		graphics::VTexCoord2f TextureCoord;
		graphics::VTexCoord2f LightmapCoord;
		graphics::VVector3f Normal;
		vbyte ColorData[4];
	};

	struct BSPVector
	{
		int x,y,z;
	};

	struct BSPHeader
	{
		vchar StringIdentifier[4];
		int iVersion;
	};

	struct BSPLump
	{
		vint iOffset;
		vint iLength;
	};

	struct BSPFace
	{
		int iTextureID;
		int iEffect; // 1=polygon, 2=patch, 3=mesh, 4=billboard 
		int iType;
		
		int iVertexIndexStart;
		int iNumVertices;
		int iMeshIndexStart;
		int iNumMeshVertices;

		int iLightmapID;
		int LightmapSize[2];
		int LightmapCorner[2];

		graphics::VVector3f LightmapOrigin;
		graphics::VVector3f Normal;
		graphics::VVector3f LightmapVectors[2]; //the u v unit vectors
		int BezierSize[2];
	};
	
	struct BSPTexture
	{
		vchar sTextureName[64];
		int iFlags;
		int iContents;

	};

	struct BSPLightmap
	{
		vbyte LightmapData[49152]; //128*128*3
	};

	struct BSPNode
	{
		int iPLane;
		int iFront;
		int iBack;
        BSPVector min;
		BSPVector max;
	};

	struct BSPLeaf
	{
		vint iCluster;
		vint iArea;
		BSPVector min;
		BSPVector max;
		vint iLeafFace;
		vint iNumLeafFaces;
		vint iLeafBrush;
		vint iNumLeafBrushes;
	};

	struct BSPPlane
	{
		graphics::VVector3f Normal;
		vfloat32 fDistance;
	};

	struct BSPPVS
	{
		vint	iNumClusters;
		int		iClusterbytes;
		vbyte*	pCluster;
	};


	BSPVertex*		GetVertexPointer();
	BSPFace*		GetFacePointer();
	BSPTexture*		GetTexturePointer();
	BSPLightmap*	GetLightmapPointer();
	BSPNode*		GetNodePointer();
	BSPLeaf*		GetLeafPointer();
	vint*			GetLeafFacePointer();
	BSPPlane*		GetPlanePointer();
	BSPPVS*			GetPVSData();

private:

	/* Delete our alloced mem */
	void DeleteRawData();



	vint m_iNumVertices;
    vint m_iNumFaces;
	vint m_iNumTextures;
	vint m_iNumLightmaps;
	vint m_iNumNodes;
	vint m_iNumLeafs;
	vint m_iNumLeafFaces;
	vint m_iNumPlanes;
    
	
	BSPFace*     m_pFaces;
	BSPVertex*   m_pVertices;
	BSPTexture*  m_pTextures;
	BSPLightmap* m_pLightmaps;
	BSPNode*	 m_pNodes;
	BSPLeaf*	 m_pLeaf;
	BSPPlane*	 m_pPlanes;
	vint*		 m_pLeafFaces;
	BSPPVS		 m_PVSData;

	vbyte*		 m_pRawData;

};
//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VQ3BSPIMPORTER_05_17_2004_H
