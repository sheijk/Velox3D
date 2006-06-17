#include <V3d/Entity/IVPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

namespace {
	template<typename T>
	void Set(messaging::VMessage* msg, const std::string& name, const T& value)
	{
		if( msg->HasProperty(name) )
			msg->Set(name, utils::VStringValue(value));
		else
			msg->AddProperty(name, value);
	}
}

void IVPart::Send(
	const messaging::VMessage& in_Message, 
	messaging::VMessage* in_pAnswer)
{
	try 
	{
		OnMessage(in_Message, in_pAnswer);
	}
	catch(VException& e)
	{
		if( in_pAnswer != 0 )
		{
			Set(in_pAnswer, "catched-exception", "true");
			Set(in_pAnswer, "exception-message", e.GetErrorString());
			Set(in_pAnswer, "exception-file", e.GetErrorFile());
			Set(in_pAnswer, "exception-line", e.GetErrorLine());
		}
		else
		{
			vout << "Exception when sending message to part:\n"
				<< in_Message.ToString()
				<< e.ToString();
		}
	}
}

void IVPart::OnMessage(
	const messaging::VMessage& in_Message, 
	messaging::VMessage* in_pAnswer)
{
}

void IVPart::AttachTag(const tags::VTag& tag)
{
	if( ! HasTag(tag) )
	{
		m_Tags.push_back(&tag);
	}
}


void IVPart::RemoveTag(const tags::VTag& tag)
{
	for(std::vector<const tags::VTag*>::iterator tagIter = m_Tags.begin();
		tagIter != m_Tags.end();
		++tagIter)
	{
		if( (**tagIter) == tag )
		{
			m_Tags.erase(tagIter);
			break;
		}
	}
}

vbool IVPart::HasTag(const tags::VTag& tag) const
{
	for(std::vector<const tags::VTag*>::const_iterator tagIter = m_Tags.begin();
		tagIter != m_Tags.end();
		++tagIter)
	{
		if( **tagIter == tag )
			return true;
	}

	return false;
}

VRangeIterator<const tags::VTag> IVPart::Tags() const
{
	return CreateDerefBeginIterator<const tags::VTag>(m_Tags);
}

//-----------------------------------------------------------------------------
}} // namespace v3d
//-----------------------------------------------------------------------------
