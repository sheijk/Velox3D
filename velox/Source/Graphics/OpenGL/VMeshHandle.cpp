#include "VMeshHandle.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VMeshHandle::VMeshHandle(VMeshBase* in_hBuffer)
{
	m_pMesh = in_hBuffer;
}

/**
 * d'tor
 */
VMeshHandle::~VMeshHandle()
{
}

VMeshBase* VMeshHandle::GetGLMesh() const
{
	return m_pMesh;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
