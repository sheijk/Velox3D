#ifndef V3D_XMLUTILS_2005_02_15_H
#define V3D_XMLUTILS_2005_02_15_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/XML/IVXMLElement.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace xml {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Returns the given node as IVXMLELement if it is a valid IVXMLElement
 * Else 0 is returned
 *
 * @author sheijk
 */
#pragma deprecated(ToElement)
IVXMLElement* ToElement(IVXMLNode* in_pNode);

/**
 * Returns true iff the given element has an attribute with the given
 * name and value
 *
 * @param IVXMLElement* in_pElement The element
 * @param VStringParam in_strAttribName The name of the attribute
 * @param const T& in_ExpectedValue The value to be compared to
 *
 * @author sheijk
 */
template<typename T>
vbool HasAttributeWithValue(
							IVXMLElement* in_pElement, 
							VStringParam in_strAttribName,
							const T& in_ExpectedValue);

//-----------------------------------------------------------------------------
#include "XMLUtils.inl"
//-----------------------------------------------------------------------------
}} // namespace v3d::xml
//-----------------------------------------------------------------------------
#endif // V3D_XMLUTILS_2005_02_15_H
