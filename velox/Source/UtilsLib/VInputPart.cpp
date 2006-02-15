#include <V3dLib/Utils/VInputPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VInputPart::VInputPart()
{
	m_pInputManager = 0;
}

VInputPart::~VInputPart()
{
}

void VInputPart::SetInputManager(input::IVInputManager* in_pInputManager)
{
	m_pInputManager = in_pInputManager;
}

input::IVInputManager* VInputPart::GetInputManager() const
{
	return m_pInputManager;
}

void VInputPart::Activate()
{
}

void VInputPart::Deactivate()
{
}

namespace {
	entity::VPartParser<VInputPart> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
