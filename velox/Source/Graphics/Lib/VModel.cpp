#include <V3d/Graphics/VModel.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VModelMesh::VModelMesh(IVMesh* in_pMesh, IVMaterial* in_pMaterial)
{
	m_pMesh = in_pMesh;
	m_pMaterial = in_pMaterial;
	m_pTransform = math::IdentityPtr();
}

VModelMesh::VModelMesh(resource::VResourceDataPtr<IVMesh> in_hMesh)
{
	V3D_THROW(VException, "not implemented");
	//m_hMesh = in_hMesh;
	//m_hMaterial = 0;
	//m_pTransform = math::IdentityPtr();
}

VModelMesh::VModelMesh(
		   resource::VResourceDataPtr<IVMesh> in_hMesh,
		   VSharedPtr<VMatrix44f> in_pTransform)
{
	V3D_THROW(VException, "not implemented");
	//m_hMesh = in_hMesh;
	//m_pTransform = in_pTransform;
	//m_hMaterial = 0;
}

VModelMesh::VModelMesh(
		   resource::VResourceDataPtr<IVMesh> in_hMesh,
		   resource::VResourceDataPtr<IVMaterial> in_hMaterial,
		   VSharedPtr<VMatrix44f> in_pTransform)
{
	V3D_THROW(VException, "not implemented");
	//m_hMesh = in_hMesh;
	//m_hMaterial = in_hMaterial;
	//m_pTransform = in_pTransform;
}

IVMesh* VModelMesh::GetMesh() 
{
	return m_pMesh;
	//return &*m_hMesh;
}

IVMaterial* VModelMesh::GetMaterial()
{
	return m_pMaterial;
	//return &*m_hMaterial;
}

VMatrix44f& VModelMesh::GetTransform()
{
	return *m_pTransform;
}

//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VModel::VModel()
{
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

vuint VModel::GetPartCount() const
{
	return vuint(m_Parts.size());
}

VModelMesh& VModel::GetPart(vuint in_nNum)
{
	return m_Parts[in_nNum];
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
