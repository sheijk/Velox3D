/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VCGFXMaterial.h"
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>
#include <V3d/Core/RangeIter/VEmptyPolicy.h>

#include <string>

#include <V3d/Resource.h>

#include "../VTextureState.h"
#include "../Textures/VTexture2D.h"

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace std;

CGcontext VCGFXMaterial::s_Context = cgCreateContext();

VCGFXMaterial::VCGFXMaterial(VRenderStateList::RenderStateList in_DefaultStates, 
	const std::string& in_strSource)
{
	m_DefaultStates = in_DefaultStates;
	m_Effect = 0;
	m_Technique = 0;
	m_strSource = in_strSource;
	m_bNeedsUpdate = true;

	//CreateFromSource(in_strSource);
}

VCGFXMaterial::~VCGFXMaterial()
{
	Delete();
}

void VCGFXMaterial::CreateFromSource(const std::string& in_strSource)
{
	vout << "--- Creating cgfx material from source:\n" 
		<< in_strSource 
		<< "\n---" << vendl;

	cgGLRegisterStates(s_Context);
	V3D_CHECK_CG_ERROR();

	// initialize
	m_Effect = cgCreateEffect(s_Context, in_strSource.c_str(), 0);
	V3D_CHECK_CG_ERROR();
	//m_Effect = cgCreateEffectFromFile(s_Context, in_strSource.c_str(), 0);
	V3D_ASSERT(m_Effect != 0);

	// get a suitable technique
	m_Technique = cgGetFirstTechnique(m_Effect);
	V3D_CHECK_CG_ERROR();

	while( m_Technique )
	{
		cgValidateTechnique(m_Technique);
		V3D_CHECK_CG_ERROR();
		m_Technique = cgGetNextTechnique(m_Technique);
		V3D_CHECK_CG_ERROR();
	}

	// find a vaild technique
	m_Technique = cgGetFirstTechnique(m_Effect);
	V3D_CHECK_CG_ERROR();
	while( m_Technique != 0 && !cgIsTechniqueValidated(m_Technique) )
	{
		m_Technique = cgGetNextTechnique(m_Technique);
		V3D_CHECK_CG_ERROR();
	}

	if( m_Technique == 0 )
		V3D_THROW(VException, "Could not find a suitable technique");
		//V3D_THROWMSG(VException, "Could not find a suitable technique when "
		//	"loading the following cgfx source: <<<\n"
		//	<< in_strSource << "\n>>>\n");

	vout << "Effect using technique " << cgGetTechniqueName(m_Technique) << vendl;

	// get first pass TODO: use all passes (or specific pass)
	CGpass pass = cgGetFirstPass(m_Technique);
	V3D_CHECK_CG_ERROR();

	while( pass != 0 )
	{
		VCGFXPass* pPass = new VCGFXPass(m_DefaultStates, pass, m_Effect, m_Technique, this);
		m_Passes.push_back(VSharedPtr<VCGFXPass>(pPass));

		string passName = cgGetPassName(pass);

		vout << "\tpass " << passName << vendl;
		V3D_CHECK_CG_ERROR();

		pass = cgGetNextPass(pass);
		V3D_CHECK_CG_ERROR();
	}

	//TODO: get parameters
	CGparameter param = cgGetFirstEffectParameter(m_Effect);
	V3D_CHECK_CG_ERROR();

	vout << "parameters:" << vendl;

	while( param != 0 )
	{
		const CGtype paramType = cgGetParameterType(param);
		V3D_CHECK_CG_ERROR();

		const string paramName = cgGetParameterName(param);
		V3D_CHECK_CG_ERROR();

		vout << "\t" << paramName << " : " 
			<< cgGetTypeString(paramType);
		//<< " as " << cgGetParameterSemantic(param)
		//<< vendl;
		V3D_CHECK_CG_ERROR();

		const string semantic(cgGetParameterSemantic(param));
		V3D_CHECK_CG_ERROR();

		if( semantic == "MODELVIEWPROJECTION" )
		{
			m_AutoParameters.push_back(VSharedPtr<VCGFXParameterBase>(new VCGFXModelViewProjectionAutoParam(param)));

			vout << " as " << semantic;
		}
		else if( semantic == "" )
		{
			VSharedPtr<VCGFXParameterBase> pParam;

			switch(paramType)
			{
			case CG_FLOAT:
				{
					pParam.Assign(new VCGFXFloatParameter(param));
				} break;
			case CG_FLOAT4:
				{
					pParam.Assign(new VCGFXFloat4Parameter(param));
				} break;

			case CG_SAMPLER2D:
				{
					using namespace resource;

					//VResourceDataPtr<const VTextureState> pTexState = GetResourceData<VTextureState>("/data/moon.jpg");
					//VTexture2D* pTexture = reinterpret_cast<VTexture2D*>(pTexState->m_pTexture);
					VResourceDataPtr<const VTexture2D> pTexture = GetResourceData<VTexture2D>("/data/moon.jpg");

					GLenum texHandle = pTexture->GetTextureId();

					m_AutoParameters.push_back(VSharedPtr<VCGFXParameterBase>(new VCGFXTexture(param, texHandle)));
				} break;
			}

			// add parameter
			if( pParam.Get() != 0 )
				m_Parameters[paramName] = pParam;
		}

		vout << vendl;

		param = cgGetNextParameter(param);
		V3D_CHECK_CG_ERROR();
	}

	m_bNeedsUpdate = false;
}

