#include "VTextureStage.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

VTextureStage::VTextureStage(VStringParam in_strFileName)
{
	m_TextureFileName = in_strFileName;
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
	return m_Image;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
