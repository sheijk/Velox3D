#ifndef V3D_VCGFXMATERIAL_2005_08_18_H
#define V3D_VCGFXMATERIAL_2005_08_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "VCGFXPass.h"

#include <V3d/Math/VVector.h>
#include <V3d/Core/VIOStream.h>

#include <vector>
#include <map>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

//	vout << "[" << __FILE__ << "|" << __LINE__ << "] " << message << vendl;

class VCGFXParameterBase
{
public:
	virtual void Apply() = 0;

	virtual void Unapply() {}

	virtual vbool Set(vfloat32 in_fValue) { return false; }
	virtual vbool Set(const VVector4f& in_Value) { return false; }

protected:
    CGparameter m_Parameter;    
};

class VCGFXFloatParameter : public VCGFXParameterBase
{
public:
	VCGFXFloatParameter(CGparameter in_Param)
	{
		m_Parameter = in_Param;
	}

	virtual void Apply()
	{
		cgSetParameter1f(m_Parameter, m_fValue);
		V3D_CHECK_CG_ERROR();
	}

	virtual vbool Set(vfloat32 in_fValue)
	{
		m_fValue = in_fValue;
		return true;
	}

private:
	vfloat32 m_fValue;
};

class VCGFXFloat4Parameter : public VCGFXParameterBase
{
public:
	VCGFXFloat4Parameter(CGparameter in_Param)
	{
		m_Parameter = in_Param;
	}

	virtual void Apply()
	{
		cgSetParameter4f(m_Parameter, m_Value[0], m_Value[1], m_Value[2], m_Value[3]);
		V3D_CHECK_CG_ERROR();
	}

	virtual vbool Set(const VVector4f& in_Value)
	{
		m_Value = in_Value;
		return true;
	}

private:
	VVector4f m_Value;
};

class VCGFXModelViewProjectionAutoParam : public VCGFXParameterBase
{
public:
	VCGFXModelViewProjectionAutoParam(CGparameter in_Param)
	{
		m_Parameter = in_Param;
	}

	virtual void Apply()
	{
		cgGLSetStateMatrixParameter(m_Parameter, 
			CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
		V3D_CHECK_CG_ERROR();
	}
};

class VCGFXTexture : public VCGFXParameterBase
{
public:
	VCGFXTexture(CGparameter in_Param, GLenum in_TextureHandle)
	{
		m_Parameter = in_Param;
		m_TextureHandle = in_TextureHandle;

		cgGLSetupSampler(m_Parameter, m_TextureHandle);
		V3D_CHECK_CG_ERROR();
		cgGLSetTextureParameter(m_Parameter, m_TextureHandle);
		V3D_CHECK_CG_ERROR();
	}

	virtual void Apply()
	{
		cgGLEnableTextureParameter(m_Parameter);
		V3D_CHECK_CG_ERROR();
	}

	virtual void Unapply()
	{
		cgGLDisableTextureParameter(m_Parameter);
		V3D_CHECK_CG_ERROR();
	}

private:
	CGparameter m_Parameter;
	GLenum m_TextureHandle;
};

class VCGFXMaterial : public IVMaterial
{
public:
	VCGFXMaterial(VRenderStateList::RenderStateList in_DefaultStates, const std::string& in_strSource);

	virtual vuint PassCount() const;
	virtual const IVPass& GetPass(vuint in_nNum) const;

	void ApplyParameters();
	void UnapplyParameters();

	virtual void SetParameter(ParamHandle in_Param, vfloat32 in_Value) const;
	virtual void SetParameter(ParamHandle in_Param, VVector4f in_Value) const;

private:
	void ApplyAutoParameters();
	void UnapplyAutoParameters();
	VCGFXParameterBase* FindParameter(const std::string& in_strName) const;

	void AddTexture(CGparameter in_Param, GLenum in_Handle);

	//enum AutoParameterType
	//{
	//	APModelViewProjectionMatrix
	//};

	//struct AutoParameter
	//{
	//	CGparameter param;
	//	AutoParameterType type;
	//};

	//typedef std::vector<AutoParameter> AutoParamVector;
	typedef std::vector< VSharedPtr<VCGFXParameterBase> > AutoParamVector;
	typedef std::map< std::string, VSharedPtr<VCGFXParameterBase> > ParameterMap;

	AutoParamVector m_AutoParameters;
	ParameterMap m_Parameters;

	std::vector< VSharedPtr<VCGFXTexture> > m_Textures;

	static CGcontext s_Context;

	std::vector< VSharedPtr<VCGFXPass> > m_Passes;
	CGeffect m_Effect;
	CGtechnique m_Technique;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO_WITHPARENT(v3d::graphics::VCGFXMaterial, v3d::graphics::IVMaterial);
//-----------------------------------------------------------------------------
#endif // V3D_VCGFXMATERIAL_2005_08_18_H
