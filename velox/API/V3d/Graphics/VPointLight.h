/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//TODO: add file creation date to file guard
#ifndef V3D_VPOINTLIGHT_2005_06_15_H
#define V3D_VPOINTLIGHT_2005_06_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math/VVector.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A simple point light with ambient, specular and diffuse color.
 *
 * @author sheijk
 */
class VPointLight
{
public:
	math::VVector3f GetPosition() const;
	void SetPosition(const math::VVector3f& in_Position);

	VColor4f GetAmbient() const;
	void SetAmbient(const VColor4f& in_Ambient);

	VColor4f GetSpecular() const;
	void SetSpecular(const VColor4f& in_Specular);

	VColor4f GetDiffuse() const;
	void SetDiffuse(const VColor4f& in_Diffuse);

private:
	math::VVector3f m_Position;
	VColor4f m_Ambient;
	VColor4f m_Specular;
	VColor4f m_Diffuse;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VPOINTLIGHT_2005_06_15_H

