/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VUPDATEABLEPART_H
#define V3D_VUPDATEABLEPART_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Math.h>
#include <V3d/Entity/VPartBase.h>
#include <V3d/Entity.h>

#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
* A Update Interface for SceneGraph Animation
*
* @author lars
*/
class IVUpdateablePart : public VPartBase
{
public:

	IVUpdateablePart() {};
	virtual ~IVUpdateablePart() {};

	/** Update the Animation Part */
	virtual void Update(vfloat32 in_Seconds) = 0;

	static std::string GetDefaultId() { return "sgiu"; };
private:
};

/**
* add all IVUpdateablePart in a list and update the list 
*
* @author lars
*/
class VUpdateManagerPart : public VPartBase
{
public:

	VUpdateManagerPart();
	virtual ~VUpdateManagerPart();

	/** Update all the Animation Part */
	void Update(vfloat32 in_Seconds);

	/** 
	* When called, the part registers itself to it's parent and
	* activates its children
	*/
	virtual void Activate();

	/**
	* When called, the part unregisters itself from it's parent and
	* deactivates its children
	*/
	virtual void Deactivate();

	/** Register all IVUpdateableParts */
	void Register(IVUpdateablePart* in_pChild);

	/** Unregister all IVUpdateableParts */
	void Unregister(IVUpdateablePart* in_pChild);

	static std::string GetDefaultId();
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:
	std::list<IVUpdateablePart*> m_pChilds;
};
//-----------------------------------------------------------------------------
}} // namespace v3d::entity

V3D_TYPEINFO_WITHPARENT(v3d::entity::IVUpdateablePart, v3d::entity::IVPart);
V3D_TYPEINFO_WITHPARENT(v3d::entity::VUpdateManagerPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VUPDATEABLEPART_H
