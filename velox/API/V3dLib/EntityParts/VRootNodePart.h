#ifndef V3D_VROOTNODEPART_2004_11_14_H
#define V3D_VROOTNODEPART_2004_11_14_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dlib/EntityParts/VSceneGraphPart.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VRootNodePart : public VSceneGraphPart
{
public:

	VRootNodePart();
	virtual ~VRootNodePart() {}

	/**
	 * Calls the Update-Methods of all children
	 */
	virtual void Update();

	/** 
  	 * Does nothing for a root node
	 */
	virtual void Activate();

	/**
	 * Does nothing for a root node
	 */
	virtual void Deactivate();

	/**
	 * The root node's parent is always zero, so this method
	 * does nothing.
	 */
	virtual void SetParent(VSceneGraphPart* in_pParent);
};
//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VROOTNODE_2004_11_14_H