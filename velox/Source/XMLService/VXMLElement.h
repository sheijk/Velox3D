#ifndef V3D_VXMLELEMNT_H
#define V3D_VXMLELEMNT_H
//-----------------------------------------------------------------------------
#include <string>
#include <vector>
#include <V3d/XML/IVXMLElement.h>
#include <V3d/Core/Wrappers/VString.h>
#include <v3d/Core/Wrappers/VSTLDerefIteratorPol.h>
//-----------------------------------------------------------------------------
#include "VXMLAttribute.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------
/**
 * The IVXMLElement implementation
 * @author insane
 * @version 1.0
 */

class VXMLElement : public IVXMLElement
{
public:
	VXMLElement();
	~VXMLElement();
	virtual VStringRetVal GetName();
	virtual IVXMLAttribute* GetFirstAttribute();
	virtual IVXMLAttribute* NextAttribute();
	virtual IVXMLAttribute* GetAttribute(VStringParam Name);
	virtual AttributeIter AttributeBegin();
	virtual AttributeIter AttributeEnd();

	void AddAttribute(VXMLAttribute* p_Attribute);
	void SetName(VStringParam Name);


private:

	std::string m_Name;
	std::vector <VXMLAttribute*> m_AttributeList;
	vuint m_iPos;
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLELEMNT_H