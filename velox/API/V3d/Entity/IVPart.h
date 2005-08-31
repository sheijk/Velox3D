#ifndef V3D_VPART_2004_10_09_H
#define V3D_VPART_2004_10_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Entity/VEntityExceptions.h>

#include <V3d/Messaging/VMessage.h>

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
 * @see v3d::entity::VEntityManager
 * @see v3d::entity::VEntity
 * 
 * @author sheijk
 */
class IVPart
{
public:
	/** The location of a dependency: where the required part is located */
	enum Location { Neighbour, Ancestor };

	/** Dependency to another part placed in the same or an (in)direct parent */
	struct Dependency
	{
		Location location;
		std::string id;
	};

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
		Location in_Location, 
		const std::string& in_Id, 
		IVPart& in_Part)
	{}

	/** 
	* Notify the part that another connected part has been removed 
	* The disconnected part might be deleted right after this call. Thus all
	* references to it must be reset to null
	*/
	virtual void Disconnect(
		Location in_Location,
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
	virtual Dependency GetDependencyInfo(vuint in_nIndex) const = 0;

	virtual void Send(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer = 0)
	{}

	template<typename T>
		vbool IsOfType() const;

	template<typename T>
		const T* Convert() const;

	template<typename T>
		T* Convert();
};

//-----------------------------------------------------------------------------
template<typename T>
	vbool IVPart::IsOfType() const
{
	return (typeid(*this) == typeid(T)) != 0;
}

template<typename T>
	const T* IVPart::Convert() const
{
	if( IsOfType<T>() )
		return dynamic_cast<const T*>(this);
	else
		return 0;
}

template<typename T>
	T* IVPart::Convert()
{
	if( IsOfType<T>() )
		return dynamic_cast<T*>(this);
	else
		return 0;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VPART_2004_10_09_H
