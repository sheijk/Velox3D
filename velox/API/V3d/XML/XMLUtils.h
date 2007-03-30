/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_XMLUTILS_2005_02_15_H
#define V3D_XMLUTILS_2005_02_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/XML/IVXMLElement.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace xml {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Returns the given node as IVXMLELement if it is a valid IVXMLElement
 * Else 0 is returned. (Use IVXMLNode::ToElement instead)
 *
 * @deprecated
 *
 * @author sheijk
 */
V3D_DEPRECATED IVXMLElement* ToElement(IVXMLNode* in_pNode);

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

/**
 * Reads out the given xml element and writes it to an xml file
 */
void SaveXMLElementToFile(IVXMLElement* in_pELement, VStringParam in_strFileName);

/**
 * Same as above but writes to a file without using the vfs
 */
void SaveXMLElementToFileNoVFS(IVXMLElement* in_pElement, VStringParam in_strFileName);

std::string XMLElementToString(IVXMLElement* in_pElement);

//-----------------------------------------------------------------------------
#include "XMLUtils.inl"
//-----------------------------------------------------------------------------
}} // namespace v3d::xml
//-----------------------------------------------------------------------------
#endif // V3D_XMLUTILS_2005_02_15_H

