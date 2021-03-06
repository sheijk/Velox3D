/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/Materials/VModeTypeInfo.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------

namespace {
	VModeTypeInfo<VPolygonMode> g_PolygonModeInfo;
	VModeTypeInfo<VDepthTest> g_DepthTestInfo;
	VModeTypeInfo<VBlendFactor> g_BlendFactorInfo;
	VModeTypeInfo<VTextureWrapMode> g_TextureWrapModeInfo;
	VModeTypeInfo<VTextureFilter> g_TextureFilterInfo;
	VModeTypeInfo<VTexGenMode> g_TexGenModeInfo;
	VModeTypeInfo<VShaderType, CGprofile> g_ShaderTypeInfo;

	class VModeInfoCreator
	{
	public:
		VModeInfoCreator()
		{
			g_PolygonModeInfo.AddModeInfo(PMFilled, "fill", GL_FILL);
			g_PolygonModeInfo.AddModeInfo(PMLine, "line", GL_LINE);
			g_PolygonModeInfo.AddModeInfo(PMPoint, "point", GL_POINT);

			g_DepthTestInfo.AddModeInfo(DepthAlways, "always", GL_ALWAYS);
			g_DepthTestInfo.AddModeInfo(DepthOnLess, "onless", GL_LESS);
			g_DepthTestInfo.AddModeInfo(DepthOnLessEqual, "onlesseq", GL_LEQUAL);
			g_DepthTestInfo.AddModeInfo(DepthOnGreater, "ongreater", GL_GREATER);
			g_DepthTestInfo.AddModeInfo(DepthOnGreaterEqual, "ongreatereq", GL_GEQUAL);
			g_DepthTestInfo.AddModeInfo(DepthNever, "never", GL_NEVER);
			g_DepthTestInfo.AddModeInfo(DepthOnEqual, "onequal", GL_EQUAL);
			g_DepthTestInfo.AddModeInfo(DepthOnNotEqual, "onnotequal", GL_NOTEQUAL);

			g_BlendFactorInfo.AddModeInfo(BlendZero, "zero", GL_ZERO);
			g_BlendFactorInfo.AddModeInfo(BlendOne, "one", GL_ONE);
			g_BlendFactorInfo.AddModeInfo(BlendSourceColor, "source.color", GL_SRC_COLOR);
			g_BlendFactorInfo.AddModeInfo(BlendOneMinusSourceColor, "one.minus.source.color", GL_ONE_MINUS_SRC_COLOR);
			g_BlendFactorInfo.AddModeInfo(BlendDestColor, "dest.color", GL_DST_COLOR);
			g_BlendFactorInfo.AddModeInfo(BlendOneMinusDestColor, "one.minus.dest.color", GL_ONE_MINUS_DST_COLOR);
			g_BlendFactorInfo.AddModeInfo(BlendSourceAlpha, "source.alpha", GL_SRC_ALPHA);
			g_BlendFactorInfo.AddModeInfo(BlendOneMinusSourceAlpha, "one.minus.source.alpha", GL_ONE_MINUS_SRC_ALPHA);
			g_BlendFactorInfo.AddModeInfo(BlendDestAlpha, "dest.alpha", GL_DST_ALPHA);
			g_BlendFactorInfo.AddModeInfo(BlendOneMinusDestAlpha, "one.minus.dest.alpha", GL_ONE_MINUS_DST_ALPHA);
			g_BlendFactorInfo.AddModeInfo(BlendSourceAlphaSaturate, "source.alpha.saturate", GL_SRC_ALPHA_SATURATE);

			g_TextureWrapModeInfo.AddModeInfo(TextureRepeat, "repeat", GL_REPEAT);
			g_TextureWrapModeInfo.AddModeInfo(TextureClamp, "clamp", GL_CLAMP);
			g_TextureWrapModeInfo.AddModeInfo(TextureClampToEdge, "clamp.to.edge", GL_CLAMP_TO_EDGE);

			g_TextureFilterInfo.AddModeInfo(FilterNearest, "nearest", GL_NEAREST);
			g_TextureFilterInfo.AddModeInfo(FilterLinear, "linear", GL_LINEAR);
			g_TextureFilterInfo.AddModeInfo(FilterNearestMipmapNearest, "nearest.mipmap.nearest", GL_NEAREST_MIPMAP_NEAREST);
			g_TextureFilterInfo.AddModeInfo(FilterLinearMipmapNearest, "linear.mipmap.nearest", GL_LINEAR_MIPMAP_NEAREST);
			g_TextureFilterInfo.AddModeInfo(FilterNearestMipmapLinear, "nearest.mipmap.linear", GL_NEAREST_MIPMAP_LINEAR);
			g_TextureFilterInfo.AddModeInfo(FilterLinearMipmapLinear, "linear.mipmap.linear", GL_LINEAR_MIPMAP_LINEAR);

			g_TexGenModeInfo.AddModeInfo(TexGenNone, "none", 0);
			g_TexGenModeInfo.AddModeInfo(TexGenEyeSpace, "eye", GL_EYE_PLANE);

			// difference by 10 in numbers is intended, nvidia has strange naming conventions ;)
			g_ShaderTypeInfo.AddModeInfo(ShaderCGVertex10, "cg.v.10", CG_PROFILE_VP20);
			g_ShaderTypeInfo.AddModeInfo(ShaderCGVertex20, "cg.v.20", CG_PROFILE_VP30);
			//TODO: upgrade to newest cg toolkit, and add next line --sheijk
			//g_ShaderTypeInfo.AddModeInfo(ShaderCGVertex30, "cg.v.20", CG_PROFILE_VP40);

			g_ShaderTypeInfo.AddModeInfo(ShaderCGPixel10, "cg.p.10", CG_PROFILE_FP20);
			g_ShaderTypeInfo.AddModeInfo(ShaderCGPixel20, "cg.p.20", CG_PROFILE_FP30);
		}
	};

	// initialize global mode info
	VModeInfoCreator g_Creator;
}

VModeTypeInfo<VPolygonMode> GetPolygonModeInfo()
{
	return g_PolygonModeInfo;
}

VModeTypeInfo<VDepthTest> GetDepthTestInfo()
{
	return g_DepthTestInfo;
}

VModeTypeInfo<VBlendFactor> GetBlendFactorInfo()
{
	return g_BlendFactorInfo;
}

VModeTypeInfo<VTextureWrapMode> GetTextureWrapModeInfo()
{
	return g_TextureWrapModeInfo;
}

VModeTypeInfo<VTextureFilter> GetTextureFilterInfo()
{
	return g_TextureFilterInfo;
}

VModeTypeInfo<VTexGenMode> GetTexGenModeInfo()
{
	return g_TexGenModeInfo;
}

VModeTypeInfo<VShaderType, CGprofile> GetShaderTypeInfo()
{
	return g_ShaderTypeInfo;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

