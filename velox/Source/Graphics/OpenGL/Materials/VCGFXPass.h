/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCGFXPASS_2005_08_17_H
#define V3D_VCGFXPASS_2005_08_17_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "../../DeviceBase/VRenderStateList.h"
#include "VCGFXState.h"

#include <V3d/OpenGL.h>
#include <CG/cg.h>
#include <CG/cgGL.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VCGFXMaterial;

#define V3D_CHECK_CG_ERROR()\
{\
	CGerror error = cgGetError();\
	if( CG_NO_ERROR != error )\
{\
	const char* message = cgGetErrorString(error);\
	V3D_THROW(VException, message);\
}\
}

/**
 */
class VCGFXPass : public VRenderStateList
{
public:
	VCGFXPass(
		RenderStateList in_DefaultStates, 
		CGpass in_Pass, CGeffect in_Effect, CGtechnique in_Technique,
		VCGFXMaterial* in_pMaterial);
	virtual ~VCGFXPass();

	static vbool CanRealize(const VRenderPass& in_Pass);

	void Bind(const VOpenGLDevice*);
	void Unbind();

private:
	CGpass m_Pass;
	CGeffect m_Effect;
	CGtechnique m_Technique;
	VCGFXMaterial* m_pMaterial;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VCGFXPASS_2005_08_17_H

