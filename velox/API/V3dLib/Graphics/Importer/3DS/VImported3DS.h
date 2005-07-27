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

#include <V3dLib/Graphics/Importer/Base/VImportedMaterialContainer.h>
#include <V3dLib/Graphics/Importer/Base/VImportedMaterialDescription.h>
#include <V3dLib/Graphics/Importer/Base/VImportedFaceContainer.h>

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

	vbool LoadFile(VStringParam in_sFilename);

	/**
	 * load the model to the resource
	 */
	
	vbool LoadModel();
	vbool LoadNode(Lib3dsNode* in_pNode);
	void CreateMeshResourceName(VStringParam in_sName);
	VStringRetVal CreateMeshPartName(VStringParam in_sMeshPartName);
	VStringRetVal GetMeshResourceName();
	void CreateMeshBufferResource(
		VStringParam in_sMeshname,
		VImportedBufferDescription* in_BufferInfo);
	
	//the libs file structure for loading
	Lib3dsFile* m_p3DSFile;
	std::string m_sMeshResourceName;

	VImportedFaceContainer m_FaceContainer;
	VImportedMaterialContainer m_MaterialContainer;

};
//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VIMPORTED3DS_04_08_23_H