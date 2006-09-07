/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Utils/ColorConversion.h>
#include <cmath>
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace utils{

XYZColor ConvertYxyToXYZ( const YxyColor in_Color )
{
	XYZColor color;

	color.X = in_Color.x * (in_Color.Y / in_Color.y);
	color.Y = in_Color.Y;
	color.Z = (1.0f - in_Color.x - in_Color.y)* (in_Color.Y/in_Color.y);

	return color;
}

void ScaleXYZLuminanceTORGBRange( XYZColor& inout_Color )
{
	//TODO what's going on here?? --ins
	//inout_Color.Y = 1- e(-1.0f/25.0f)* inout_Color.Y;
}

RGBColor ConvertXYZToRGB( const XYZColor in_Color )
{
	RGBColor color;

	color.r =  3.240479f * in_Color.X  -1.537150f * in_Color.Y  -0.498535f * in_Color.Z;
	color.g = -0.969256f * in_Color.X  +1.875991f * in_Color.Y  +0.041556f * in_Color.Z;
	color.b =  0.055648f * in_Color.X  -0.204043f * in_Color.Y  +1.057311f * in_Color.Z;

	return color;
}

void GammaCorrection(RGBColor& inout_Color, const vfloat32 in_fGamma )
{
	inout_Color.r = pow(inout_Color.r, 1.0f / in_fGamma);
	inout_Color.g = pow(inout_Color.g, 1.0f / in_fGamma);
	inout_Color.b = pow(inout_Color.b, 1.0f / in_fGamma);
}

//-----------------------------------------------------------------------------
} //namespace utils
} //namespace v3d
//-----------------------------------------------------------------------------
