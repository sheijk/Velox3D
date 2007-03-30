/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VBSPRENDERER_21_04_04_H
#define V3D_VBSPRENDERER_21_04_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <v3dLib/Graphics.h>
#include <v3dLib/Utils/VStreamReader.h>
#include <v3dLib/Graphics/Importer/VQ3BspImporter.h>
#include <V3d/Math.h>
#include <list>
#include <vector>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
//-----------------------------------------------------------------------------
class VBSPRenderer
{
public:
	
	VBSPRenderer(IVDevice* in_pDevice, IVCamera* in_pCamera);
	~VBSPRenderer();

	void Render();
		
	/**
	 * Loads the map by given filename
	 */
	void Create(VStringParam in_sName);

	/**
	 * Call this to free the used resources
	 */
	void Delete();

private:

	typedef VVector<vfloat32, 3> Vector;

	//no copying for this class
	VBSPRenderer(const VBSPRenderer&);
	//no assigment
	VBSPRenderer& operator=(const VBSPRenderer);

	void BuildMesh();
	
	void CreateVertexBuffer();
	void CreateTextures();

	/**
	 * creates for each vertex in the vertexbuffer the indexset
	 * to render a face
	 */
    void CreateLightmapCoords();
	
	void AddTextureEffect(VStringParam in_sTextureName);
	void AddLightmapEffect();


	void CreateEmptyEffect(VEffectDescription& in_rEffect);


	/**
	 * rendering
	 */

	/**
	 * takes in a vector as an position and determines visible face
	 * @return: face id number
	 */
	vint FindLeaf(Vector in_Pos);

	/**
	 * checks cluster for visiblity.
	 * @param: returns true on visible false otherwise
	 */
	vbool IsClusterVisible(vint in_VisCluster, vint in_TestCluster);
	
	std::vector<VEffectDescription*> m_TexEffectList;
	std::vector<VEffectDescription*> m_LightEffectList;
	std::vector<std::string>		 m_TextureNameList;
	std::list<IVDevice::MeshHandle>  m_MeshList;

	IVDevice::MeshHandle* m_MeshTextureTable;
	IVDevice::MeshHandle* m_MeshLightTable;
	int m_Bla;


	
	
	
	std::list<IVDevice::BufferHandle> m_BufferHandleList;

		
	utils::VQ3BSPImporter m_Level;

	// rendering members
	IVDevice* m_pDevice;
	
	VResizeableGeometryData<VTexturedVertex> m_GeometryData;
	
	vfloat32*  m_pLightmapCoords;
	vfloat32*  m_pLightmapCoordsSorted;
	vuint32    m_iNumSortedLightmapElements;

	IVCamera* m_pCamera;
};
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBSPRENDERER_21_04_04_H

