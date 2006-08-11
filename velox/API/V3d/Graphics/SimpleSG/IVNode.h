#ifndef V3D_IVNODE_H
#define V3D_IVNODE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>
#include <V3d/Graphics/Misc/IVDrawList.h>
#include <V3d/Math/VMatrix.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
//-----------------------------------------------------------------------------

class IVCamera;

/**
 * Base class of all scene graph nodes. May have one or more childs.
 *
 * @author sheijk/ins
 */
class IVNode
{
public:
	typedef VRangeIterator<IVNode> NodeIterator;
	//typedef VBidirectionalIterator<IVNode> NodeIterator;
	typedef math::VMatrix<float, 4, 4> Matrix44f;

	/** transforms the given matrix by node's local transformation */
	virtual void ApplyTransformation(Matrix44f* io_pMatrix) = 0;

	/** sets the absolute transformation of the node */
	virtual void SetAbsoluteTransformation(const Matrix44f& in_Matrix) = 0;

	/** 
	 * applies it's own culling algorithm, adding or removing itself
	 * and all childs to/from the drawlist

	 entfernen von nodes: node muss auch aus der drawlist entfernt werden
	 lebenszeit von nodes muss irgendwo gemanaged werden
	 */
	virtual void ApplyCulling(
		IVDrawList* in_pDrawList, 
		IVCamera*) = 0;

	/** removes the node's and all child's meshes from the drawlist */
	virtual void Remove(IVDrawList* in_pDrawList) = 0;

	/*
	idee: scene graph: keine unterscheidung zwischen parent und childs,
	sondern nur neighbours? dann beim culling von dem node ausgehen, welcher
	die kamera enthaelt? so portal engines unterstuetzen? oder einfach velox
	von vorneherein als portal engine aufbauen?
	*/

	// evtl sinnvoll, das noch aufzunehmen, fuer generische culling algos
	//virtual VBoundingVolume GetBoundingVolume() = 0;

	/** returns the name of the node. must be different from all names
	 of other nodes sharing the same parent */
	virtual const vchar* GetNodeName() = 0;

	virtual void SetParent(IVNode* in_pNode) = 0;
	virtual void AddChild(IVNode* in_pChild) = 0;
	virtual void DeleteChild(IVNode* in_pNode) = 0;
	
	/** iterator pointing to the first child */
	virtual NodeIterator ChildsBegin() = 0;
	/** iterator pointing behind the last child */
	virtual NodeIterator ChildsEnd() = 0;

	//virtual void AddIntoFrameList(drawlist::IVDrawList* in_pDrawlist) = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVNODE_H
