/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VSUBAREACONTEXT_2007_05_17_H
#define V3D_VSUBAREACONTEXT_2007_05_17_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVRenderContext.h>
#include <V3d/Core/SmartPtr/VSharedPtr.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Renders to a subarea of the parent's context using glViewport
 *
 * Attention: untested and never used. Be careful! :)
 *
 * @author sheijk
 */
class VSubAreaContext : public IVRenderContext
{
public:
	VSubAreaContext(VSharedPtr<IVRenderContext> in_pParentContext);
	virtual ~VSubAreaContext();

	virtual void MakeCurrent();
	virtual void SwapBuffers();
	virtual VDisplaySettings* GetDisplaySettings();
	virtual IVRenderContext* CreateOffscreenContext(const VDisplaySettings* in_pDisplaySettings);

	void SetArea(vint left, vint top, vint right, vint bottom);
	void SetReallySwap(vbool yesno);
	vbool GetReallySwap();
private:
	VSharedPtr<IVRenderContext> m_pParentContext;

	/// propagate swap call to parent context yes/no
	vbool m_bReallySwap;

	vint m_nLeft;
	vint m_nTop;
	vint m_nRight;
	vint m_nBottom;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VSUBAREACONTEXT_2007_05_17_H

