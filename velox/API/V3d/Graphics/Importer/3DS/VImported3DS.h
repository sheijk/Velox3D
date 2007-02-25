/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VIMPORTED3DS_04_08_23_H
#define V3D_VIMPORTED3DS_04_08_23_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Graphics/VModel.h>
#include <vector>
#include <list>
#include <map>
#include <v3d/Graphics.h>

#include <V3d/Graphics/Importer/Base/VImportedMaterialContainer.h>
#include <V3d/Graphics/Importer/Base/VImportedMaterialDescription.h>
#include <V3d/Graphics/Importer/Base/VImportedFaceContainer.h>

#include "lib3ds/file.h"
#include "lib3ds/node.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace utils{
//-----------------------------------------------------------------------------

/**
 * 3DS importer using lib3ds
 * @author: ins
 */

class VImportedBufferDescription;


class VImported3DS
{
public:

	VImported3DS();
	~VImported3DS();

	/**
	 * @note: returns true on success, false otherwise
	 */
	vbool CreateModel(
		graphics::IVDevice* in_pDevice,
		graphics::VModel* in_pModel,
		VStringParam in_sFilename);

	/**
	 * loads the model into the resource with included filename
	 */
	vbool CreateModel(
		graphics::VModel* in_pModel,
		VStringParam in_sFilename);

	vuint m_iNumFaces;
	vuint m_iNumVertices;
	vuint m_iNumMaterials;
	vuint m_nTexCoords;

private:

	struct ArrayBuffer
	{
		vfloat32* pVertexBuffer;
		vfloat32* pTextureCoordBuffer;
		vuint32* pIndexBuffer;
		vuint32 nIndexCount;
		vuint32 nVertexCount;
		vuint32 nTexelCount;

		ArrayBuffer()
		{
			pVertexBuffer = 0;
			pTextureCoordBuffer = 0;
			pIndexBuffer = 0;
			nIndexCount = 0;
			nVertexCount = 0;
			nTexelCount = 0;
		}
	};

	vbool LoadFile(VStringParam in_sFilename);

	/**
	 * load the model to the resource
	 */
	
	vbool LoadModel();
	vbool LoadNode(Lib3dsNode* in_pNode);
	bool LoadMesh();
	void CreateMeshResourceName(VStringParam in_sName);
	vbool CopyBuffers(Lib3dsMesh* in_pMesh, ArrayBuffer* in_pArrayBuffer);
	VStringRetVal CreateMeshPartName(VStringParam in_sMeshPartName);
	VStringRetVal GetMeshResourceName();
	void CreateMeshBufferResource(VStringParam in_sMeshname,
		VImportedBufferDescription* in_BufferInfo);
	
	/**
	 * looks for global materials
	 */
	vbool IsGlobalMaterial(std::string sName);
	std::string m_sGlobalMaterialIdentifier;
	
	//the libs file structure for loading
	Lib3dsFile* m_p3DSFile;
	std::string m_sMeshResourceName;

	VImportedFaceContainer m_FaceContainer;
	VImportedMaterialContainer m_MaterialContainer;
	typedef std::list<VImportedBufferDescription*> BufferDescriptionList;
	BufferDescriptionList m_BufferDescriptionList;

};
//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VIMPORTED3DS_04_08_23_H
