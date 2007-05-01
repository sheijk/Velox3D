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

#include <V3d/Messaging/VMessage.h>
#include <V3d/Tags/VTag.h>

#include <V3d/xml/IVXMLElement.h>

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
class IVPart
{
public:
	typedef VPartDependency Dependency;
	typedef VPartDependency::Location Location;

	virtual ~IVPart() {}

	/** 
	* When called, the part has to register itself to it's subsystem 
	*/
	virtual void Activate() = 0;

	/**
	* When called, the part has to unregister itself from it's subsystem
	*/
	virtual void Deactivate() = 0;

	/** Connect to another entity part */
	virtual void Connect(
		VPartDependency::Location in_Location, 
		const std::string& in_Id, 
		IVPart& in_Part)
	{}

	/** 
	* Notify the part that another connected part has been removed 
	* The disconnected part might be deleted right after this call. Thus all
	* references to it must be reset to null
	*/
	virtual void Disconnect(
		VPartDependency::Location in_Location,
		const std::string& in_Id,
		IVPart& in_Part)
	{}

	/** 
	* The part can activated and used if this function returns true. (all
	* dependencies must be fulfilled etc.)
	*/
	virtual vbool IsReady() const = 0;

	/** Return the number of dependencies */
	virtual vuint DependencyCount() const = 0;

	/** Return information about the n-th dependency */
	virtual VPartDependency GetDependencyInfo(vuint in_nIndex) const = 0;

	/** Return information about the type of the part */
	virtual const VTypeInfo& GetTypeInfo() const = 0;

	/** Send a message to the part. Used by the serialization manager, the
	 * editor and maybe in the future to notify parts about events */
	void Send(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	template<typename T>
		vbool IsOfType() const;

	/** Returns 0 if part could not be converted */
	template<typename T>
		const T* Convert() const;

	/** Returns 0 if part could not be converted */
	template<typename T>
		T* Convert();

	void AttachTag(const tags::VTag& tag);
	void RemoveTag(const tags::VTag& tag);
	vbool HasTag(const tags::VTag& tag) const;
	VRangeIterator<const tags::VTag> Tags() const;

	virtual void ToXML(xml::IVXMLElement& node);
	virtual void FromXML(const xml::IVXMLElement& node);
private:
	/** Override for parts which will handle messages */
	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	std::vector<const tags::VTag*> m_Tags;
};

//-----------------------------------------------------------------------------
template<typename T>
	vbool IVPart::IsOfType() const
{
	return GetTypeInfo().CanBeCastedTo(GetCompileTimeTypeInfo<T>(0));
	//return (typeid(*this) == typeid(T)) != 0;
}

template<typename T>
	const T* IVPart::Convert() const
{
	if( IsOfType<T>() )
		return reinterpret_cast<const T*>(this);
	else
		return 0;
}

template<typename T>
	T* IVPart::Convert()
{
	if( IsOfType<T>() )
		return reinterpret_cast<T*>(this);
	else
		return 0;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity

V3D_TYPEINFO(v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VPART_2004_10_09_H

