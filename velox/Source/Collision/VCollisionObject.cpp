//-----------------------------------------------------------------------------
#include <v3dLib/Collision/VCollisionObject.h>
#include <v3dLib/Collision/VCollisionException.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace collision {
//-----------------------------------------------------------------------------
VCollisionObject::VCollisionObject()
{
	m_iNumVertices		= 0;
	m_iNumIndices		= 0;

	m_pTriangleIndex	= 0;
	m_pPoints			= 0;
	m_pWorldMatrix      = 0;
}

VCollisionObject::~VCollisionObject()
{
	delete [] m_pTriangleIndex;
	delete [] m_pPoints;

	m_iNumVertices		= 0;
	m_iNumIndices		= 0;

	m_pTriangleIndex	= 0;
	m_pPoints			= 0;
	m_pWorldMatrix      = 0;
}

vint VCollisionObject::GetNumVertex()
{
	return m_iNumVertices;
}

vint VCollisionObject::GetNumIndices()
{
	return m_iNumIndices;
}

Point* VCollisionObject::GetVertexPointer()
{
	return m_pPoints;
}

IndexedTriangle* VCollisionObject::GetIndexPointer()
{
	return m_pTriangleIndex;
}

VMatrix44f* VCollisionObject::GetWorldMatrix()
{
	return m_pWorldMatrix;
}

Opcode::Model& VCollisionObject::GetOpcodeModel()
{ 
	return m_Model;
}

void VCollisionObject::SetWorldMatrix(VMatrix44f* in_pWorldMatrix)
{
	m_pWorldMatrix =  in_pWorldMatrix;
}


void VCollisionObject::CreatePoints(vfloat32* in_Array, int iNumVertices)
{

	m_iNumVertices = iNumVertices;

	m_pPoints = new Point[iNumVertices];

	for(vuint i = 0; i< m_iNumVertices; i++)
	{
		m_pPoints[i].x  = in_Array[i*3];
		m_pPoints[i].y  = in_Array[i*3+1];
		m_pPoints[i].z  = in_Array[i*3+2];
	}
}

void VCollisionObject::CreateIndex(vint* in_Array, int iNumIndices)
{

	m_iNumIndices	= iNumIndices;

	m_pTriangleIndex = new IndexedTriangle[iNumIndices];

	for(vuint i  = 0; i < m_iNumIndices; i++)
	{
		m_pTriangleIndex[i].mVRef[0] = in_Array[i*3];
		m_pTriangleIndex[i].mVRef[1] = in_Array[i*3+1];
		m_pTriangleIndex[i].mVRef[2] = in_Array[i*3+2];
	}
}

void VCollisionObject::Initialize()
{

	/**
	* The one and only opcode creation structure
	* and build settints. This
	* variables are tempoary and can be discarded
	* after the final initalization
	*/


	Opcode::OPCODECREATE  createStructure;
	Opcode::BuildSettings buildSettings;



	//TODO: exception header
	if(( GetNumIndices() / 3) < 1)
	{
		V3D_THROW(VCollisionException, "value must be greater 0!");
	}

	m_MeshInterface.SetNbTriangles( GetNumIndices() / 3);
	m_MeshInterface.SetNbVertices(GetNumVertex());
	m_MeshInterface.SetPointers(
		GetIndexPointer(),
		GetVertexPointer()
		);

	m_MeshInterface.SetStrides(0,0);

	//TODO: wrap settings out

	buildSettings.mRules = Opcode::SPLIT_BEST_AXIS;

	createStructure.mIMesh = &m_MeshInterface;
	createStructure.mSettings = buildSettings;
	createStructure.mNoLeaf = true;
	createStructure.mQuantized = false;
	createStructure.mKeepOriginal = false;
	createStructure.mCanRemap = false;

	m_Model.Build(createStructure);
}

//-----------------------------------------------------------------------------
} // namespace collision
} // namespace v3d
//-----------------------------------------------------------------------------