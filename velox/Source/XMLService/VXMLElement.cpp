#include "VXmlElement.h"
#include <v3d/Core/Wrappers/VSTLDerefIteratorPol.h> 
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/MemManager.h>

#include <sstream>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

VXMLElement::VXMLElement()
{
	m_strName = "NoName";
	m_iPos = 0;
}

VXMLElement::VXMLElement(VStringParam in_strName)
{
	m_strName = in_strName;
	m_iPos = 0;
}

VXMLElement::~VXMLElement()
{
	vuint i;
	for(i=0; i<m_AttributeList.size(); i++)
		delete m_AttributeList[i];

}

VStringRetVal VXMLElement::GetName()
{
	return m_strName;
}

IVXMLAttribute* VXMLElement::GetFirstAttribute()
{
	if(m_AttributeList.empty())
		return NULL;
	else 
	{
		m_iPos = 0;
		return m_AttributeList[0];
	}
}

IVXMLAttribute* VXMLElement::GetAttribute(VStringParam in_strName)
{
	VString name(in_strName);

	for(vuint i = 0; i<m_AttributeList.size(); i++)
	{
		if(name == m_AttributeList[i]->GetName() )
			return m_AttributeList[i];
	}

	std::stringstream message;
	message << "Could not find attribute '" << in_strName << "' in xml "
		<< "element '" << m_strName << "'";

	V3D_THROW(VXMLAttributeException, message.str().c_str());
}

/**
 * Adds a new VXMLAttribute to this element. The <code>in_pAttribute
 * </code> parameter must be unequal to 0. If it equals zero you will
 * get an assertion. :)
 * 
 * @param in_pAttribute A pointer to the attribute that is added
 *	    				to this element. Must be not zero.
 * @author ins/acrylsword
 * @see VXMLAttribute
 */
void VXMLElement::AddAttribute(VXMLAttribute* in_pAttribute)
{
	V3D_ASSERT(in_pAttribute != 0);
	
	m_AttributeList.push_back(in_pAttribute);
}

IVXMLAttribute* VXMLElement::NextAttribute()
{
	m_iPos++;

	if(m_iPos <= m_AttributeList.size())
		return m_AttributeList[m_iPos];
	else
		return NULL;
}

void VXMLElement::SetName(const VStringParam in_strName)
{
	m_strName = in_strName;
}

void VXMLElement::Visit(IVXMLVisitor& in_Visitor)
{
	in_Visitor.OnElementOpen(this);
		VisitChildren(in_Visitor);
	in_Visitor.OnElementClose(this);
}

void VXMLElement::VisitChildren(IVXMLVisitor& in_Visitor)
{
	for (std::list<IVXMLNode*>::iterator iter = m_Childs.begin();
		 iter != m_Childs.end();
		 ++iter)
	{
		(*iter)->Visit(in_Visitor);
	}
}

IVXMLNode::NodeType VXMLElement::GetType()
{
	return Element;
}

void VXMLElement::AddChild(IVXMLNode* in_pChild)
{
	V3D_ASSERT(in_pChild != 0);

	m_Childs.push_back(in_pChild);
}

IVXMLElement::NodeIter VXMLElement::ChildBegin()
{
	typedef VSTLDerefIteratorPol<std::list<IVXMLNode*>::iterator,
		IVXMLNode> IterPol;

	return NodeIter(new IterPol(m_Childs.begin()));
}

IVXMLElement::NodeIter VXMLElement::ChildEnd()
{
	typedef VSTLDerefIteratorPol<std::list<IVXMLNode*>::iterator,
		IVXMLNode> IterPol;

	return NodeIter(new IterPol(m_Childs.end()));
}

IVXMLElement::AttributeIter VXMLElement::AttributeBegin()
{
typedef VSTLDerefIteratorPol<std::vector <VXMLAttribute*>::iterator,
		IVXMLAttribute> IterPol;

	return AttributeIter(new IterPol(m_AttributeList.begin()));
}

IVXMLElement::AttributeIter VXMLElement::AttributeEnd()
{
typedef VSTLDerefIteratorPol<std::vector <VXMLAttribute*>::iterator,
		IVXMLAttribute> IterPol;

	return AttributeIter(new IterPol(m_AttributeList.end()));
}

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------