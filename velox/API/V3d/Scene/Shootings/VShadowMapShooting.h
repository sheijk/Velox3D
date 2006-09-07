/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSHADOWMAPSHOOTING_2006_06_02_H
#define V3D_VSHADOWMAPSHOOTING_2006_06_02_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/Shootings/VShootingBase.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VShadowMapShooting : public VShootingBase
{
public:
	VShadowMapShooting();
	virtual ~VShadowMapShooting();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VSHADOWMAPSHOOTING_2006_06_02_H

