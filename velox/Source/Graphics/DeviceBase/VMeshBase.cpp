#include "VMeshBase.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

VMeshBase::VMeshBase(IVMaterial* in_pMaterial) : 
	m_pMaterial(in_pMaterial)
{
}

IVMaterial& VMeshBase::GetMaterial()
{
	return *m_pMaterial;
}

void VMeshBase::SetBuffers(std::vector<VMeshDescription::BufferHandle> in_Buffers)
{
	m_Buffers = in_Buffers;
}

std::vector<VMeshDescription::BufferHandle> VMeshBase::GetBuffers() const
{
	return m_Buffers;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
