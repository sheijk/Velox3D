/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCGFXMATERIAL_2005_08_18_H
#define V3D_VCGFXMATERIAL_2005_08_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "VCGFXPass.h"

#include <V3d/Graphics/IVDevice.h>
#include <V3d/Graphics/VLight.h>
#include <V3d/Graphics/Geometry/Conversions.h>
#include "../VOpenGLDevice.h"

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
	virtual void Apply(const VOpenGLDevice* in_pDevice) = 0;

	virtual void Unapply() {}

	virtual vbool Set(vfloat32 in_fValue) { return false; }
	virtual vbool Set(const math::VVector4f& in_Value) { return false; }

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

	virtual void Apply(const VOpenGLDevice* in_pDevice)
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

	virtual void Apply(const VOpenGLDevice* in_pDevice)
	{
		cgSetParameter4f(m_Parameter, m_Value[0], m_Value[1], m_Value[2], m_Value[3]);
		V3D_CHECK_CG_ERROR();
	}

	virtual vbool Set(const math::VVector4f& in_Value)
	{
		m_Value = in_Value;
		return true;
	}

private:
	math::VVector4f m_Value;
};

class VCGFXModelViewProjectionAutoParam : public VCGFXParameterBase
{
public:
	VCGFXModelViewProjectionAutoParam(CGparameter in_Param)
	{
		m_Parameter = in_Param;
	}

	virtual void Apply(const VOpenGLDevice* in_pDevice)
	{
		cgGLSetStateMatrixParameter(m_Parameter, 
			CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
		V3D_CHECK_CG_ERROR();
	}
};

class VCGFXLightAutoParam : public VCGFXParameterBase
{
public:
	enum Property
	{
		Position,
		AmbientColor,
		DiffuseColor,
		SpecularColor
	};

	VCGFXLightAutoParam(CGparameter in_Param, IVDevice::LightId in_LightId, Property in_Component)
	{
		m_Parameter = in_Param;
		m_LightNum = in_LightId;
	}

	virtual void Apply(const VOpenGLDevice* in_pDevice)
	{
		// get light parameters
		if( in_pDevice->GetLight(m_LightNum) == 0 )
			return;

		const VLight& light = *in_pDevice->GetLight(m_LightNum);

		math::VVector4f data;

		switch(m_Component)
		{
		case Position:
			{
				math::VVector3f pos = light.GetPosition();
				data = ToVector4f(pos, 1.0f);
			} break;

		case AmbientColor:
			{
				data = ToVector4f(light.GetAmbientColor());
			} break;

		case DiffuseColor:
			{
				data = ToVector4f(light.GetDiffuseColor());
			} break;

		case SpecularColor:
			{
				data = ToVector4f(light.GetSpecularColor());
			} break;

		default:
			{
				// generate an error
				Property valid = Property(vuint(m_Component) + 1);
				V3D_ASSERT(m_Component == valid);
			} break;
		};

		// set parameter
		cgGLSetParameter4f(m_Parameter, data[0], data[1], data[2], data[3]);
	}

private:
	IVDevice::LightId m_LightNum;
	Property m_Component;
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

	virtual void Apply(const VOpenGLDevice* in_pDevice)
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
	~VCGFXMaterial();

	virtual vuint PassCount() const;
	virtual const IVPass& GetPass(vuint in_nNum) const;

	virtual void ApplyParameters(const VOpenGLDevice* in_pDevice);
	virtual void UnapplyParameters();

	virtual void SetParameter(ParamHandle in_Param, vfloat32 in_Value) const;
	virtual void SetParameter(ParamHandle in_Param, math::VVector4f in_Value) const;

	virtual vbool SetShaderSource(const std::string& in_strSource);

	virtual VRangeIterator<IVParameter> Parameters();
	IVParameter* GetParameterByName(const std::string& in_strName);
private:
	void ApplyAutoParameters(const VOpenGLDevice* in_pDevice);
	void UnapplyAutoParameters();
	VCGFXParameterBase* FindParameter(const std::string& in_strName) const;

	void AddTexture(CGparameter in_Param, GLenum in_Handle);

	void CreateFromSource(const std::string& in_strSource);
	void Delete();

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

	std::string m_strSource;
	vbool m_bNeedsUpdate;

	VRenderStateList::RenderStateList m_DefaultStates;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO_WITHPARENT(v3d::graphics::VCGFXMaterial, v3d::graphics::IVMaterial);
//-----------------------------------------------------------------------------
#endif // V3D_VCGFXMATERIAL_2005_08_18_H

