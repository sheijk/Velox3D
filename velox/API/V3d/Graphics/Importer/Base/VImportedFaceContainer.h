/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VIMPORTEDFACECONTAINER_2005_05_21_H
#define V3D_VIMPORTEDFACECONTAINER_2005_05_21_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Graphics/VModel.h>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;
class VImportedFaceDescription;
class VImportedBufferDescription;

/**
 * Container for faces
 * @note: takes ownership of the faces and
 * deletes all on desctructor call
 */
class VImportedFaceContainer
{
public:
	VImportedFaceContainer();
	~VImportedFaceContainer();

	void Add(VImportedFaceDescription* in_pFace);
	void Remove(VImportedFaceDescription* in_pFace);

	//returns the number of faces stored in here
	vuint GetFaceCount();
	VImportedFaceDescription* GetElemAt(vuint index);

	//calls all stored faces to to be created
	void CreateFaceResources(VImportedBufferDescription* in_pBufferDescription);

	void CreateMeshes(
		graphics::IVDevice* in_pDevice,
		graphics::VModel* in_pModel
		);

	void V3D_DEPRECATED CreateMeshes(graphics::VModel* in_pModel);

	/**
	 * creates a optimized mesh for rendering by taking and combining
	 * equal materials and constructing one mesh description
	 */
	void CreateOptimizedMeshes(graphics::VModel* in_pModel, VStringParam in_strResource);

private:
	
	typedef std::list<std::string> MaterialLoadedList;
	vbool IsInMaterialLoadedList(VStringParam in_sName);

	std::vector<VImportedFaceDescription*> m_FaceList;
	MaterialLoadedList m_MaterialLoadedList;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VIMPORTEDFACECONTAINER_2005_05_21_H

