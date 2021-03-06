/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VIMPORTED3DSRESOURCETYPE_H
#define V3D_VIMPORTED3DSRESOURCETYPE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Resource/Types/VFileName.h>
#include <V3d/Resource.h>

//-----------------------------------------------------------------------------
namespace v3d{
namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
* Automatically loads imported 3ds files
*
* @author ins
*/
class VImported3DSResourceType : public resource::IVResourceType
{
	std::vector<VTypeInfo> m_ManagedTypes;
public:
	VImported3DSResourceType();
	virtual ~VImported3DSResourceType();

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
#endif // V3D_VIMPORTED3DSRESOURCETYPE_H

