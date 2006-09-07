/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VXMLVisitor.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------
using namespace xml;
/**
 * standard c'tor
 */
VXMLVisitor::VXMLVisitor()
{
}

/**
 * d'tor
 */
VXMLVisitor::~VXMLVisitor()
{
}

void VXMLVisitor::OnElementClose(IVXMLElement* pElement)
{
}

void VXMLVisitor::OnElementOpen(IVXMLElement* pElement)
{
}

void VXMLVisitor::OnFileEnd()
{
}
void VXMLVisitor::OnComment(VStringParam pText)
{
}
void VXMLVisitor::OnText(VStringParam pText)
{
}

//-----------------------------------------------------------------------------
} // v3d
} // xml
//-----------------------------------------------------------------------------