void VCGFXMaterial::Delete()
{
	//TODO: release cgfx data
	m_AutoParameters.clear();
	m_Parameters.clear();
	m_Textures.clear();
	m_Passes.clear();
	cgDestroyEffect(m_Effect);
	m_Effect = 0;
	m_Technique = 0;
	m_strSource = "";
}

vbool VCGFXMaterial::SetShaderSource(const std::string& in_strSource)
{
	try
	{
		if( m_Effect != 0 )
			Delete();

		m_strSource = in_strSource;
		m_bNeedsUpdate = true;
		//CreateFromSource(in_strSource);
                
		return true;
	}
	catch(VException& e)
	{
		vout << e.GetErrorString() << vendl;
		return false;
	}
}

vuint VCGFXMaterial::PassCount() const
{
	if( m_bNeedsUpdate )
	{
		VCGFXMaterial* pNonConst = const_cast<VCGFXMaterial*>(this);
		pNonConst->CreateFromSource(m_strSource);
		pNonConst->m_bNeedsUpdate = false;
	}

	return static_cast<vuint>(m_Passes.size());
}

const IVPass& VCGFXMaterial::GetPass(vuint in_nNum) const
{
	if( m_bNeedsUpdate )
	{
		VCGFXMaterial* pNonConst = const_cast<VCGFXMaterial*>(this);
		pNonConst->CreateFromSource(m_strSource);
		pNonConst->m_bNeedsUpdate = false;
	}

	V3D_ASSERT(in_nNum < m_Passes.size());

	return *m_Passes[in_nNum];
}

void VCGFXMaterial::ApplyParameters(const VOpenGLDevice* in_pDevice)
{
	ApplyAutoParameters(in_pDevice);

	ParameterMap::iterator param = m_Parameters.begin();
	for( ; param != m_Parameters.end(); ++param)
	{
		param->second->Apply(in_pDevice);
	}
}

void VCGFXMaterial::UnapplyParameters()
{
	UnapplyAutoParameters();

	ParameterMap::iterator param = m_Parameters.begin();
	for( ; param != m_Parameters.end(); ++param)
	{
		param->second->Unapply();
	}
}

void VCGFXMaterial::ApplyAutoParameters(const VOpenGLDevice* in_pDevice)
{
	for(vuint num = 0; num < m_AutoParameters.size(); ++num) 
	{
		m_AutoParameters[num]->Apply(in_pDevice);
	}
}

void VCGFXMaterial::UnapplyAutoParameters()
{
	for(vuint num = 0; num < m_AutoParameters.size(); ++num) 
	{
		m_AutoParameters[num]->Unapply();
	}
}

VCGFXParameterBase* VCGFXMaterial::FindParameter(const std::string& in_strName) const
{
	ParameterMap::const_iterator paramIter = m_Parameters.find(in_strName);

	VCGFXParameterBase* pParam = 0;

	if( paramIter != m_Parameters.end() )
		pParam = const_cast<VCGFXParameterBase*>(paramIter->second.Get());

	return pParam;
}

void VCGFXMaterial::SetParameter(ParamHandle in_Param, vfloat32 in_Value) const
{
	VCGFXParameterBase* pParam = FindParameter(in_Param);

	if( pParam != 0 )
		pParam->Set(in_Value);

	//CGparameter param = cgGetNamedEffectParameter(m_Effect, in_Param.c_str());

	//if( param != 0 )
	//{
 //       cgSetParameter1f(param, in_Value);
	//	V3D_CHECK_CG_ERROR();
	//}
}

void VCGFXMaterial::SetParameter(ParamHandle in_Param, math::VVector4f in_Value) const
{
	VCGFXParameterBase* pParam = FindParameter(in_Param);

	if( pParam != 0 )
		pParam->Set(in_Value);

	//CGparameter param = cgGetNamedEffectParameter(m_Effect, in_Param.c_str());

	//if( param != 0 )
	//{
	//	cgSetParameter4f(param, in_Value[0], in_Value[1], in_Value[2], in_Value[3]);
	//	V3D_CHECK_CG_ERROR();
	//}
}

VRangeIterator<IVParameter> VCGFXMaterial::Parameters()
{
	V3D_THROW(VException, "Not yet implemented");
}

IVParameter* VCGFXMaterial::GetParameterByName(const std::string& in_strName)
{
	V3D_THROW(VException, "Not yet implemented");
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

