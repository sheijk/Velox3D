/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VXMLVISITOR_H
#define V3D_VXMLVISITOR_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/XML/IVXMLWriter.h>
#include <V3d/XML/IVXMLVisitor.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

class VXMLVisitor : public xml::IVXMLVisitor
{
public:
	VXMLVisitor();
	virtual ~VXMLVisitor();
	virtual void OnElementClose(xml::IVXMLElement* pElement);
	virtual void OnElementOpen(xml::IVXMLElement* pElement);
	virtual void OnFileEnd();
	virtual void OnComment(VStringParam pText);
	virtual void OnText(VStringParam pText);
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VXMLVISITOR_H

