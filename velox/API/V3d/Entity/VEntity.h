#ifndef V3D_VENTITY_2004_10_09_H
#define V3D_VENTITY_2004_10_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Entity/VEntityExceptions.h>
#include <V3d/Entity/IVPart.h>

#include <map>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * 
 */
class VEntity
{
public:
	typedef VPointer<IVPart>::SharedPtr PartPtr;

	VEntity();
	virtual ~VEntity();

	/** Will activate all parts */
    void Activate();

	/** Will deactivate all parts */
	void Deactivate();

	/** Adds a part to the entity */
	void AddPart(const utils::VFourCC& in_Id, PartPtr in_pPart);

private:
	VEntity(const VEntity&);
	void operator=(const VEntity&);

	typedef std::map<utils::VFourCC, PartPtr> PartContainer;
	PartContainer m_Parts;
	vbool m_bActivated;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VENTITY_2004_10_09_H
