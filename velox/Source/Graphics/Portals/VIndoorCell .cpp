#include <V3dLib/Graphics/Portal/VIndoorCell.h>
#include <V3dLib/Graphics/Geometry/VGeometryUtil.h>
#include <V3dLib/Graphics/Geometry/VGeometryData.h>
#include <V3d/Math/VMatrixOps.h>
#include <V3d/Math/TransformationOps.h>
#include <v3d/Image/IVImageFactory.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3dlib/Graphics/Misc/MiscUtils.h>
#include <V3dLib/Graphics/Geometry.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VIndoorCell::VIndoorCell(IVDevice* in_pDevice) 
{
	m_bModelAdded = false;
	
	m_pDevice = in_pDevice;
	
	/*m_pPortalBox = new VBox<VSimpleVertex>(5,5,1);
	m_pPortalBox->CreateCoordinates();
	*///m_pPortalBox->CreateTextureCoordinates();

	VGeometryData<VTexturedVertex> box(VMeshDescription::GeometryType::Quads, 8, 20);

	box.GetVertexBuffer()[0].position.x = 10;
	box.GetVertexBuffer()[0].position.y = 0;
	box.GetVertexBuffer()[0].position.z = -15;
	box.GetVertexBuffer()[0].texCoords.u = 0.7f;
	box.GetVertexBuffer()[0].texCoords.v = 0.7f;
    	
	box.GetVertexBuffer()[1].position.x = 10;
	box.GetVertexBuffer()[1].position.y = 0;
	box.GetVertexBuffer()[1].position.z = -5;
	box.GetVertexBuffer()[1].texCoords.u = 0.7f;
	box.GetVertexBuffer()[1].texCoords.v = 0.3f;

	box.GetVertexBuffer()[2].position.x = -10;
	box.GetVertexBuffer()[2].position.y = 0;
	box.GetVertexBuffer()[2].position.z = -15;
	box.GetVertexBuffer()[2].texCoords.u = 0.3f;
	box.GetVertexBuffer()[2].texCoords.v = 0.7f;

	box.GetVertexBuffer()[3].position.x = -10;
	box.GetVertexBuffer()[3].position.y = 0;
	box.GetVertexBuffer()[3].position.z = -5;
	box.GetVertexBuffer()[3].texCoords.u = 0.3f;
	box.GetVertexBuffer()[3].texCoords.v = 0.3f;

	box.GetVertexBuffer()[4].position.x = -30;
	box.GetVertexBuffer()[4].position.y = 20;
	box.GetVertexBuffer()[4].position.z = 15;
	box.GetVertexBuffer()[4].texCoords.u = 0.0f;
	box.GetVertexBuffer()[4].texCoords.v = 0.0f;

	box.GetVertexBuffer()[5].position.x = 30;
	box.GetVertexBuffer()[5].position.y = 20;
	box.GetVertexBuffer()[5].position.z = 15;
	box.GetVertexBuffer()[5].texCoords.u = 1.0f;
	box.GetVertexBuffer()[5].texCoords.v = 0;

	box.GetVertexBuffer()[6].position.x = -30;
	box.GetVertexBuffer()[6].position.y = 20;
	box.GetVertexBuffer()[6].position.z = -30;
	box.GetVertexBuffer()[6].texCoords.u = 0.0f;
	box.GetVertexBuffer()[6].texCoords.v = 1.0f;


	////8
	box.GetVertexBuffer()[7].position.x = 30;
	box.GetVertexBuffer()[7].position.y = 20;
	box.GetVertexBuffer()[7].position.z = -30;
	box.GetVertexBuffer()[7].texCoords.u = 1.0f;
	box.GetVertexBuffer()[7].texCoords.v = 1.0f;


	box.GetIndexBuffer()[0] = 0;
	box.GetIndexBuffer()[1] = 1;
	box.GetIndexBuffer()[2] = 3;
	box.GetIndexBuffer()[3] = 2;

	box.GetIndexBuffer()[4] = 1;
	box.GetIndexBuffer()[5] = 5;
	box.GetIndexBuffer()[6] = 4;
	box.GetIndexBuffer()[7] = 3;

	box.GetIndexBuffer()[8] = 0;
	box.GetIndexBuffer()[9] = 7;
	box.GetIndexBuffer()[10] = 5;
	box.GetIndexBuffer()[11] = 1;

	box.GetIndexBuffer()[12] = 2;
	box.GetIndexBuffer()[13] = 3;
	box.GetIndexBuffer()[14] = 4;
	box.GetIndexBuffer()[15] = 6;

	box.GetIndexBuffer()[16] = 2;
	box.GetIndexBuffer()[17] = 6;
	box.GetIndexBuffer()[18] = 7;
	box.GetIndexBuffer()[19] = 0;
	
	ForEachVertex(box.GetVertexBuffer(), SwitchYZ<VTexturedVertex>);
	ForEachVertex(box.GetVertexBuffer(), 
		ScaleVertex<VTexturedVertex>(.2f, .2f, .1f));
	ForEachVertex(box.GetVertexBuffer(),
		AddVertex<VTexturedVertex>(0, 0, -2.0f));



	VMeshDescription meshDescs;

	meshDescs =	BuildMeshDescription<VTexturedVertex>(
		*m_pDevice,
		box.GetVertexBuffer().GetDataAddress(), 
		box.GetVertexBuffer().GetSize(),
		box.GetIndexBuffer().GetDataAddress(),
		box.GetIndexBuffer().GetSize()
		);

	meshDescs.geometryType = box.GetGeometryType();
	

	VMaterialDescription matDescs =
		BuildTextureMaterial(m_pDevice, "/data/test2.jpg");



	matDescs.backPolyMode = VMaterialDescription::Filled;
	matDescs.frontPolyMode = VMaterialDescription::Filled;

	IVDevice::MeshHandle BoxHandle = m_pDevice->CreateMesh(meshDescs, matDescs);

	MatrixPtr translate;
	
	translate.Assign(new VMatrix44f());

	Identity(*translate);

//	math::SetTranslate(*translate, 0.0f,0.0f, -10.0f);

	m_pModel = new VModel(BoxHandle, translate);
}

VIndoorCell::~VIndoorCell()
{
}

void VIndoorCell::Cull(VCamera* in_pCamera, VMultipassDrawList& in_DrawList)
{
	m_pDrawList = &in_DrawList;
	
	//show this cell
	Show();

	//traversal list to set each connected cell to be  visible
	std::list<IVCell*>::iterator begin = m_CellList.begin();

	for(begin; begin != m_CellList.end(); ++begin)
	{
		(*begin)->Cull(in_pCamera, in_DrawList);
	}
}

void VIndoorCell::Show()
{
	if(!m_bModelAdded)
	{	
		m_pDrawList->Add(*m_pModel);
		m_bModelAdded = true;
	}
}

void VIndoorCell::Hide(VMultipassDrawList& in_DrawList)
{
	if(m_bModelAdded)
	{
        m_pDrawList->Remove(*m_pModel);
		m_bModelAdded = false;
	}
}

void VIndoorCell::AddCell(IVCell* in_pCell)
{
	m_CellList.push_back(in_pCell);
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
