#ifndef V3D_VXMLCOMMENT_09_11_2004_H
#define V3D_VXMLCOMMENT_09_11_2004_H
//-----------------------------------------------------------------------------
#include <V3d/XML/IVXMLComment.h>
#include <V3d/Core/Wrappers/VString.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------
/**
 * The IVXMLComment implementation
 * @author AcrylSword
 * @version 1.0
 */
class VXMLComment : public IVXMLComment
{
private:
	VString m_strComment;

	VXMLComment();

public:
	VXMLComment(VStringParam in_strComment);

	virtual VStringRetVal GetComment();
	virtual void Visit(IVXMLVisitor& in_Visitor);
	virtual NodeType GetType();
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLCOMMENT_09_11_2004_H