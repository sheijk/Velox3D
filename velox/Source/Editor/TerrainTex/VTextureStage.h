#ifndef V3D_VTEXTURESTAGE_2004_06_18_H
#define V3D_VTEXTURESTAGE_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Image.h>
//-----------------------------------------------------------------------------
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
	VTextureStage(VStringParam in_strFileName);

	VTextureDistributionOptions& Distribution();

	const VTextureDistributionOptions& Distribution() const;

	VStringRetVal GetTextureFileName();

	v3d::image::VImage& Image();

private:
	VString m_TextureFileName;
	VTextureDistributionOptions m_Distri;
	v3d::image::VImage m_Image;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTAGE_2004_06_18_H
