#ifndef V3D_VUPDATEABLEPART_2004_10_14_H
#define V3D_VUPDATEABLEPART_2004_10_14_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>
#include "VEntityUpdater.h"
//-----------------------------------------------------------------------------
namespace v3d { namespace racer {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * A generic entity part which has an update function. Use this class as a
 * base class for 'special' entity parts which need regular updates but
 * have no manager where they may register. (Create an instance of
 * VEntityUpdater<VUpdateablePart> where you register instances of classes
 * derived from VUpdateablePart and call it's UpdateAll() function each frame)
 *
 * @author sheijk
 */
class VUpdateablePart : public entity::IVPart
{
	VEntityUpdater<VUpdateablePart>* m_pUpdater;
	vbool m_bRegistered;

public:
	virtual void Activate();
	virtual void Deactivate();

	virtual void Update() = 0;
protected:
	VUpdateablePart(VEntityUpdater<VUpdateablePart>* in_pUpdater);
	virtual ~VUpdateablePart();

	/** Call this function inside Activate() if you override it */
	void Register();
	/** Call this function inside Deactivate() if you override it */
	void Unregister();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::racer
//-----------------------------------------------------------------------------
#endif // V3D_VUPDATEABLEPART_2004_10_14_H
