#ifndef V3D_VDISPLAYSETTINGS_H
#define V3D_VDISPLAYSETTINGS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Settings for the window and graphics device
 *
 * @author sheijk/insane
 */
class VDisplaySettings
{
public:
	VDisplaySettings();

	void SetFullscreen(vbool f);
	vbool IsFullscreen() const;

	void SetSize(vuint width, vuint height);
	void SetWidth(vuint w);
	vuint GetWidth() const;
	void SetHeight(vuint h);
	vuint GetHeight() const;

	void SetPosition(vuint x, vuint y);
	void SetX(vuint x);
	vuint GetX() const;
	void SetY(vuint y);
	vuint GetY() const;

	void SetBitsPerPixel(vuint bpp);
	vuint GetBitsPerPixel() const;

	void SetDepthBits(vuint depth);
	vuint GetDepthBits() const;

	vuint GetStencilBits() const;
	vuint GetAccumulationBits() const;

	std::string GetAPI() const;
	void SetAPI(const std::string& api);

private:
	vbool m_bFullscreen;
	vuint m_nWidth;
	vuint m_nHeight;
	vuint m_nWinCoordX;
	vuint m_nWinCoordY;
	vuint m_nBitsPerPixel;
	vuint m_nAccumulationBuffer;
	vuint m_nDepthBits;
	vuint m_nStencilBits;
	std::string m_sAPIType;
	
	vfloat32 m_fFieldOfView;
	vfloat32 m_fNearClippingPlane;
	vfloat32 m_fFarClippingPlane;
	vfloat32 m_fClearDepth;

	vfloat32 m_fBackgroundRed;
	vfloat32 m_fBackgroundGreen;
	vfloat32 m_fBackgroundBlue;
	vfloat32 m_fBackgroundAlpha;

	
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif V3D_VDISPLAYSETTINGS_H
