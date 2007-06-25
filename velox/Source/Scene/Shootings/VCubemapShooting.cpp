/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Scene/Shootings/VCubemapShooting.h>
//-----------------------------------------------------------------------------

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; //  auto indent

/**
 * standard c'tor
 */
VCubemapShooting::VCubemapShooting()
{
}

/**
 * d'tor
 */
VCubemapShooting::~VCubemapShooting()
{
}

void VCubemapShooting::UpdateAndCull()
{
}

void VCubemapShooting::Render()
{
}

vbool VCubemapShooting::IsActive() const
{
	V3D_THROW(VException, "ooops, this is called?");
}

V3D_REGISTER_PART_PARSER(VCubemapShooting);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

