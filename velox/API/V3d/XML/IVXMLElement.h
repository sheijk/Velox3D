/*
 *
 *	created:	2003/06/26
 *	created:	26:6:2003   17:18
 *	filename: 	IVXMLElement.h
 *	author:		insane
 *	
 *	purpose:	Interface for a xml element
 */


#ifndef IVXMLELEMNT_H
#define IVXMLELEMNT_H

#include <V3d/Core/VTypes.h>
#include <V3d/XML/IVXMLAttribute.h>

namespace v3d{
namespace xml{


//TODO: doku (sheijk)
class IVXMLElement
{
public:

	virtual VStringRetVal GetName() = 0;
	//TODO: warum keine iteratoren? was ist wenn man die elemente
	// 2x durchlaufen will? (sheijk)
	virtual IVXMLAttribute* GetFirstAttribute() = 0;
	virtual IVXMLAttribute* NextAttribute() = 0;
	virtual IVXMLAttribute* GetAttribute(VStringParam Name) = 0;


};

}
}




#endif
