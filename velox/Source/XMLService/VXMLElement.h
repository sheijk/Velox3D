/*
 *
 *	created:	2003/06/26
 *	created:	26:6:2003   17:24
 *	filename: 	VXMLElement.h
 *	author:		insane
 *	
 *	purpose:	Implementation of the IVXMLElement
 */

#include <V3d/XML/IVXMLElement.h>
#include <V3d/Core/Wrappers/VString.h>
#include <string>
#include <vector>

#include "VXMLAttribute.h"

namespace v3d
{
namespace xml
{

class VXMLElement : public IVXMLElement
{
public:
	VXMLElement();
	~VXMLElement();
	virtual VStringRetVal GetName();
	virtual IVXMLAttribute* GetFirstAttribute();
	virtual IVXMLAttribute* NextAttribute();

	void AddAttribute(VXMLAttribute* p_Attribute);
	void SetName(VStringParam Name);


private:

	std::string m_Name;
	std::vector <VXMLAttribute*> m_AttributeList;
	vuint m_iPos;
	
	




};

}
}
