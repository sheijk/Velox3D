/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_STATETYPES_2004_09_23_H
#define V3D_STATETYPES_2004_09_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math/VMatrixOps.h>

#include <iostream>

/*
Name-Type-GLenum Zuordnungen werden in VModeTypeInfo.cpp festgelegt
*/

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting


/**
 * The polygon mode for rendering.
 * Filled means normal
 * Point means render vertices as points
 * Line means wireframe
 */
enum VPolygonMode
{
	PMFilled, PMPoint, PMLine
};

std::ostream& operator<<(std::ostream& str, VPolygonMode mode);

//-----------------------------------------------------------------------------
// z-buffer

/**
 * The depth buffer test mode
 */
enum VDepthTest
{
	DepthAlways,
	DepthOnLess,
	DepthOnLessEqual,
	DepthOnGreater,
	DepthOnGreaterEqual,
	DepthNever,
	DepthOnEqual,
	DepthOnNotEqual
};

std::ostream& operator<<(std::ostream& str, VDepthTest depthTest);

/** Enable or disable depth test */
enum VDepthTestEnable
{
	DepthTestEnabled,
	DepthTestDisabled
};

std::ostream& operator<<(std::ostream& str, VDepthTestEnable enabled);

/** write values to z buffer or not */
enum VDepthWriteMode
{
	DepthWrite,
	DepthReadOnly
};

std::ostream& operator<<(std::ostream& str, VDepthWriteMode writeMode);

//-----------------------------------------------------------------------------
// alpha blending

/**
 * Blending factors
 */
enum VBlendFactor
{
	BlendZero,
	BlendOne,
	BlendSourceColor,
	BlendOneMinusSourceColor,
	BlendDestColor,
	BlendOneMinusDestColor,
	BlendSourceAlpha,
	BlendOneMinusSourceAlpha,
	BlendDestAlpha,
	BlendOneMinusDestAlpha,
	BlendSourceAlphaSaturate
};

std::ostream& operator<<(std::ostream& str, VBlendFactor blendFactor);

/** enable or disable alpha blending */
enum VBlendEnable
{
	BlendEnabled,
	BlendDisabled
};

std::ostream& operator<<(std::ostream& str, VBlendEnable enable);

//-----------------------------------------------------------------------------
// textures

/**
 * Handling of texture coordinates outside the range [0,1]
 */
enum VTextureWrapMode
{
	TextureRepeat,
	TextureClamp,
	TextureClampToEdge
};

std::ostream& operator<<(std::ostream& str, VTextureWrapMode wrapMode);
std::istream& operator>>(std::istream& str, VTextureWrapMode& wrapMode);

/**
 * Filtering of textures for minification/magnification
 */
enum VTextureFilter
{
	FilterNearest,
	FilterLinear,
	FilterNearestMipmapNearest,
	FilterLinearMipmapNearest,
	FilterNearestMipmapLinear,
	FilterLinearMipmapLinear
};

std::ostream& operator<<(std::ostream& str, VTextureFilter filter);
std::istream& operator>>(std::istream& str, VTextureFilter& filter);

/** Texture coord generation */
enum VTexGenMode
{
	TexGenNone,
	TexGenEyeSpace
};

std::ostream& operator<<(std::ostream& str, VTexGenMode genMode);
std::istream& operator>>(std::istream& str, VTexGenMode& genMode);

/**
 * Enable or disable any color channel for writing
 */
struct VColorBufferMask
{
	VColorBufferMask();
	VColorBufferMask(vbool red, vbool green, vbool blue, vbool alpha);

	vbool writeRed;
	vbool writeGreen;
	vbool writeBlue;
	vbool writeAlpha;
};

/**
 * Different shader types
 */
enum VShaderType
{
	ShaderCGVertex10,
    ShaderCGVertex20,
	//ShaderCGVertex30
	ShaderCGPixel10,
	ShaderCGPixel20
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_STATETYPES_2004_09_23_H

