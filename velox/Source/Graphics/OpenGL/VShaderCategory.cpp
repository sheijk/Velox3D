#include "VShaderCategory.h"
//-----------------------------------------------------------------------------

#include <V3d/Resource.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

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

using namespace resource;

VShaderState* VShaderCategory::CreateState(const VRenderPass& in_Pass)
{
	if( CanCreateStateFrom(in_Pass) )
	{
		//TODO: get fragment and vertex shader from resource system

		// get fragment and vertex shader resource name and load them
		const std::string fragmentResource = GetResFromState(in_Pass, FRAGMENT_PROGRAM_STATE_NAME);
		const std::string fragmentSource = 
			GetResourceData<VTextFile>(fragmentResource.c_str())->GetContent();

		const std::string vertexResource = GetResFromState(in_Pass, VERTEX_PROGRAM_STATE_NAME);
		const std::string vertexSource =
			GetResourceData<VTextFile>(vertexResource.c_str())->GetContent();

		VGLSLShader* pShader = new VGLSLShader(vertexSource, fragmentSource);
		VShaderState* pShaderState = new VShaderState(pShader, this);
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

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
