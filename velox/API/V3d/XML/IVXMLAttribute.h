/*
 *
 *	created:	2003/06/24
 *	created:	24:6:2003   18:04
 *	filename: 	IVXMLAttribute.h
 *	author:		insane
 *	
 *	purpose:	Maps an xml attribute
 */

#ifndef IVXMLATTRIBUTE_H
#define IVXMLATTRIBUTE_H

#include <V3d/Core/VTypes.h>

namespace v3d{
namespace xml{

//TODO: stil an den restlichen velox source anpassen, vor allem die doku
// im javadoc style (sheijk)
class IVXMLAttribute
{
public:

	virtual VStringRetVal GetName() = 0;
	virtual VStringRetVal GetValue() = 0;

};

//TODO: hier unbedingt // namespace xml hinterschreiben, sonst sieht
//man nicht wozu die schliessende klammer gehoert
}
}



#endif

