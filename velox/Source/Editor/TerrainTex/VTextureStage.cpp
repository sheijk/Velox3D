#include "VTextureStage.h"
//-----------------------------------------------------------------------------

#include <v3d/Image.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

VTextureStage::VTextureStage(VStringParam in_strFileName)
{
	m_TextureFileName = in_strFileName;

	// try to open the image
	//VServicePtr<v3d::image::IVImageFactory> pImageService;

	//m_pImage = pImageService->CreateImage(in_strFileName);
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

v3d::image::VImage& VTextureStage::Image()
{
	return *m_pImage;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
