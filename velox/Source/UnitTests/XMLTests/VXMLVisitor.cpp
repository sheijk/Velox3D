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
