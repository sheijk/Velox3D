/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMODEL_2005_04_13_H
#define V3D_VMODEL_2005_04_13_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

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
	VSharedPtr<math::VMatrix44f> m_pTransform;

public:
	//VModelMesh(IVMesh* in_pMesh, IVMaterial* in_pMaterial);
	typedef resource::VResourceDataPtr<const IVMesh> MeshPtr;
	typedef resource::VResourceDataPtr<const IVMaterial> MaterialPtr;
	typedef VSharedPtr<math::VMatrix44f> MatrixPtr;

	VModelMesh(MeshPtr in_pMesh, MaterialPtr in_pMaterial, MatrixPtr in_pTransform);
	/*
	 * using default identity matrix
	 */
	VModelMesh(MeshPtr in_pMesh, MaterialPtr in_pMaterial);

	MeshPtr GetMesh() const;
	MaterialPtr GetMaterial() const;
	VSharedPtr<math::VMatrix44f> GetTransform();
	VSharedPtr<const math::VMatrix44f> GetTransform() const;
};

/**
 * @author sheijk
 */
class VModel
{
	typedef std::vector<VModelMesh> PartArray;
	PartArray m_Parts;

public:
	typedef VSharedPtr<math::VMatrix44f> MatrixPtr;

	VModel();
	VModel(const VModelMesh& in_Part);
	
	virtual ~VModel();

	void Add(const VModelMesh& in_Part);
	void AddMeshes(const VModel& in_Model);
	void ApplyMatrix(math::VMatrix44f in_Matrix);

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

