#include <v3dLib/Graphics/Importer/Base/VImportedFaceDescription.h>
#include <v3dLib/Graphics/Importer/Base/VImportedBufferDescription.h>
#include <v3dLib/Graphics/Importer/Base/VImportedMaterialDescription.h>
//-----------------------------------------------------------------------------
#include <v3d/Graphics.h>
#include <V3dLib/Graphics.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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
	
	resource::VResourceId face =
		pResourceManager->CreateResource(m_sName.c_str());

	VMeshDescription* meshDescription = new VMeshDescription();

	meshDescription->SetGeometryType(VMeshDescription::GeometryType::Triangles);
	meshDescription->SetCoordinateResource(m_sParentName.c_str());
	meshDescription->SetCoordinateFormat(
		in_pBufferDescription->GetVertexBufferFormat()->GetCoordinateFormat());
	
	meshDescription->SetIndexResource(sIndices.c_str());
	meshDescription->SetIndexFormat(VDataFormat(m_nFaceIndexStart, 3, 0));
	
	if(in_pBufferDescription->GetTexCoordCount1())
	{
		meshDescription->SetTexCoordResource(0, sTexCoords.c_str());
		meshDescription->SetTexCoordFormat(0,
		in_pBufferDescription->GetTexCoordBufferFormat1()->GetTexCoordFormat(0));
	}

	//TODO: insert 2. texcoods

	face->AddData(meshDescription);
	
	return face;
}

VStringRetVal VImportedFaceDescription::GetResourceName()
{
	return m_sName.c_str();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
