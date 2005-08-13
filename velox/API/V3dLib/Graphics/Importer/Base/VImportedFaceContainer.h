#ifndef V3D_VIMPORTEDFACECONTAINER_2005_05_21_H
#define V3D_VIMPORTEDFACECONTAINER_2005_05_21_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVDevice.h>
#include <v3d/Graphics/VModel.h>
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

	void CreateMeshes(graphics::VModel* in_pModel);

private:
	
	typedef std::list<std::string> MaterialLoadedList;
	vbool IsInMaterialLoadedList(VStringParam in_sName);

	std::list<VImportedFaceDescription*> m_FaceList;
	MaterialLoadedList m_MaterialLoadedList;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VIMPORTEDFACECONTAINER_2005_05_21_H