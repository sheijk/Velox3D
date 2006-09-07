/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVXMLTEXT_08_31_04_H
#define V3D_IVXMLTEXT_08_31_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/XML/IVXMLNode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------
/**
 * The XML Text interface
 * @author insane/acrylsword/sheijk
 * @version 2.0
 */
class IVXMLText : public IVXMLNode
{
public:
	/** Returns the text */
	virtual VStringRetVal GetText() const = 0;

	/** Change the text */
	virtual void SetText(VStringParam in_strText) = 0;

	virtual	IVXMLElement* ToElement() { return 0; }
	virtual IVXMLComment* ToComment() { return 0; }
	virtual IVXMLText* ToText() { return this; }
};

//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLTEXT_08_31_04_H
