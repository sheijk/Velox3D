#ifndef V3D_VIMPORTEDFACEDESCRIPTION_2005_05_21_H
#define V3D_VIMPORTEDFACEDESCRIPTION_2005_05_21_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Resource/VResourceId.h>
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


private:

	vuint m_nFaceId;
	vuint m_nFaceIndexStart;
	std::string m_sParentName;
	std::string m_sName;
	VImportedMaterialDescription* m_pMaterial;
	//resource::VResourceId* m_pResourceId;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VIMPORTEDFACEDESCRIPTION_2005_05_21_H
