/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCCYLINDER_2006_11_29_H
#define V3D_VCCYLINDER_2006_11_29_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace math {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Representation of a capped cylinder
 */
class VCCylinder
{
public:
	VCCylinder(vfloat32 in_fLength = 1.0f, vfloat32 in_fRadius = 1.0f);
	~VCCylinder();

	vfloat32 GetLength();
	vfloat32 GetRadius();
	void SetParams(vfloat32 in_fLength, vfloat32 in_fRadius);

private:
    vfloat32 m_fLength;
	vfloat32 m_fRadius;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::math
//-----------------------------------------------------------------------------
#endif // V3D_VCCYLINDER_2006_11_29_H

