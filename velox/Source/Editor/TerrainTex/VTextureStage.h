#ifndef V3D_VTEXTURESTAGE_2004_06_18_H
#define V3D_VTEXTURESTAGE_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/IVDevice.h>
#include <v3d/Image.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics { 
	class IVDrawList; 
}}

namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

struct VTextureDistributionOptions
{
    vfloat32 minHeight;
	vfloat32 maxHeight;
};

class VTextureStage
{
public:
	VTextureStage(VStringParam in_strFileName, graphics::IVDevice& device);
	VTextureStage(image::VImage& in_Image, graphics::IVDevice& device);

	VTextureDistributionOptions& Distribution();

	const VTextureDistributionOptions& Distribution() const;

	VStringRetVal GetTextureFileName();

	v3d::image::VImage& Image();

	void AddPreviewMesh(graphics::IVDrawList& in_DrawList);
	void RemovePreviewMesh(graphics::IVDrawList& in_DrawList);

	vbyte GetPixelContribution(vuint x, vuint y, vfloat32 height, vuint comp);

private:
	// no copy'ing
	VTextureStage(const VTextureStage&);

	void CreatePreviewMesh(graphics::IVDevice& device);
	void ReleaseResources();

	VString m_TextureFileName;
	VTextureDistributionOptions m_Distri;
	v3d::image::IVImageFactory::ImagePtr m_pImage;
	graphics::IVDevice::MeshHandle m_hPreviewMesh;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTAGE_2004_06_18_H
