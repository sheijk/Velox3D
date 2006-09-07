/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVCAMERA_2004_05_15_H
#define V3D_IVCAMERA_2004_05_15_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Math/VVector.h>
#include <V3d/Math/VMatrix.h>
#include <V3d/Math/VRBTransform.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

class IVDevice;

/**
 * Interface for cameras
 *
 * @author sheijk
 */
class IVCamera
{
public:
	virtual const math::VMatrix44f& ViewMatrix() const = 0;
	virtual const math::VRBTransform& Transform() const = 0;

	virtual void ApplyTo(IVDevice& in_Device) const = 0;

	virtual math::VVector3f GetPosition() const = 0;
	virtual math::VVector3f GetViewDirection() const = 0;
	virtual math::VVector3f GetUpVector() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVCAMERA_2004_05_15_H

