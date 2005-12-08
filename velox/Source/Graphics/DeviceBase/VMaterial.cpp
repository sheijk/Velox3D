#include "VMaterial.h"
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter/VEmptyPolicy.h>
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
	for(PassList::iterator pass = m_Passes.begin();
		pass != m_Passes.end();
		++pass)
	{
		VRangeIterator<IVParameter> params = (*pass)->Parameters();

		while(params.HasNext())
		{
			m_Parameters.push_back(&*params);
			++params;
		}
	}
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

//void VMaterial::SetParameter(ParamHandle in_Param, vfloat32 in_Value) const
//{
//}
//
//void VMaterial::SetParameter(ParamHandle in_Param, VVector4f in_Value) const
//{
//}

VRangeIterator<IVParameter> VMaterial::Parameters()
{
	return CreateDerefBeginIterator<IVParameter>(m_Parameters);
}

IVParameter* VMaterial::GetParameterByName(const std::string& in_strName)
{
	for(PassList::iterator pass = m_Passes.begin();
		pass != m_Passes.end();
		++pass)
	{
        IVParameter* foundPass = (*pass)->GetParameterByName(in_strName);

		if( foundPass != 0 )
			return foundPass;
	}

	return 0;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
