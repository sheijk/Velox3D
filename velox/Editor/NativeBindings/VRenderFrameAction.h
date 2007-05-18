/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VRENDERFRAMEACTION_2006_11_11_H
#define V3D_VRENDERFRAMEACTION_2006_11_11_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVShooting.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Input/IVInputManager.h>

#include "IVFrameAction.h"

#include "../../Source/Graphics/OpenGL/VOpenGLDevice.h"
#include "../../Source/InputLib/VDIInputManager.h"

#include <windows.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

typedef int VNativeWindowHandle;

/**
 * Will tell a given shooting to render to a given device each frame
 *
 * @see v3d::editor::IVFrameAction
 * @see v3d::editor::VView
 * @author sheijk
 */
class VRenderFrameAction : public IVFrameAction
{
public:
	VRenderFrameAction(VNativeWindowHandle in_Hwnd);

	virtual void Init();
	virtual void UpdateFrame(vfloat32 in_fFrameDuration);
	virtual void Shutdown();

	void Render();

	void RegisterSelf();
	void UnregisterSelf();

	void SetShooting(v3d::scene::IVShooting* in_pShooting);
	v3d::graphics::IVDevice* GetDevice();
	v3d::input::IVInputManager* GetInputManager();

	void SetIgnoreInput(vbool ignore);

	//void setSize(vuint width, vuint height);
	void SetArea(vint left, vint top, vint right, vint bottom);

	static void InitRendering(VNativeWindowHandle handle);
	static void ShutdownRendering();
private:
	vuint m_nWidth;
	vuint m_nHeight;
	vbool m_bResized;

	v3d::scene::IVShooting* m_pShooting;
	v3d::VSharedPtr<v3d::graphics::VOpenGLDevice> m_pDevice;
	HWND m_HWND;
	v3d::input::VDIInputManager* m_pInputManager;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VRENDERFRAMEACTION_2006_11_11_H

