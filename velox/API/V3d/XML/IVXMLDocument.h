#ifndef V3D_IVXMLDOCUMENT_H
#define V3D_IVXMLDOCUMENT_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/XML/IVXMLVisitor.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------

/**
 * Represents an XML file. Use a IVXMLVisitor to access the XML Data.
 */
class IVXMLDocument
{

public:
	virtual void Load(const char* in_pcFileName) = 0;
	virtual void Parse(IVXMLVisitor* in_pVisitor) const = 0;
};

//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLDOCUMENT_H
