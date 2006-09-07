/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VIMPORTEDMATERIALCONTAINER_2005_05_20_H
#define V3D_VIMPORTEDMATERIALCONTAINER_2005_05_20_H
//-----------------------------------------------------------------------------
#include <V3d/Graphics/Importer/Base/VImportedMaterialDescription.h>
#include <V3d/Core/VCoreLib.h>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;


/**
 * simple container to handle materials and
 * name quries
 * @note: takes ownership of the material and
 * deletes all materials on desctructor call
 */
class VImportedMaterialContainer
{
public:
	VImportedMaterialContainer();
	virtual ~VImportedMaterialContainer();

	void Add(VImportedMaterialDescription* in_pMaterial);
	void Remove(VImportedMaterialDescription* in_pMaterial);
	
	/*
	 * returns true if material with given name was found in the container
	 */
	vbool FindMaterialByName(VStringParam in_sName);

	/*
	 * returns the material with given name
	 * @return: returns pointer to material if found, else 0
	 */
	VImportedMaterialDescription* GetMaterialByName(VStringParam in_sName);
	
	/*
	 * build all materials and creates resources
	 */
	void CreateResources();

private:

	void CreateDefaultMaterial();

	typedef std::list<VImportedMaterialDescription*> MaterialList;
	MaterialList m_MaterialList;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VIMPORTEDMATERIALCONTAINER_2005_05_20_H

