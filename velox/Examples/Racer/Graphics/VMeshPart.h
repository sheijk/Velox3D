#ifndef V3D_MESHPART_2004_10_12_H
#define V3D_MESHPART_2004_10_12_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity.h>
#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>

#include "../Shared/VRigidBodyPart.h"
#include "../Shared/VEntityUpdater.h"
#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace racer {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VMeshPart;

/**
 * The graphics manager provides a drawlist and updates registered graphical
 * entity parts each frame. Add entity parts to an instance of this class which
 * need to be updated each frame. (animated meshes etc)
 *
 * @author sheijk
 */
class VGraphicsManager : public VEntityUpdater<VMeshPart>
{
	graphics::IVDrawList* m_pDrawList;

public:
	VGraphicsManager();

	void SetDrawList(graphics::IVDrawList& in_DrawList);

	graphics::IVDrawList& GetDrawList();
};

/**
 * A mesh entity part. It will add itself to the given instance of the graphic
 * update manager. You may need any number of meshes to it. If a VRigidBody
 * part with the id 'body' is present, all mesh model transformation matrix
 * positions will be set to the rigid body part's position each time update
 * is called
 *
 * @author sheijk
 */
class VMeshPart : public entity::IVPart
{
	typedef std::list<graphics::VModel> MeshList;

	VGraphicsManager* m_pManager;
	MeshList m_Meshes;

	VRigidBodyPart* m_pRigidBodyPart;
	vbool m_bActive;

	graphics::IVDrawList& GetDrawList();
public:
	VMeshPart(VGraphicsManager* in_pManager);

	void AddMesh(graphics::IVDevice::MeshHandle in_hMesh);
	void AddMesh(graphics::VModel in_Model);
	void RemoveMesh(graphics::IVDevice::MeshHandle in_hMesh);

	void Update();

	virtual void Activate();
	virtual void Deactivate();
	virtual void TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::racer
//-----------------------------------------------------------------------------
#endif // V3D_MESHPART_2004_10_12_H
