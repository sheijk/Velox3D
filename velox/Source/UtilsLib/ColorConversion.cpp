#include <v3dLib/Utils/ColorConversion.h>
#include <cmath>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace utils{

XYZColor ConvertYxyToXYZ( const YxyColor in_Color )
{
	XYZColor color;

	color.X = in_Color.x * (in_Color.Y / in_Color.y);
	color.Y = in_Color.Y;
	color.Z = (1.0 - in_Color.x - in_Color.y)* (in_Color.Y/in_Color.y);

	return color;
}

void ScaleXYZLuminanceTORGBRange( XYZColor& inout_Color )
{
	//inout_Color.Y = 1- e(-1.0f/25.0f)* inout_Color.Y;
}

RGBColor ConvertXYZToRGB( const XYZColor in_Color )
{
	RGBColor color;

	color.r =  3.240479 * in_Color.X  -1.537150 * in_Color.Y  -0.498535 * in_Color.Z;
	color.g = -0.969256 * in_Color.X  +1.875991 * in_Color.Y  +0.041556 * in_Color.Z;
	color.b =  0.055648 * in_Color.X  -0.204043 * in_Color.Y  +1.057311 * in_Color.Z;

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