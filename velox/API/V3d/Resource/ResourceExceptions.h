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

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_RESOURCE_EXCEPTIONS_2004_08_31_H
