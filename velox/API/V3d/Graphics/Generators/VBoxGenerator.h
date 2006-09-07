/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VBOXGENERATOR_2005_10_09_H
#define V3D_VBOXGENERATOR_2005_10_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/VVertexBuffer.h>
#include <V3d/Graphics/Generators/IVMeshGenerator.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VBoxGenerator : public IVMeshGenerator
{
public:
	VBoxGenerator(vfloat32 in_fSize = 2.0f);
	VBoxGenerator(vfloat32 in_fWidth, vfloat32 in_fHeight, vfloat32 in_fDepth);
	virtual ~VBoxGenerator();

	virtual VVertexBuffer* CreateVertexBuffer() const;
	virtual VVertexBuffer* CreateIndexBuffer() const;
	virtual VMeshDescription::GeometryType GetGeometryType() const;

private:
	vfloat32	m_fHeight;
	vfloat32	m_fWidth;
	vfloat32	m_fDepth;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO_WITHPARENT(v3d::graphics::VBoxGenerator, v3d::graphics::IVMeshGenerator);
//-----------------------------------------------------------------------------
#endif // V3D_VBOXGENERATOR_2005_10_09_H

