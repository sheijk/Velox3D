/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_RESOURCE_EXCEPTIONS_2004_08_31_H
#define V3D_RESOURCE_EXCEPTIONS_2004_08_31_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Core/VException.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

// base class for all resource related exceptions
V3D_DECLARE_EXCEPTION(VResourceException, VException);

// tried to add data of same type twice to the same resource
V3D_DECLARE_EXCEPTION(VDataAlreadyAttachedException, VResourceException);

// resource data does not exist
V3D_DECLARE_EXCEPTION(VDataNotFoundException, VResourceException);

// resource could not be found
V3D_DECLARE_EXCEPTION(VResourceNotFoundException, VResourceException);

// constant resource data was tried to be accessed mutably
V3D_DECLARE_EXCEPTION(VDataNotMutableException, VResourceException);

// resource name is illegal
V3D_DECLARE_EXCEPTION(VIllegalResourceNameException, VResourceException);

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_RESOURCE_EXCEPTIONS_2004_08_31_H

