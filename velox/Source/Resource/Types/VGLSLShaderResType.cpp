/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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

