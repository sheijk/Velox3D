#ifndef V3D_VCOLLISIONOBJECT_09_24_04_H
#define V3D_VCOLLISIONOBJECT_09_24_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Math/VMatrix.h>

#include <Opcode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace collision {
//-----------------------------------------------------------------------------


/**
 * Holds geometry data about a collision object. Wrapps the opcode
 * model structure
 *
 * @author:		ins
 * @version:	1.0
 */

//Note: adding stride support and implicit casting to Point/IndexedTriangle??

class VCollisionObject
{
public:

	VCollisionObject();
	virtual ~VCollisionObject();
	
	//TODO: bitte in GetVertex/IndexCount aendern (damits velox weit einheitlich ist)
	vint GetNumVertex();
	vint GetNumIndices();
	Point* GetVertexPointer();
	IndexedTriangle* GetIndexPointer();
	VMatrix44f* GetWorldMatrix();
	//TODO: ist das noetig? so haengt das ganze komplett an opcode..
	Opcode::Model& GetOpcodeModel();

	/**
	* Set the world matrix for this object. 0 is identity
	* and will be special treated by opcode with faster results
	* @note:  matrix MUST not contain scale. 
	*		  only rotation and translation
	*		  is supported by opcode
	*/

	void SetWorldMatrix(VMatrix44f* in_pWorldMatrix);

	/**
	 * overwrite this method if you need a concrete vertex to collision
	 * point conversion
	 */

	virtual void CreatePoints(vfloat32* in_Array, int iNumVertices);
	
	/**
	 * overwrite this method if you need
	 * a concrete index to triangleIndex conversion
	 */

	virtual void CreateIndex(vint* in_Array, int iNumIndices);

	/**
	 * Call this method to initialize and building the model
	 * @note: Has to be called BEFORE object is given to
	 * the OpcodeSystem
	 */

	void Initialize();
	
	
protected:

	vuint				m_iNumVertices;
	vuint				m_iNumIndices;
	Point*				m_pPoints;
	IndexedTriangle*	m_pTriangleIndex;
	VMatrix44f*			m_pWorldMatrix;

	/**
	 * The one and only opcode model for this object
	 */

	Opcode::Model			m_Model;
	Opcode::MeshInterface	m_MeshInterface;

};
//-----------------------------------------------------------------------------
} // namespace collision
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCOLLISIONOBJECT_09_24_04_H
