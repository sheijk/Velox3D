/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_COLORCONVERSION_2004_06_13_H
#define V3D_COLORCONVERSION_2004_06_13_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace utils {

//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Structure for RGB color
 */
struct RGBColor
{
	vfloat32 r;
	vfloat32 g;
	vfloat32 b;
};

/**
 * Structure for Yxy color (luminance(Y) and chromaticity(xy))
 */
struct YxyColor
{
	vfloat32 Y;
	vfloat32 x;
	vfloat32 y;
};

/**
 * Structure for XYZ CIE (tristimulus) color
 */
struct XYZColor
{
	vfloat32 X;
	vfloat32 Y;
	vfloat32 Z;
};

/**
 * Converts from Yxy color space to XYZ color space
 */
XYZColor ConvertYxyToXYZ( const YxyColor in_Color );

/**
 * Luminance from XYZ color space might be to big for RGB space. So scale it down
 */
void ScaleXYZLuminanceTORGBRange( XYZColor& inout_Color );

/**
 * @brief Converts from XYZ color space to RGB color space
 * The conversion using following matrix
 * / 3.240479  -1.537150 -0.498535 \
 * | -0.969256 1.875991  0.041556  |
 * \ 0.055648  -0.204043 +1.057311 /
 */
RGBColor ConvertXYZToRGB( const XYZColor in_Color );

/**
 * Gamma Corrention in RGB color space
 * @param inout_Color color that is gamme corrected
 * @param in_fGamma gamma
 */
void GammaCorrection(RGBColor& inout_Color, const vfloat32 in_fGamma );

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_COLORCONVERSION_2004_06_13_H

