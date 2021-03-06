/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VVIEW_2005_07_15_H
#define V3D_VVIEW_2005_07_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/SmartPtr/VSharedPtr.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Graphics/IVRenderContext.h>
#include <V3d/Entity.h>
#include <V3d/Scene.h>
#include <V3d/Entity/VUpdateablePart.h>

#include "../../Source/Graphics/OpenGL/Context/VSubAreaContext.h"
#include "../../Source/Graphics/OpenGL/Context/VWin32WindowContext.h"

#include <V3d/OpenGL.h>
#include <GL/glfw.h>
#include "../../Source/InputLib/VDIInputManager.h"
#include <V3d/Input/IVInputManager.h>

#include <vector>

#include "IVFrameAction.h"
#include "IVSynchronizedAction.h"
#include "VRenderFrameAction.h"
#include "VUpdateManagerCallAction.h"

namespace v3d { namespace graphics {
	class VOpenGLDevice;
}}

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VView
{
public:
	VView();
	virtual ~VView();
	
	void Add(IVFrameAction* in_pAction);
	void Remove(IVFrameAction* in_pAction);
	bool Contains(IVFrameAction* in_pAction);
	
	void Start();
	void Stop();

	void ExecSynchronized(IVSynchronizedAction* in_pAction);
	
	bool IsRunning() const { return m_bIsRunning; }
		
	static VView* GetInstance();

	static void Init(VNativeWindowHandle windowHandle);
	static void Shutdown();

	//graphics::VSubAreaContext* CreateSubAreaContext();

	graphics::VWin32WindowContext* GetMainContext();
private:
#ifndef SWIG
	static void GLFWCALL FrameUpdateLoop(void* arg);
	
	void FrameUpdateLoop();
#endif

	vbool m_bInitCalled;

	static VSharedPtr<VView> s_pInstance;

	bool m_bIsRunning;
	GLFWthread m_Thread;

	typedef std::vector<IVFrameAction*> FrameActions;
	
	FrameActions m_FrameActions;
	FrameActions m_NewFrameActions;
	FrameActions m_OldFrameActions;

	typedef std::vector<IVSynchronizedAction*> SyncActions;
	SyncActions m_SyncActions;
	GLFWmutex m_SyncMutex;
	GLFWcond m_SyncDoneCondition;
	
	static VSharedPtr<graphics::VWin32WindowContext> m_pMainContext;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor 
//-----------------------------------------------------------------------------
#endif // V3D_VVIEW_2005_07_15_H

