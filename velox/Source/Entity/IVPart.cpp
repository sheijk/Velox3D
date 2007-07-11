/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Entity/IVPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>
#include <V3d/XML/IVXMLElement.h>
#include <V3d/Tags/VTagRegistry.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

void IVPart::Save(xml::IVXMLElement& node)
{
	VNode::Save( node );
}

void IVPart::Load(const xml::IVXMLElement& in_Node)
{
	VNode::Load( in_Node );
}

//-----------------------------------------------------------------------------
}} // namespace v3d
//-----------------------------------------------------------------------------

