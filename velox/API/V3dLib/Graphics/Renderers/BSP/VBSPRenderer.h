#ifndef V3D_VBSPRENDERER_21_04_04_H
#define V3D_VBSPRENDERER_21_04_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3dLib/Graphics/Portal/IVCell.h>
#include <V3dLib/Graphics/Generators/VBoxMesh.h>
#include <V3dLib/Graphics/Geometry/VSimpleVertex.h>
#include <V3dLib/Graphics/Geometry/VTexturedVertex.h>
#include <V3dLib/Graphics/Geometry/VResizeableGeometryData.h>
#include <V3dLib/Utils/VStreamReader.h>
#include <V3dLib/Graphics/Importer/VQ3BspImporter.h>
#include <list>
#include <vector>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
//-----------------------------------------------------------------------------
class VBSPRenderer : public IVCell
{
public:
	
	//interface

	virtual void Cull(VCamera* in_pCamera, VMultipassDrawList& in_DrawList) ;
	virtual void Hide(VMultipassDrawList& in_DrawList) ;
	
	VBSPRenderer(IVDevice* in_pDevice, VMultipassDrawList& in_DrawList);
	~VBSPRenderer();

	void Show();
	

	//void AddCell(IVCell* in_pCell);

private:

	typedef VPointer<VMatrix44f>::SharedPtr MatrixPtr;

	void BuildCell();
	void BuildModelList();
	
	void GetFaceElements();
	void CreateTextures();
	void CreateLightmaps();
	
	
	vuint m_iNumFaceElements;
	utils::VQ3BspImporter m_Level;

	//flag indicating model is added to drawlist
	vbool m_bModelAdded;

	// rendering members
	IVDevice* m_pDevice;
	v3d::graphics::VMultipassDrawList* m_pDrawList;

	VResizeableGeometryData<VTexturedVertex> cell;

	std::list<VModel*> m_pModelList;
	std::vector<VMaterialDescription*> m_MaterialList;
	std::vector<VMaterialDescription*> m_LightMaterialList;


	//our list we are connecting this cell to another
	std::list<IVCell*> m_CellList;
	

};
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBSPRENDERER_21_04_04_H
