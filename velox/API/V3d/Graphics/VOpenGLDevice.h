#ifndef V3D_VOPENGLDEVICE_H
#define V3D_VOPENGLDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVDevice.h>
#include <v3d/Graphics/VDisplaySettings.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VOpenGLDevice : public IVDevice
{
public:

	/**
	* Contructor for adding a window	
	*/

	VOpenGLDevice(graphics::VDisplaySettings* in_pSettings, HWND in_hWnd);
	virtual ~VOpenGLDevice();

	/**
	* Inherts from IVDevice
	*/

	virtual IVMesh* CreateMesh(); //TODO: insert mesh description
	virtual IVMaterial* CreateMaterial();
	virtual void ApplyMaterial(IVMaterial* in_pMaterial);
	virtual void RenderMesh(IVMesh* in_pMesh);

	/**
	* This is only implemented to show anything by now
	* TODO: build the damn renderer ;)
	*/

	virtual void BeginScene(); 
	virtual void EndScene();
	
private:

	
	
	/**
	 * All gl internal calling methods
	 */
	
	void SetDisplay();
	void SetPixFormat();
	void CreateContext();
	void DestroyContext();
	void SetScreenSize();
	void SetBackgroundColor();
		

	/**
	 * Device dependant variables:
	 */
		
	graphics::VDisplaySettings* m_DisplaySettings;
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;

};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VOPENGLDEVICE_H
