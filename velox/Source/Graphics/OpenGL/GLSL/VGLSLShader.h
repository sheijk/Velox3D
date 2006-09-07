/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */


#ifndef V3D_VGLSLSHADER_2005_11_26_H
#define V3D_VGLSLSHADER_2005_11_26_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/SmartPtr/VSharedPtr.h>

#include <V3d/Graphics/IVShader.h>

#include "VGLSLParameter.h"
#include <V3d/OpenGL.h>
#include <V3d/Graphics/GraphicsExceptions.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>

#include <string>
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VGLSLTextureParameter;

V3D_DECLARE_EXCEPTION(VGLSLException, VGraphicException);

/**
 */
class VGLSLShader : public IVShader
{
public:
	VGLSLShader(
		const std::string& in_strVertexSource, 
		const std::string& in_strFragmentSource);
	virtual ~VGLSLShader();

	virtual void Bind();
	virtual void Unbind();

	VSharedPtr<IVParameter> GetParameter(VStringParam in_strName);

	VRangeIterator<IVParameter> Parameters();

	static vbool IsGLSLSupported();

private:
	vbool CompileErrorOccured(GLhandleARB in_hProgram, std::string* in_pstrErrorMesssage);
	vbool LinkErrorOccured(GLhandleARB in_hProgram, std::string* in_pstrErrorMesssage);
	IVParameter* GetActiveUniformParameter(vuint in_nIndex);

	GLhandleARB m_hVertexShader;
	GLhandleARB m_hFragmentShader;
	GLhandleARB m_hProgram;
	vuint m_nTextureCount;

	typedef std::vector<VSharedPtr<IVParameter> > ParamContainer;
	ParamContainer m_Parameters;

	std::vector<VGLSLTextureParameter*> m_Textures;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VGLSLSHADER_2005_11_26_H

