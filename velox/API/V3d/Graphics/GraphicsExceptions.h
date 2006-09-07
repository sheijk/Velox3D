/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_GRAPHICS_EXCEPTIONS_2004_08_31_H
#define V3D_GRAPHICS_EXCEPTIONS_2004_08_31_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Core/VException.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

// all exceptions thrown by the gfx subsystem
V3D_DECLARE_EXCEPTION(VGraphicException, VException);

// exceptions while creating data (buffers, states etc)
V3D_DECLARE_EXCEPTION(VCreationException, VGraphicException);

// exception while creating a material
V3D_DECLARE_EXCEPTION(VMaterialCreationException, VCreationException);
// invalid value for a material state parameter
V3D_DECLARE_EXCEPTION(VInvalidModeException, VMaterialCreationException);
// missing state parameters
V3D_DECLARE_EXCEPTION(VMissingStateParameterException, VMaterialCreationException);

// error while creating the graphics device
V3D_DECLARE_EXCEPTION(VDeviceCreationException, VCreationException);
// invalid options for display settings
V3D_DECLARE_EXCEPTION(VIllegalDisplayException, VDeviceCreationException);

// invalid matrix type set
V3D_DECLARE_EXCEPTION(VInvalidMatrixTypeException, VGraphicException);

V3D_DECLARE_EXCEPTION(VOpenGLException, VGraphicException);

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_GRAPHICS_EXCEPTIONS_2004_08_31_H

