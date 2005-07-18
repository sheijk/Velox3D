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

namespace v3d { namespace graphics {
	class VOpenGLDevice;
}}

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

typedef int VNativeWindowHandle;

class VView {
public:
	VView(VNativeWindowHandle hwnd);
	virtual ~VView();
	
	void StartRendering();
	void StopRendering();
	
	bool IsRunning() const { return m_bIsRunning; }
	bool IsRendering() const;
	
	void Render();
	HWND GetHWND() const;
	
	v3d::entity::VEntity& GetSceneRoot();

private:
#ifndef SWIG
	static void GLFWCALL RenderLoop(void* arg);
#endif

	bool m_bIsRendering;
	bool m_bIsRunning;
	GLFWthread m_Thread;
	HWND m_HWND;
	v3d::VSharedPtr<v3d::graphics::VOpenGLDevice> m_pDevice;
	
	v3d::graphics::IVDevice::MeshHandle m_hMesh;
	v3d::graphics::IVDevice::MaterialHandle m_hMaterial;

	v3d::entity::VEntity m_SceneRoot;
	
	VSharedPtr<v3d::scene::VShooting> m_pShooting;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor 
//-----------------------------------------------------------------------------
#endif // V3D_VVIEW_2005_07_15_H
