/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Entity/VEntity.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>

#include <V3d/Core/RangeIter/VSTLAccessorRangePolicy.h>
#include <V3d/XML/IVXMLElement.h>
#include <V3d/Entity/VGenericPartParser.h>

#include <sstream>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::utils;


VEntity::VEntity()
{
}

VEntity::~VEntity()
{
}
//
//VSharedPtr<VNode> VEntity::GetPartById(const std::string& in_Id)
//{
//	VRangeIterator< VSharedPtr<VNode> > node = ChildPtrIterator();
//	while( node.HasNext() )
//	{
//		if( (*node)->GetTypeInfo().CanBeCastedTo(in_Id) )
//			return *node;
//
//		++node;
//	}
//
//	return VSharedPtr<VNode>(0);
//}

//VSharedPtr<VEntity> VEntity::GetChildWithName(const std::string& in_strName)
//{
//	for(EntityContainer::iterator childIter = m_Entities.begin();
//		childIter != m_Entities.end();
//		++childIter)
//	{
//		if( (*childIter)->GetName() == in_strName )
//			return *childIter;
//	}
//
//	return VSharedPtr<VEntity>(0);
//}

void VEntity::Save(xml::IVXMLElement& node)
{
	VNode::Save( node );
}

void VEntity::Load(const xml::IVXMLElement& in_Element)
{
	VNode::Load( in_Element );
}

V3D_REGISTER_PART_PARSER(VEntity);
//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------


