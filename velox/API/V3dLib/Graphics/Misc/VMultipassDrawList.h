#ifndef V3D_VMULTIPASSDRAWLIST_2004_04_10_H
#define V3D_VMULTIPASSDRAWLIST_2004_04_10_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Core/SmartPtr/VGuards.h>

#include <v3d/Graphics.h>

#include <V3dLib/Graphics/Misc/IVDrawList.h>

#include <map>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * A drawlist which supports multiple render passes. Meshes inside on pass
 * with lower id are guaranteed to be rendered before meshes inside a pass
 * with a higher id. Meshes inside the same id may be reordered. Default
 * pass is 0
 *
 * New passes are created when meshes are inserted into them. Removing of
 * passes is not supported at this time
 *
 * A multi pass list can have sub passes which are treated like one normal
 * pass. Subpasss inside a sub list are rendered in ascending order thus 
 * a list with sub passes will be rendered like one big list
 *
 * @author sheijk
 */
class VMultipassDrawList : public IVDrawList
{
public:
	typedef vint PassId;

private:
	typedef VPointer<IVDrawList>::SharedPtr DrawListPtr;
	typedef VMultipassDrawList* MultipassListPtr;
	typedef std::map<PassId, DrawListPtr> RenderPassList;
	typedef std::map<PassId, MultipassListPtr> MultipassList;

	RenderPassList m_RenderPasses;
	MultipassList m_Subpasses;
	IVDevice& m_Device;

	/**
	 * returns the draw list for the given pass. If it does not exist yet,
	 * it will be created
	 */
	DrawListPtr GetDrawListForPass(PassId in_nPass);

	/**
	 * Replaces the drawlist for the given pass with a new draw list
	 */
	void ReplacePass(PassId in_nPassId, DrawListPtr in_pNewPass);

public:
	VMultipassDrawList(IVDevice& in_Device);

	/** 
	 * Adds a new model to pass in_nId. If the pass does not exist yet it
	 * will be created
	 */
	void Add(VModel in_Model, PassId in_nId);

	/**
	 * Adds model to the default pass
	 */
	virtual void Add(VModel in_Model);

	/**
	 * Removes the model from all passes and sub passes
	 */
	virtual void Remove(VModel in_Model);

	/**
	 * Returns a drawlist for the given pass. Will be created if it does not
	 * exist yet
	 */
	IVDrawList& GetPass(PassId in_nPass);

	/**
	 * Turns the given pass into a sub pass returning a new multi pass list
	 * for it. Will return existant list if the pass is already a sub pass
	 */
	VMultipassDrawList& MakeSubpassList(PassId in_nPassId);

	/**
	 * Renders all passes and sub passes
	 */
	virtual void Render();

	/** returns the associated device */
	IVDevice& GetDevice();
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMULTIPASSDRAWLIST_2004_04_10_H
