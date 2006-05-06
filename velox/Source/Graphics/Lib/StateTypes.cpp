#include <V3dLib/Graphics/Materials/StateTypes.h>
//-----------------------------------------------------------------------------

#include <V3dLib/Graphics/Materials/VModeTypeInfo.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { 

namespace graphics {
//-----------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& str, VPolygonMode mode)
{
	str << GetPolygonModeInfo().GetName(mode);
	return str;
}

//-----------------------------------------------------------------------------
// z-buffer

std::ostream& operator<<(std::ostream& str, VDepthTest depthTest)
{
	str << GetDepthTestInfo().GetName(depthTest);
	return str;
}

std::ostream& operator<<(std::ostream& str, VDepthTestEnable enabled)
{
	str << (enabled == DepthTestEnabled ? "true" : "false");
	return str;
}

std::ostream& operator<<(std::ostream& str, VDepthWriteMode writeMode)
{
	str << (writeMode == DepthWrite ? "true" : "false");
	return str;
}

//-----------------------------------------------------------------------------
// alpha blending

std::ostream& operator<<(std::ostream& str, VBlendFactor blendFactor)
{
	str << GetBlendFactorInfo().GetName(blendFactor);
	return str;
}

std::ostream& operator<<(std::ostream& str, VBlendEnable enable)
{
	str << (enable == BlendEnabled ? "true" : "false");
	return str;
}

//-----------------------------------------------------------------------------
// textures

std::ostream& operator<<(std::ostream& str, VTextureWrapMode wrapMode)
{
	str << GetTextureWrapModeInfo().GetName(wrapMode);
	return str;
}

std::istream& operator>>(std::istream& str, VTextureWrapMode& wrapMode)
{
	std::string text;
	str >> text;

	wrapMode = GetTextureWrapModeInfo().GetMode(text);
	return str;
}

std::ostream& operator<<(std::ostream& str, VTextureFilter filter)
{
	str << GetTextureFilterInfo().GetName(filter);
	return str;
}

std::istream& operator>>(std::istream& str, VTextureFilter& filter)
{
	std::string text;
	str >> text;

	filter = GetTextureFilterInfo().GetMode(text);
	return str;
}

std::ostream& operator<<(std::ostream& str, VTexGenMode genMode)
{
	str << GetTexGenModeInfo().GetName(genMode);

	return str;	
}

std::istream& operator>>(std::istream& str, VTexGenMode& genMode)
{
	std::string text;
	str >> text;

    genMode = GetTexGenModeInfo().GetMode(text);

	return str;
}

//-----------------------------------------------------------------------------

VColorBufferMask::VColorBufferMask() : 
	writeRed(true), writeGreen(true), writeBlue(true), writeAlpha(true)
{}

VColorBufferMask::VColorBufferMask(vbool red, vbool green, vbool blue, vbool alpha)
{
	writeRed = red;
	writeGreen = green;
	writeBlue = blue;
	writeAlpha = alpha;
}


//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
