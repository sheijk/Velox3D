/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//TODO: add file creation date to file guard
#ifndef V3D_VFILENAMERESTYPE_2005_02_25_H
#define V3D_VFILENAMERESTYPE_2005_02_25_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource/IVResourceType.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Creates VFileName's for resources. Will get the VFileName of the parent's
 * resource and add this resource's name to it. The root resource will be 
 * mapped to the current working dir
 *
 * @author sheijk
 */
class VFileNameResType : public IVResourceType
{
	std::vector<VTypeInfo> m_ManagedTypes;
public:
	VFileNameResType();
	virtual ~VFileNameResType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		VTypeInfo in_Type);

	virtual void NotifyChange(const VTypeInfo& in_Type, 
		resource::VResource* in_pResource);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VFILENAMERESTYPE_2005_02_25_H

