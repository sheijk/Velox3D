#ifndef V3D_VXMLTEXT_09_11_2004_H
#define V3D_VXMLTEXT_09_11_2004_H
//-----------------------------------------------------------------------------
#include <V3d/XML/IVXMLText.h>
#include <V3d/Core/Wrappers/VString.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------
/**
 * The IVXMLText implementation
 * @author AcrylSword
 * @version 1.0
 */
class VXMLText : public IVXMLText
{
private:
	VString m_strText;

	VXMLText();

public:
	VXMLText(VStringParam in_strText);

	virtual void Visit(IVXMLVisitor& in_Visitor);

	VStringRetVal GetText();
	NodeType GetType();
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLTEXT_09_11_2004_H