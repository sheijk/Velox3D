/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VPART_2004_10_09_H
#define V3D_VPART_2004_10_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VEntityExceptions.h>
#include <V3d/Entity/VPartDependency.h>
#include <V3d/Entity/VNode.h>

#include <V3d/Messaging/VMessage.h>
#include <V3d/Tags/VTag.h>

#include <V3d/XML/IVXMLElement.h>

#include <vector>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * A part is an independent part of an entity. Derive classes from IVPart to
 * create custom parts for your subsystems. If a part is dependant from other
 * parts, override <code>TellNeighbourParts</code>. Your part has to register
 * itself to and from it's subsystem when Activate/Deactivate are called.
 * The part may only be registered to it's subsystem between calls to Activate
 * and Deactivate. Outside this interval the part has to be unknown to any 
 * other systems because it might be deleted any time without further notice
 *
 * @see v3d::entity::VEntity
 * @see v3d::entity::VUnconnectedPartAdapter
 * @see v3d::entity::VPartBaseAdapter
 * 
 * @author sheijk
 */
class IVPart : public VNode
{
public:
	virtual ~IVPart() {}

	virtual void Save(xml::IVXMLElement& node);
	virtual void Load(const xml::IVXMLElement& node);
};

typedef IVPart VPart;

//-----------------------------------------------------------------------------
}
  //V3D_TYPEINFO(v3d::entity::IVPart);

template<> class InitTypeInfo< v3d::entity::IVPart >
	{
	public:
		void operator()(VTypeInfo* out_pTypeInfo)
		{
		  out_pTypeInfo->SetName( "v3d::entity::IVPart" );
		}
	};
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPART_2004_10_09_H

