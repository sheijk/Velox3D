#include "VTextureStage.h"
//-----------------------------------------------------------------------------

#include <V3dLib/Graphics.h>
#include <v3d/Image.h>
#include <V3dLib/Math.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

VTextureStage::VTextureStage(VStringParam in_strFileName, graphics::IVDevice& device) :
	m_hPreviewMesh(0)
{
	m_TextureFileName = in_strFileName;

	// try to open the image
	VServicePtr<v3d::image::IVImageFactory> pImageService;

	m_pImage = pImageService->CreateImage(in_strFileName);

	CreatePreviewMesh(device);
}

VTextureStage::VTextureStage(image::VImage& in_Image, graphics::IVDevice& device) :
	m_hPreviewMesh(0)
{
	m_pImage = SharedPtr(new image::VImage(in_Image));

	CreatePreviewMesh(device);
}

VTextureDistributionOptions& VTextureStage::Distribution()
{
	return m_Distri;
}

const VTextureDistributionOptions& VTextureStage::Distribution() const
{
	return m_Distri;
}

VStringRetVal VTextureStage::GetTextureFileName()
{
	return m_TextureFileName;
}

vbyte VTextureStage::GetPixelContribution(
	vuint x, vuint y, vfloat32 height, vuint comp
	)
{
	vbyte val = m_pImage->GetPixelData()[(x+y*m_pImage->GetWidth())*3+comp];

	if( height >= Distribution().minHeight &&
		height <= Distribution().maxHeight )
	{
		return val;
	}
	else
	{
		return 0;
	}
}

v3d::image::VImage& VTextureStage::Image()
{
	return *m_pImage;
}

template<typename GeometryProvider>
v3d::graphics::VMeshDescription BuildMeshDescription(
	graphics::IVDevice& device,
	GeometryProvider& provider)
{
	v3d::graphics::VMeshDescription meshDescr = BuildMeshDescription(
		device,
		provider.GetVertexBuffer().GetDataAddress(),
		provider.GetVertexBuffer().GetSize(),
		provider.GetIndexBuffer().GetDataAddress(),
		provider.GetIndexBuffer().GetSize()
		);

	meshDescr.SetGeometryType(provider.GetGeometryType());
	//meshDescr.geometryType = provider.GetGeometryType();

	return meshDescr;
}

void VTextureStage::CreatePreviewMesh(graphics::IVDevice& device)
{
	// create a quad mesh description
	graphics::VQuadMesh<graphics::VTexturedVertex> quad;
	quad.GenerateCoordinates();
	quad.GenerateTexCoords();

	for(vuint vertexNum = 0; vertexNum < quad.GetVertexBuffer().GetSize();
		++vertexNum)
	{
		quad.GetVertexBuffer()[vertexNum].position.z = -1.0f;
	}

	v3d::graphics::VMeshDescription md = BuildMeshDescription(
		device, quad);
	
	// create a texture material
	graphics::VMaterialDescription mat;
	//graphics::BuildTextureMaterial(
	//	&device,
	//	m_TextureFileName);
	mat.AddTexture(graphics::CreateTextureRef(device, *m_pImage));
	
	// create mesh
    m_hPreviewMesh = device.CreateMesh(md, mat);
}

void VTextureStage::ReleaseResources()
{
	//in_DrawList.GetDevice().DeleteMesh(m_hPreviewMesh);
}

void VTextureStage::AddPreviewMesh(graphics::IVDrawList& in_DrawList)
{
	if( m_hPreviewMesh == 0 ) 
	{
		CreatePreviewMesh(in_DrawList.GetDevice());
	}

	in_DrawList.Add(graphics::VModel(m_hPreviewMesh, math::IdentityPtr()));
}

void VTextureStage::RemovePreviewMesh(graphics::IVDrawList& in_DrawList)
{
	in_DrawList.Remove(graphics::VModel(m_hPreviewMesh, math::IdentityPtr()));
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
