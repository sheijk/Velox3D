#ifndef V3D_IVXMLVISITOR_H
#define V3D_IVXMLVISITOR_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/XML/IVXMLDeclaration.h>
#include <v3d/XML/IVXMLComment.h>
#include <v3d/XML/IVXMLText.h>
#include <v3d/XML/IVXMLUnknown.h>
#include <v3d/XML/IVXMLElement.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------

/**
 * An interface used by IVXMLDocument.
 * Use a class implementing this interface for parsing XML files. IVXMLDocument
 * does not store the data for you. Instead use IVXMLVisitor to generate the data
 * you need.
 */
class IVXMLVisitor
{
public:
	virtual void OnDeclaration(const IVXMLDeclaration* in_pDecl) = 0;
	virtual void OnComment(const IVXMLComment* in_pComment) = 0;
	virtual void OnElement(const IVXMLElement* in_pElement) = 0;
	virtual void OnText(const IVXMLText* in_pText) = 0;
	virtual void OnUnknown(const IVXMLUnknown* in_pUnknown) = 0;
};

//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLVISITOR_H