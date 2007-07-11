/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VENTITY_2004_10_09_H
#define V3D_VENTITY_2004_10_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VEntityExceptions.h>
#include <V3d/Entity/IVPart.h>
#include <V3d/Entity/VNode.h>

#include <V3d/Core/RangeIter/VRangeIterator.h>

#include <map>
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
//using namespace v3d;

class VEntityHelper;

/**
 * The entity system provides a way for independent subsystems which need to 
 * interact in some way to share data without knowing about each other. Thus 
 * coupling between subsystems is reduced which makes it easier to exchange 
 * them when needed and for intance replace parts of Velox's default systems 
 * by application specific ones. Another benefit is the construction of 
 * dynamically combined object in a game editor by artists etc.
 *
 * The entity manager operates on the level of game objects called 'entities'. 
 * An entity is a collection of one or more 'parts'. Parts contain data of 
 * their subsystems and may provide interfaces to access them. The parts of an 
 * entity are independent from each other but may also access each other 
 * through unique names.
 *
 * Interaction between subsystems which don't know about each other happens 
 * through jointly used parts. For example a position part might be written to 
 * by the physics system and be read by the graphics system for display.
 *
 * Use an entity directly, instead
 *
 * @see v3d::entity::IVPart
 *
 * An entity is a container of entity parts. It owns it's parts once they are added.
 * Parts are told about each other when they are added.
 *
 * @author sheijk
 */
class VEntity : public VNode
{
public:
	VEntity();
	virtual ~VEntity();

	virtual void Save(xml::IVXMLElement& node);
	virtual void Load(const xml::IVXMLElement& in_Element);

	virtual const VTypeInfo& GetTypeInfo() const 
	{ return GetCompileTimeTypeInfo(this); }

private:
	VEntity(const VEntity&);
	void operator=(const VEntity&);
};

//-----------------------------------------------------------------------------
}
} // namespace v3d::entity
V3D_TYPEINFO_WITHPARENT( v3d::entity::VEntity, v3d::entity::VNode );
//-----------------------------------------------------------------------------
#endif // V3D_VENTITY_2004_10_09_H

