#ifndef V3D_VVIEW_2005_07_15_H
#define V3D_VVIEW_2005_07_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/SmartPtr/VSharedPtr.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Entity.h>
#include <V3d/Scene.h>

#include <V3d/OpenGL.h>
#include <GL/glfw.h>

#include <vector>


namespace v3d { namespace graphics {
	class VOpenGLDevice;
}}

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

typedef int VNativeWindowHandle;

class IVFrameAction
{
public:
	virtual ~IVFrameAction() {}
	
	virtual void Init() {};
	virtual void UpdateFrame() = 0;
	virtual void Shutdown() {};
};

class VTestFrameAction : public IVFrameAction
{
	vuint m_nCount;
public:
	virtual void Init();
	virtual void UpdateFrame();
	virtual void Shutdown();
};

class VRenderFrameAction : public IVFrameAction
{
public:
	VRenderFrameAction(VNativeWindowHandle in_Hwnd);
	
	virtual void Init();
	virtual void UpdateFrame();
	virtual void Shutdown();
	
	void SetShooting(v3d::scene::IVShooting* in_pShooting);
	v3d::graphics::IVDevice* GetDevice();
	
	void setSize(vuint width, vuint height);
	
private:
	vuint m_nWidth;
	vuint m_nHeight;
	vbool m_bResized;
	
	v3d::scene::IVShooting* m_pShooting;
	v3d::VSharedPtr<v3d::graphics::VOpenGLDevice> m_pDevice;
	HWND m_HWND;
};

class VView
{
public:
	VView();
	virtual ~VView();
	
	void Add(IVFrameAction* in_pAction);
	
	void Start();
	void Stop();
	
	bool IsRunning() const { return m_bIsRunning; }
		
	static VView* GetInstance();
//	VView(VNativeWindowHandle hwnd);
//	bool IsRendering() const;
	
//	void StartRendering();
//	void StopRendering();
//	void Render();
//	HWND GetHWND() const;
	
//	v3d::entity::VEntity& GetSceneRoot();

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
	
//	bool m_bIsRendering;
//	v3d::VSharedPtr<v3d::graphics::VOpenGLDevice> m_pDevice;
//	HWND m_HWND;
	
//	v3d::graphics::IVDevice::MeshHandle m_hMesh;
//	v3d::graphics::IVDevice::MaterialHandle m_hMaterial;

//	v3d::entity::VEntity m_SceneRoot;
	
//	VSharedPtr<v3d::scene::VShooting> m_pShooting;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor 
//-----------------------------------------------------------------------------
#endif // V3D_VVIEW_2005_07_15_H
