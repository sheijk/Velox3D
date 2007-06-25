/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VCUBEMAPSHOOTING_2007_06_23_H
#define V3D_VCUBEMAPSHOOTING_2007_06_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVShooting.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Will render to an (axis aligned) cube map
 *
 * @author sheijk
 */
class VCubemapShooting : public IVShooting
{
public:
	VCubemapShooting();
	virtual ~VCubemapShooting();

	virtual void UpdateAndCull();
	virtual void Render();
	virtual vbool IsActive() const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VCubemapShooting, v3d::scene::IVShooting);
//-----------------------------------------------------------------------------
#endif // V3D_VCUBEMAPSHOOTING_2007_06_23_H

