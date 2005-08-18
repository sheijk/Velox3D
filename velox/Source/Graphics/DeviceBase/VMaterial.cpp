#include "VMaterial.h"
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
VMaterial::VMaterial(const PassList& in_Passes)
	:
	m_Passes(in_Passes.begin(), in_Passes.end())
{
}

/**
 * d'tor
 */
VMaterial::~VMaterial()
{
}

vuint VMaterial::PassCount() const
{
	return vuint(m_Passes.size());
}

const IVPass& VMaterial::GetPass(vuint in_nNum) const
{
	return *m_Passes[in_nNum];
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
