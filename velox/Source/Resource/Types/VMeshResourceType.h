/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMESHRESOURCETYPE_H
#define V3D_VMESHRESOURCETYPE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Resource/Types/VFileName.h>
#include <V3d/Resource.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
* Create a mesh from a mesh description
*
* @author: ins
*/
class VMeshResourceType : public resource::IVResourceType
{
	std::vector<VTypeInfo> m_ManagedTypes;
public:
	VMeshResourceType();
	virtual ~VMeshResourceType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		VTypeInfo in_Type);

	virtual void NotifyChange(const VTypeInfo& in_Type, 
		resource::VResource* in_pResource);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::image
//-----------------------------------------------------------------------------
#endif // V3D_VMESHRESOURCETYPE_H

