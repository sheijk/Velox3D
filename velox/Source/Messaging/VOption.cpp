#include <V3d/Messaging/VOption.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VOption::VOption(const std::string& name)
{
	m_strName = name;
}

VOption::~VOption()
{
}

std::string VOption::GetName() const
{
	return m_strName;
}

void VOption::SetName(const std::string& in_Value)
{
	m_strName = in_Value;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------
