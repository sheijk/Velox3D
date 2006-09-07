/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VXMLMODELRESOURCETYPE_2006_05_24_H
#define V3D_VXMLMODELRESOURCETYPE_2006_05_24_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Resource/IVResourceType.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Creates a VModel from an .xml file which can be loaded with VModelLoader
 *
 * @see VModelLoader
 *
 * @author sheijk
 */
class VXMLModelResourceType : public resource::IVResourceType
{
public:
	VXMLModelResourceType();
	virtual ~VXMLModelResourceType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		VTypeInfo in_Type);

	virtual void NotifyChange(const VTypeInfo& in_Type, 
		resource::VResource* in_pResource);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VXMLMODELRESOURCETYPE_2006_05_24_H

