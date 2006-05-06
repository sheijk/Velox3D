#include "VShaderCategory.h"
//-----------------------------------------------------------------------------

#include <V3d/Resource.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

using namespace resource;

namespace {
	const std::string FRAGMENT_PROGRAM_STATE_NAME = "fragment-program";
	const std::string VERTEX_PROGRAM_STATE_NAME = "vertex-program";

	std::string GetResFromState(
		const VRenderPass& pass, 
		const std::string& stateName)
	{
		const VState* pState = pass.GetStateByName(stateName.c_str());

		if( pState == 0 )
			return "";

		VStateParameter param = pState->GetParameterByName("res");
		std::string res = param.GetValue<std::string>();

		return res;
	}

	std::string GetSourceFromState(
		const VRenderPass& pass, 
		const std::string& stateName)
	{
		const VState* pState = pass.GetStateByName(stateName.c_str());

		if( pState == 0 )
			return "";

		VStateParameter param = pState->GetParameterByName("res");
		std::string res = param.GetValue<std::string>();

		std::string source;

		if( res.empty() )
		{
			source = pState->GetParameterByName("source").GetValue<std::string>();
		}
		else
		{
			source = GetResourceData<VTextFile>(res.c_str())->GetContent();
		}

		return source;
	}
}

/**
 * standard c'tor
 */
VShaderCategory::VShaderCategory()
{
}

/**
 * d'tor
 */
VShaderCategory::~VShaderCategory()
{
}

VShaderState* VShaderCategory::CreateState(const VRenderPass& in_Pass)
{
	if( CanCreateStateFrom(in_Pass) )
	{
		// get fragment and vertex shader resource name and load them
		const std::string fragmentSource = GetSourceFromState(in_Pass, FRAGMENT_PROGRAM_STATE_NAME);
		const std::string vertexSource = GetSourceFromState(in_Pass, VERTEX_PROGRAM_STATE_NAME);

		VGLSLShader* pShader = new VGLSLShader(vertexSource, fragmentSource);
		VShaderState* pShaderState = new VShaderState(pShader, this);

		VDepthState depthState;
		depthState.Parse(in_Pass);
		pShaderState->SetDepthState(depthState);

		return pShaderState;
	}
	else
	{
		// create a shader state which will apply no shader
		return new VShaderState(0, this);
	}
}

vbool VShaderCategory::CanCreateStateFrom(const VRenderPass& in_Pass)
{
	return in_Pass.GetStateByName(VERTEX_PROGRAM_STATE_NAME.c_str()) != 0 &&
		in_Pass.GetStateByName(FRAGMENT_PROGRAM_STATE_NAME.c_str()) != 0;
}

std::vector<std::string> VShaderCategory::GetResourceDependencies(
	const VRenderPass& in_Pass)
{
	std::vector<std::string> resources;

	resources.push_back(GetResFromState(in_Pass, FRAGMENT_PROGRAM_STATE_NAME));
	resources.push_back(GetResFromState(in_Pass, VERTEX_PROGRAM_STATE_NAME));

	return resources;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
