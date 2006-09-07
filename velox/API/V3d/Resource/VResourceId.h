/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VRESOURCEID_H
#define V3D_VRESOURCEID_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource/VResourceDataPtr.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VResource;

/**
 * A proxy to an existing resource
 *
 * @author sheijk
 */
class VResourceId
{
public:
	explicit VResourceId(VStringParam in_pResName);
	VResourceId(VResource*);

	VResource* operator->();
	VResource& operator*();

private:
	// const pointer to resource
	VResource* const m_pResource;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VRESOURCEID_H

