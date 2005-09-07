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
 * Dependency to another part placed in the same entity or an (in)direct 
 * parent
 */
struct VPartDependency
{
	/** The location of a dependency: where the required part is located */
	enum Location { Neighbour, Ancestor };

#ifndef SWIG
	Location location;
	std::string id;
#endif

	Location GetLocation() const { return location; }
	void SetLocation(Location loc) { location = loc; }

	std::string GetId() const { return id; }
	void SetId(const std::string& in_Id) { id = in_Id; }
};

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
	 * Tells the part about the next part with it's id up the entity hierarchy
	 */
	virtual void TellParentPart(const utils::VFourCC& in_Id, IVPart& in_Part)
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
