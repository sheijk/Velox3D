#ifndef V3D_VMODEL_2005_04_13_H
#define V3D_VMODEL_2005_04_13_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <vector>

#include <V3d/Core/RangeIter/VRangeIterator.h>
#include <V3d/Core/SmartPtr/VSharedPtr.h>
#include <V3d/Resource.h>
#include <V3d/Graphics/IVMesh.h>
#include <V3d/Graphics/IVMaterial.h>
#include <V3d/Math/VMatrix.h>
#include <V3d/Math/TransformationOps.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VModelMesh
{
	resource::VResourceDataPtr<const IVMesh> m_pMesh;
	resource::VResourceDataPtr<const IVMaterial> m_pMaterial;
	VSharedPtr<VMatrix44f> m_pTransform;

public:
	//VModelMesh(IVMesh* in_pMesh, IVMaterial* in_pMaterial);
	typedef resource::VResourceDataPtr<const IVMesh> MeshPtr;
	typedef resource::VResourceDataPtr<const IVMaterial> MaterialPtr;
	typedef VSharedPtr<VMatrix44f> MatrixPtr;

	VModelMesh(MeshPtr in_pMesh, MaterialPtr in_pMaterial, MatrixPtr in_pTransform);
	/*
	 * using default identity matrix
	 */
	VModelMesh(MeshPtr in_pMesh, MaterialPtr in_pMaterial);

	MeshPtr GetMesh() const;
	MaterialPtr GetMaterial() const;
	VSharedPtr<VMatrix44f> GetTransform();
	VSharedPtr<const VMatrix44f> GetTransform() const;
};

/**
 * @author sheijk
 */
class VModel
{
	std::vector<VModelMesh> m_Parts;

public:
	typedef VSharedPtr<VMatrix44f> MatrixPtr;

	VModel();
	VModel(const VModelMesh& in_Part);
	
	virtual ~VModel();

	void Add(const VModelMesh& in_Part);

	vuint GetPartCount() const;
	VModelMesh& GetPart(vuint in_nNum);
	const VModelMesh& GetPart(vuint in_nNum) const;
	//vuint GetMeshCount() const;
	//VMeshHandle GetMesh(vuint in_nNum) const;
	//VMaterialHandle GetMaterial(vuint in_nNum) const;
	//MatrixPtr GetTransform(vuint in_nNum);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
V3D_TYPEINFO(graphics::VModel);
#endif // V3D_VMODEL_2005_04_13_H
