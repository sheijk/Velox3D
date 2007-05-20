/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVSCENEMANAGERPART_2005_09_22_H
#define V3D_IVSCENEMANAGERPART_2005_09_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVGraphicsPart.h>
#include <V3d/Scene/IVShapePart.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Manages a list of IVShapeParts. Used to construct scenes which contain more
 * than one part
 *
 * @author sheijk
 */
class IVSceneManagerPart : public IVGraphicsPart
{
public:
	virtual ~IVSceneManagerPart() {}

	virtual void Add(IVGraphicsPart* in_pShape) = 0;
	virtual void Remove(IVGraphicsPart* in_pShape) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::IVSceneManagerPart, v3d::scene::IVGraphicsPart);
//-----------------------------------------------------------------------------
#endif // V3D_IVSCENEMANAGERPART_2005_09_22_H

