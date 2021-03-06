/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VIMPORTEDFACEDESCRIPTION_2005_05_21_H
#define V3D_VIMPORTEDFACEDESCRIPTION_2005_05_21_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Resource/VResourceId.h>
#include <V3d/Graphics/VMeshDescription.h>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;

class VImportedMaterialDescription;
class VImportedBufferDescription;
/**
 * describes a face set with its corresponding indices
 */
class VImportedFaceDescription
{
public:
	explicit VImportedFaceDescription();
	
	VImportedFaceDescription(VStringParam in_sParentName,
		vuint nFaceId,
		vuint nFaceIndexStart,
		VImportedMaterialDescription* in_pMaterialDescription
		);

	virtual ~VImportedFaceDescription();

	vuint GetFaceCount();
	vuint GetFaceIndexStart();
	VImportedMaterialDescription* GetMaterial();
	VStringRetVal GetResourceName();
	resource::VResourceId CreateResource(
		VImportedBufferDescription* in_pBufferDescription);
	VStringRetVal GetParentResourceName();
	VImportedBufferDescription* GetBufferDescription();
	graphics::VMeshDescription* GetMeshDescription();


private:

	vuint m_nFaceId;
	vuint m_nFaceIndexStart;
	std::string m_sParentName;
	std::string m_sName;
	VImportedMaterialDescription* m_pMaterial;
	VImportedBufferDescription* m_pBufferDescription;
	graphics::VMeshDescription* m_pMeshDescription;
	//resource::VResourceId* m_pResourceId;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VIMPORTEDFACEDESCRIPTION_2005_05_21_H

