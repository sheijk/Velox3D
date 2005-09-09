#include <V3d/Graphics/VModel.h>
#include <V3d/Math/VMatrixOps.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

//VModelMesh::VModelMesh(IVMesh* in_pMesh, IVMaterial* in_pMaterial)
//{
//	m_pMesh = in_pMesh;
//	m_pMaterial = in_pMaterial;
//	m_pTransform = math::IdentityPtr();
//}

VModelMesh::VModelMesh(
	MeshPtr in_pMesh,
	MaterialPtr in_pMaterial,
	MatrixPtr in_pTransform)
{
	m_pMesh = in_pMesh;
	m_pMaterial = in_pMaterial;
	m_pTransform = in_pTransform;
}

VModelMesh::VModelMesh(
					   MeshPtr in_pMesh,
					   MaterialPtr in_pMaterial)
{
	m_pMesh = in_pMesh;
	m_pMaterial = in_pMaterial;

		
	m_pTransform.Assign(new VMatrix44f(math::IdentityMatrix()));
}
//TODO: eine war falsch und produziert nen heap fehler -ins
/*VModelMesh::VModelMesh(
	MeshPtr in_pMesh,
	MaterialPtr in_pMaterial)
{
	m_pMesh = in_pMesh;
	m_pMaterial = in_pMaterial;
	m_pTransform = math::IdentityPtr();
}*/

VModelMesh::MeshPtr VModelMesh::GetMesh() const
{
	return m_pMesh;
	//return &*m_hMesh;
}

VModelMesh::MaterialPtr VModelMesh::GetMaterial() const
{
	return m_pMaterial;
	//return &*m_hMaterial;
}

VSharedPtr<VMatrix44f> VModelMesh::GetTransform()
{
	return m_pTransform;
}

VSharedPtr<const VMatrix44f> VModelMesh::GetTransform() const
{
	return m_pTransform;
}

//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VModel::VModel()
{
}

VModel::VModel(const VModelMesh& in_Part)
{
	Add(in_Part);
}

/**
 * d'tor
 */
VModel::~VModel()
{
}

void VModel::Add(const VModelMesh& in_Part)
{
	m_Parts.push_back(in_Part);
}

void VModel::AddMeshes(const VModel& in_Model)
{
	for(vuint partnum = 0; partnum < in_Model.GetPartCount(); ++partnum)
	{
		Add(in_Model.GetPart(partnum));
	}
}

vuint VModel::GetPartCount() const
{
	return vuint(m_Parts.size());
}

VModelMesh& VModel::GetPart(vuint in_nNum)
{
	return m_Parts[in_nNum];
}

const VModelMesh& VModel::GetPart(vuint in_nNum) const
{
	return m_Parts[in_nNum];
}

void VModel::ApplyMatrix(VMatrix44f in_Matrix)
{
	if(m_Parts.size())
	{	PartArray::iterator i = m_Parts.begin();
		VSharedPtr<VMatrix44f> currentMatrix;

		for(; i != m_Parts.end(); ++i)
		{
			currentMatrix = (*i).GetTransform();
			currentMatrix->m_Mat = in_Matrix.m_Mat;
		}
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
