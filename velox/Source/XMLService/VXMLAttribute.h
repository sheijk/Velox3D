/*
 *
 *	created:	2003/06/24
 *	created:	24:6:2003   18:11
 *	filename: 	VXMLAttribute.h
 *	author:		insane
 *	
 *	purpose:	Implements the IVXMLAttribute Interface
 */


#ifndef VXMLATTRIBUTE_H
#define VXMLATTRIBUTE_H

#include <V3d/XML/IVXMLAttribute.h>
#include <V3d/Core/Wrappers/VString.h>
#include <string>



using namespace v3d;

namespace v3d{
namespace xml{

class VXMLAttribute : public IVXMLAttribute
{
public:

	VXMLAttribute();
	VXMLAttribute(VStringParam Name, VStringParam Value);


	virtual VStringRetVal GetName();
	virtual VStringRetVal GetValue();
	
	void SetName(VStringParam Name);
	void SetValue(VStringParam Value);

private:

	std::string m_Name;
	std::string m_Value;

};

}
}


#endif
