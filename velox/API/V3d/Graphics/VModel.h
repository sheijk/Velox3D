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
	//resource::VResourceDataPtr<IVMesh> m_hMesh;
	//resource::VResourceDataPtr<IVMaterial> m_hMaterial;
	VSharedPtr<VMatrix44f> m_pTransform;

	IVMesh* m_pMesh;
	IVMaterial* m_pMaterial;
public:
	VModelMesh(IVMesh* in_pMesh, IVMaterial* in_pMaterial);
	VModelMesh(resource::VResourceDataPtr<IVMesh> in_hMesh);
	VModelMesh(
		resource::VResourceDataPtr<IVMesh> in_hMesh,
		VSharedPtr<VMatrix44f> in_pTransform);
	VModelMesh(
		resource::VResourceDataPtr<IVMesh> in_hMesh,
		resource::VResourceDataPtr<IVMaterial> in_hMaterial,
		VSharedPtr<VMatrix44f> in_pTransform);

	IVMesh* GetMesh();
	IVMaterial* GetMaterial();
	VMatrix44f& GetTransform();
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
	virtual ~VModel();

	void Add(const VModelMesh& in_Part);

	vuint GetPartCount() const;
	VModelMesh& GetPart(vuint in_nNum);
	//vuint GetMeshCount() const;
	//VMeshHandle GetMesh(vuint in_nNum) const;
	//VMaterialHandle GetMaterial(vuint in_nNum) const;
	//MatrixPtr GetTransform(vuint in_nNum);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VMODEL_2005_04_13_H
