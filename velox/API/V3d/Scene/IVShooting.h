/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVSHOOTING_2005_05_20_H
#define V3D_IVSHOOTING_2005_05_20_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Entity/IVPart.h>
#include <V3d/Graphics/Misc/IVCamera.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVShooting : public entity::IVPart
{
public:
	virtual ~IVShooting() {}

	virtual void UpdateAndCull() = 0;
	virtual void Render() = 0;

	virtual vbool IsActive() const = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::IVShooting, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_IVSHOOTING_2005_05_20_H

