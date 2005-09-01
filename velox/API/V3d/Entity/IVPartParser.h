#ifndef V3D_IVPARTPARSER_2005_07_18_H
#define V3D_IVPARTPARSER_2005_07_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>
#include <V3dLib/Utils/VFourCC.h>
#include <V3d/XML/IVXMLElement.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Parses an xml file/node and creates a IVPart from it
 *
 * @author sheijk
 */
class IVPartParser
{
public:
	virtual ~IVPartParser() {}

	/** Returns the type for which parts are parsed */
	virtual std::string GetType() const = 0;

	/** 
	 * Parse the xml node and create a part from it 
	 *
	 * @throws VPartParseException if an error occured
	 */
	virtual VSharedPtr<IVPart> Parse(xml::IVXMLElement& in_Node) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_IVPARTPARSER_2005_07_18_H
