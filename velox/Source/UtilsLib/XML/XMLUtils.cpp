#include <V3d/XML/XMLUtils.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace xml {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

IVXMLElement* ToElement(IVXMLNode* in_pNode)
{
	if( in_pNode != 0 && in_pNode->GetType() == IVXMLNode::Element )
		return reinterpret_cast<IVXMLElement*>(in_pNode);
	else
		return 0;
}


//-----------------------------------------------------------------------------
}} // namespace v3d::xml
//-----------------------------------------------------------------------------
