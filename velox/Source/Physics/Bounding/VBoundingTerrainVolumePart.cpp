/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/Bounding/VBoundingTerrainVolumePart.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VBoundingTerrainVolumePart::VBoundingTerrainVolumePart() :
	m_pTerrainPart(entity::VPartDependency::Neighbour, RegisterTo())
{
	m_bActive = false;
	m_pIndicesPointer = 0;
}
VBoundingTerrainVolumePart::~VBoundingTerrainVolumePart()
{
  if(m_pIndicesPointer)
  {
	delete m_pIndicesPointer;
	m_pIndicesPointer = 0;
  }
}

VBoundingMesh* VBoundingTerrainVolumePart::GetBoundingMesh()
{
	return &m_BoundingMesh;
}

vbool VBoundingTerrainVolumePart::HasBoundingMesh()
{
	if(m_BoundingMesh.GetVertices())
		return true;
	return false;
}

math::VPlane* VBoundingTerrainVolumePart::GetBoundingPlane()
{
	return 0;
}

math::VBoundingBox* VBoundingTerrainVolumePart::GetBoundingBox()
{
	return 0;
}

math::VBoundingSphere* VBoundingTerrainVolumePart::GetBoundingSphere()
{
	return 0;
}

math::VCCylinder* VBoundingTerrainVolumePart::GetBoundingCylinder()
{
  return 0;
}

void VBoundingTerrainVolumePart::Activate()
{
	if( m_pTerrainPart.Get() == 0 )
		V3D_THROW(entity::VMissingPartException, "missing terrain volume part 'data'");

	if( !m_bActive )
		Create();
}

void VBoundingTerrainVolumePart::Create()
{
//	VSharedPtr<VBoundingMeshVolumePart> pBoundingVolume(new VBoundingMeshVolumePart);

	vint size = m_pTerrainPart->GetIndexCount();
	size = (size-2) * 3; //hack, does not take degenerated triangle into account
	vuint* pNewIndices = new vuint[size];

	vint* pIndices = (vint*)m_pTerrainPart->GetIndexBuffer()->GetBufferAddress();
	vint nCount = 0;
	int lastIndex1 = 0;
	int lastIndex2 = 0;
	int lastIndex3 = 0;
	//create a index list out of the terrain strip WITHOUT degenerated triangles
	for(vuint i = 0; i< m_pTerrainPart->GetIndexCount(); i++)
	{
		if(i==0) //first triangle copy data
		{
			pNewIndices[nCount] = pIndices[i];
			nCount++;
			pNewIndices[nCount] = pIndices[i+1];
			nCount++;
			pNewIndices[nCount] = pIndices[i+2];
			nCount++;
			i=2;
			continue;
		}
		pNewIndices[nCount] = pIndices[i-1];
		lastIndex1 = pNewIndices[nCount];
		nCount++;

		pNewIndices[nCount] = pIndices[i-2];
		lastIndex2 = pNewIndices[nCount];
		nCount++;

		pNewIndices[nCount] = pIndices[i];
		lastIndex3 = pNewIndices[nCount];
		nCount++;

		if(lastIndex1 == lastIndex2 || lastIndex2 == lastIndex3 || lastIndex1 == lastIndex3)
		{
			nCount -=3;
			vuint a = 0;
			i+=2;
			/*pNewIndices[nCount-2] = 0;
			pNewIndices[nCount-1] = 1;
			pNewIndices[nCount] = 2;*/
		}	
	}

	VBoundingMesh mesh((float*)m_pTerrainPart->GetVertexBuffer()->GetBufferAddress(), m_pTerrainPart->GetVertexCount(), 3* sizeof(vfloat32),
		pNewIndices, nCount, 3 * sizeof(vuint));
	m_pIndicesPointer = pNewIndices;

	m_BoundingMesh = mesh;
	m_bActive = true;
}

void VBoundingTerrainVolumePart::Deactivate()
{
	if(m_pIndicesPointer)
		delete [] m_pIndicesPointer;
	m_bActive = false;
}

void VBoundingTerrainVolumePart::OnMessage(
										const messaging::VMessage& in_Message,
										messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;

	const string request = in_Message.GetAs<string>("type");

	if( request == "getSettings" )
	{
		if( in_pAnswer != 0 )
		{
			in_pAnswer->AddProperty("VertexCount",  m_BoundingMesh.GetVertexCount());
			in_pAnswer->AddProperty("VertexStride",  m_BoundingMesh.GetVertexStride());
			in_pAnswer->AddProperty("IndexCount", m_BoundingMesh.GetIndexCount());
			in_pAnswer->AddProperty("IndexStride", m_BoundingMesh.GetIndexStride());
			in_pAnswer->AddProperty("NormalCount",  m_BoundingMesh.GetNormalCount());
			in_pAnswer->AddProperty("NormalStride",  m_BoundingMesh.GetNormalStride());
		}
	}
}

V3D_REGISTER_PART_PARSER(VBoundingTerrainVolumePart);
//-----------------------------------------------------------------------------
} // namespace v3d::
}
//-----------------------------------------------------------------------------

