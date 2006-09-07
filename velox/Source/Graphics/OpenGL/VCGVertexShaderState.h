/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCGVERTEXSHADERSTATE_2005_03_14_H
#define V3D_VCGVERTEXSHADERSTATE_2005_03_14_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "IVOpenGLRenderState.h"

#include <V3d/CG.h>

#include <string>
#include <list>
#include <iostream>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VCGVertexShaderState : public IVOpenGLRenderState
{
public:
	enum ShaderMode { DisablePixelShader, DisableVertexShader };

	enum AutoVariable 
	{
		AutoVarModelViewMatrix
	};

	VCGVertexShaderState(ShaderMode in_Mode, IVStateCategory* in_pCategory);
	VCGVertexShaderState(VStringParam in_strFileName, CGprofile in_Profile,
		IVStateCategory* in_pCategory);
	virtual ~VCGVertexShaderState();

	virtual void Apply() const;
	virtual const IVStateCategory* GetCategory() const;

	void AddAutoVar(const std::string& in_strName, AutoVariable in_Type);

private:
	void SetAutoVariables() const;
	void SetAutoVariable(const std::string& name, AutoVariable type) const;

	IVStateCategory* m_pCategory;

	static CGcontext m_Context;
	CGprogram m_Program;
	CGprofile m_Profile;

	CGparameter m_ModelViewParam;

	static CGprofile s_LastPixelProfile;
	static CGprofile s_LastVertexProfile;

	ShaderMode m_DisableMode;
	
	struct Autovar
	{
		AutoVariable variable;
		std::string name;
	};

	typedef std::list<Autovar> AutovarList;
	AutovarList m_AutoVariables;
};

std::istream& operator>>(std::istream& str, VCGVertexShaderState::AutoVariable& v);

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VCGVERTEXSHADERSTATE_2005_03_14_H

