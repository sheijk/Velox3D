#include "VXmlElement.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

VXMLElement::VXMLElement()
{

	m_Name = "NoName";
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
	return m_Name.c_str();
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

IVXMLAttribute* VXMLElement::GetAttribute(VStringParam Name)
{
	if(m_AttributeList.empty())
		V3D_THROW(VXMLException, "Attribute cannot be found. List empty");
	else
	{
		std::string NameCheck = Name;
		vuint i;
		for(i = 0; i<m_AttributeList.size(); i++)
		{
			IVXMLAttribute* att = m_AttributeList[i];
			std::string NameCheck2 = att->GetName();
			if(NameCheck == NameCheck2)
				return m_AttributeList[i];

		}
	}
	V3D_THROW(VXMLException, "Attribute cannot be found. Not in list");
}

void VXMLElement::AddAttribute(VXMLAttribute* p_Attribute)
{
	VXMLAttribute* Attribute = new VXMLAttribute;
	Attribute->SetName(p_Attribute->GetName());
	Attribute->SetValue(p_Attribute->GetValue());

	m_AttributeList.push_back(Attribute);
}

IVXMLAttribute* VXMLElement::NextAttribute()
{
	m_iPos++;

	if(m_iPos <= m_AttributeList.size())
		return m_AttributeList[m_iPos];
	else
		return NULL;
}

void VXMLElement::SetName(VStringParam Name)
{
	m_Name = Name;
}

IVXMLElement::AttributeIter VXMLElement::AttributeBegin()
{
typedef VSTLDerefIteratorPol<std::vector <VXMLAttribute*>::iterator, IVXMLAttribute> IterPol;
	return AttributeIter(new IterPol(m_AttributeList.begin()));
}

IVXMLElement::AttributeIter VXMLElement::AttributeEnd()
{
typedef VSTLDerefIteratorPol<std::vector <VXMLAttribute*>::iterator, IVXMLAttribute> IterPol;
	return AttributeIter(new IterPol(m_AttributeList.end()));
}

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------