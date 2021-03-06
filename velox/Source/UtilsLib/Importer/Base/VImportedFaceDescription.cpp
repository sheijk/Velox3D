/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/Importer/Base/VImportedFaceDescription.h>
#include <V3d/Graphics/Importer/Base/VImportedBufferDescription.h>
#include <V3d/Graphics/Importer/Base/VImportedMaterialDescription.h>
#include <V3d/Graphics/Importer/VImporterException.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics.h>
#include <V3d/Graphics.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::graphics;

VImportedFaceDescription::VImportedFaceDescription()
{
	m_nFaceIndexStart = 0;
	m_nFaceId = 0;
	m_sParentName = "none";
	m_sName = m_sParentName;
	m_pMaterial = 0;
	m_pBufferDescription = 0;
}

VImportedFaceDescription::VImportedFaceDescription(
	VStringParam in_sParentName,
	vuint nFaceId = 0,
	vuint nFaceIndexStart = 0,
	VImportedMaterialDescription* in_pMaterialDescription = 0
	)
{
	m_nFaceId = nFaceId;
	m_nFaceIndexStart = nFaceIndexStart;
	m_sParentName = in_sParentName;
	m_pMaterial = in_pMaterialDescription;
	m_sName = m_sParentName;
	m_pBufferDescription = 0;
}


VImportedFaceDescription::~VImportedFaceDescription()
{
}

vuint VImportedFaceDescription::GetFaceCount()
{
	return m_nFaceId;
}

vuint VImportedFaceDescription::GetFaceIndexStart()
{
	return m_nFaceIndexStart;
}

VImportedMaterialDescription* VImportedFaceDescription::GetMaterial()
{
	return m_pMaterial;
}

resource::VResourceId VImportedFaceDescription::CreateResource(
		VImportedBufferDescription* in_pBufferDescription)
{
	if( m_pBufferDescription )
	{
	  return 0;
	}
	else
	{

	  m_pBufferDescription = in_pBufferDescription;

	  resource::VResourceManagerPtr pResourceManager;
	  std::string sFaceName = m_sParentName;
	  std::string sIndices = m_sParentName;
	  std::string sTexCoords = m_sParentName;
  		
	  //create a unique resource name by it's id
	  m_sName.append("/faceSet_");
	  std::stringstream ss;
	  ss << m_nFaceId;
	  m_sName.append(ss.str());

	  sIndices.append("/indices");
	  sTexCoords.append("/texcoords");
  	
	  //resource::VResourceId face =
	  //	pResourceManager->CreateResource(m_sName.c_str());

	  m_pMeshDescription = new VMeshDescription();

	  m_pMeshDescription->SetGeometryType(VMeshDescription::Triangles);
	  m_pMeshDescription->SetCoordinateResource(m_sParentName.c_str());
	  m_pMeshDescription->SetCoordinateFormat(
		  in_pBufferDescription->GetVertexBufferFormat()->GetCoordinateFormat());
  	
	  m_pMeshDescription->SetIndexResource(sIndices.c_str());
	  m_pMeshDescription->SetIndexFormat(VDataFormat(m_nFaceIndexStart, 3, 0));
  	
	  if(in_pBufferDescription->GetTexCoordCount1())
	  {
		  m_pMeshDescription->SetTexCoordResource(0, sTexCoords.c_str());
		  m_pMeshDescription->SetTexCoordFormat(0,
		  in_pBufferDescription->GetTexCoordBufferFormat1()->GetTexCoordFormat(0));
	  }

	  //TODO: insert 2. texcoodrs

	  //face->AddData(m_pMeshDescription);
  	
	  //return face;
	  return 0;
	}
}

VStringRetVal VImportedFaceDescription::GetResourceName()
{
	return m_sName.c_str();
}

VStringRetVal VImportedFaceDescription::GetParentResourceName()
{
	return m_sParentName.c_str();
}

VImportedBufferDescription* VImportedFaceDescription::GetBufferDescription()
{
	if(m_pBufferDescription)
		return m_pBufferDescription;
	else
		V3D_THROW(graphics::VImporterException,
		"requested buffer is not valid. This seems to be an invalid model.");
}

graphics::VMeshDescription* VImportedFaceDescription::GetMeshDescription()
{
	if(m_pBufferDescription)
        return m_pMeshDescription;
	else
		V3D_THROW(graphics::VImporterException,
		"requested buffer is not valid. This seems to be an invalid model.");
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------

