#include <v3dlib/Graphics/Renderers/Sky/VDaylightSkyColorizer.h>
#include <v3dlib/Math.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d::utils;

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {

VDaylightSkyColorizer::VDaylightSkyColorizer(
	vfloat32 in_fSunTheta,
	vfloat32 in_fSunPhi,
	vfloat32 in_fTurbidity)

	: m_fSunTheta(in_fSunTheta),
	  m_fSunPhi(in_fSunPhi)
{
	SetTurbidity(in_fTurbidity);
	//CalculateZenith();
}

VDaylightSkyColorizer::~VDaylightSkyColorizer()
{

}

void VDaylightSkyColorizer::SetSunPosition(vfloat32 in_fSunTheta, vfloat32 in_fSunPhi )
{
	m_fSunTheta = in_fSunTheta;
	m_fSunPhi= in_fSunPhi;
	
	CalculateZenith();
}

void VDaylightSkyColorizer::SetTurbidity(vfloat32 in_fTurbidity)
{
	m_fTurbidity = in_fTurbidity;

	//precalculate distribution coefficients
	//luminace 
	m_DCY[0] =  0.1787f * m_fTurbidity - 1.4630f;
	m_DCY[1] = -0.3554f * m_fTurbidity + 0.4275f;
	m_DCY[2] = -0.0227f * m_fTurbidity + 5.3251f;
	m_DCY[3] =  0.1206f * m_fTurbidity - 2.5771f;
	m_DCY[4] = -0.0670f * m_fTurbidity + 0.3703f;

	//x
	m_DCx[0] = -0.0193f * m_fTurbidity - 0.2592f;
	m_DCx[1] = -0.0665f * m_fTurbidity + 0.0008f;
	m_DCx[2] = -0.0004f * m_fTurbidity + 0.2125f;
	m_DCx[3] = -0.0641f * m_fTurbidity - 0.8989f;
	m_DCx[4] = -0.0033f * m_fTurbidity - 0.0452f;

	//y
	m_DCy[0] = -0.0167f * m_fTurbidity - 0.2608f;
	m_DCy[1] = -0.0950f * m_fTurbidity + 0.0092f;
	m_DCy[2] = -0.0079f * m_fTurbidity + 0.2102f;
	m_DCy[3] = -0.0441f * m_fTurbidity - 1.6537f;
	m_DCy[4] = -0.0109f * m_fTurbidity + 0.0529f;

	CalculateZenith();
}

void VDaylightSkyColorizer::CalculateZenith()
{
	// theta, theta square, theta cubic
    const vfloat32 t1 = m_fSunTheta;
	const vfloat32 t2 = t1*t1;
	const vfloat32 t3 = t2 * t1;

	//Calculate x
	m_ZenithColor.x =  0.00166f * t3 -0.00375f * t2 +0.00209f * t1 +
				      -0.02903f * t3 +0.06377f * t2 -0.03203f * t1 +0.00394f * m_fTurbidity +
                       0.11693f * t3 -0.21196f * t2 +0.06052f * t1 +0.25886f;

	//Calculate y
	m_ZenithColor.y =  0.00275f * t3  -0.00610f * t2 +0.00317f * t1 +
				      -0.04214f * t3  +0.08970f * t2 -0.04153f * t1 + 0.00516f * m_fTurbidity +
                       0.15346f * t3  -0.26756f * t2 +0.06670f * t1 + 0.26688f;

	//Calcutate Y
	vfloat32 fTan = ( 4.0f / 9.0f - m_fTurbidity / 120.0f ) * ( math::Pi() - 2.0f * m_fSunTheta );
	m_ZenithColor.Y =  ( 4.0453f * m_fTurbidity - 4.9710f ) * tan(fTan) - 0.2155f * m_fTurbidity + 2.4192f;
	
	if ( m_ZenithColor.Y < 0.0f )
		m_ZenithColor.Y = -m_ZenithColor.Y;
}

YxyColor VDaylightSkyColorizer::CalculateDistribution(vfloat32 in_fTheta, vfloat32 in_fGamma)
{
	YxyColor color;

	color.Y = PerezFunction(m_DCY[0], m_DCY[1], m_DCY[2], m_DCY[3], m_DCY[4], in_fTheta, in_fGamma) /
				PerezFunction(m_DCY[0], m_DCY[1], m_DCY[2], m_DCY[3], m_DCY[4], 0.0f, m_fSunTheta );

	color.x = PerezFunction(m_DCx[0], m_DCx[1], m_DCx[2], m_DCx[3], m_DCx[4], in_fTheta, in_fGamma) /
				PerezFunction(m_DCx[0], m_DCx[1], m_DCx[2], m_DCx[3], m_DCx[4], 0.0f, m_fSunTheta );

	color.y = PerezFunction(m_DCy[0], m_DCy[1], m_DCy[2], m_DCy[3], m_DCy[4], in_fTheta, in_fGamma) /
				PerezFunction(m_DCy[0], m_DCy[1], m_DCy[2], m_DCy[3], m_DCy[4], 0.0f, m_fSunTheta );

	return color;
}

vfloat32 VDaylightSkyColorizer::PerezFunction( vfloat32 in_fA,
											   vfloat32 in_fB,
											   vfloat32 in_fC,
											   vfloat32 in_fD,
											   vfloat32 in_fE,
                                               vfloat32 in_fTheta,
											   vfloat32 in_fGamma )
{
	vfloat32 fCos = cos(in_fGamma);
	return ( 1.0f + in_fA * exp(in_fB / cos(in_fTheta)) ) *
		   ( 1.0f + in_fC * exp(in_fD * in_fGamma ) + in_fE * fCos * fCos );
}

vfloat32 GetAngleBetween(
	vfloat32 in_fTheta1,
	vfloat32 in_fPhi1,
	vfloat32 in_fTheta2,
	vfloat32 in_fPhi2)
{
	vfloat32 fCosAngle = sin(in_fTheta1) * sin(in_fTheta2) * cos(in_fPhi2-in_fPhi1) + cos(in_fTheta1) * cos(in_fTheta2);
	
	if ( fCosAngle > 1.0f )
		return 0.0f;

	if ( fCosAngle < -1.0f )
		return math::Pi();

	return acos(fCosAngle);
}


VColor4f VDaylightSkyColorizer::GetColor(vfloat32 in_fTheta, vfloat32 in_fPhi )
{
	vfloat32 fGamma = GetAngleBetween(in_fTheta, in_fPhi, m_fSunTheta, m_fSunPhi);
	//vfloat32 fGamma = GetAngleBetween(0, 0, m_fSunTheta, m_fSunPhi);

    YxyColor distributionColor = CalculateDistribution(in_fTheta, fGamma);
	//YxyColor distributionColor = CalculateDistribution(0.0f, fGamma);
	
	YxyColor skyColor;
	skyColor.Y = m_ZenithColor.Y * distributionColor.Y;
	skyColor.x = m_ZenithColor.x * distributionColor.x;
	skyColor.y = m_ZenithColor.y * distributionColor.y;

	skyColor.Y = 1.0f - exp(-(1.0f/25.0f) * skyColor.Y);

	RGBColor temp = ConvertXYZToRGB( ConvertYxyToXYZ(skyColor) );

	return VColor4f( temp.r, temp.g, temp.b, 1.0f);
}

} //namespace graphics
} //namespace v3d
