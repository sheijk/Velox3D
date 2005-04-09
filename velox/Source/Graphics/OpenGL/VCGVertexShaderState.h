#ifndef V3D_VCGVERTEXSHADERSTATE_2005_03_14_H
#define V3D_VCGVERTEXSHADERSTATE_2005_03_14_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "IVOpenGLRenderState.h"

#include <Cg/cg.h>

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

	VCGVertexShaderState(ShaderMode in_Mode);
	VCGVertexShaderState(VStringParam in_strFileName, CGprofile in_Profile);
	virtual ~VCGVertexShaderState();

	virtual void Apply() const;

	void AddAutoVar(const std::string& in_strName, AutoVariable in_Type);

private:
	void SetAutoVariables() const;
	void SetAutoVariable(const std::string& name, AutoVariable type) const;

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
