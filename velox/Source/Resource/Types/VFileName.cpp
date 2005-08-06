#include <V3d/Resource/Types/VFileName.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VFileName::VFileName(VStringParam in_strName)
{
	m_strName = in_strName;
}

/**
 * d'tor
 */
VFileName::~VFileName()
{
}

const std::string& VFileName::AsString() const
{
	return m_strName;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------