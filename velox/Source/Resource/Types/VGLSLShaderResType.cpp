#include "VGLSLShaderResType.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VGLSLShaderResType::VGLSLShaderResType()
{
}

/**
 * d'tor
 */
VGLSLShaderResType::~VGLSLShaderResType()
{
}

VRangeIterator<VTypeInfo> VGLSLShaderResType::CreatedTypes()
{
	return CreateSingleValueIterator<VTypeInfo>(&GetTypeInfo<VGLSLShader>());
}

vbool VGLSLShaderResType::Generate(
	resource::VResource* in_pResource, 
	VTypeInfo in_Type)
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
