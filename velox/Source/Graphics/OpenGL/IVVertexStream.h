/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVVERTEXSTREAM_2005_02_03_H
#define V3D_IVVERTEXSTREAM_2005_02_03_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VTypeInfo.h>

#include <V3d/Graphics/VVertexFormat.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * An OpenGL vertex stream. Provides a way to bind vertex data to be sent to
 * OpenGL
 * 
 * @author sheijk
 */
class IVVertexStream
{
public:
	virtual ~IVVertexStream() {};

	virtual vbool Bind(VVertexFormat::DataTypes in_StreamTypes) const = 0;
	virtual void UnbindAll() const = 0;

	virtual const void* GetIndexAddress() const = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO(v3d::graphics::IVVertexStream);

//-----------------------------------------------------------------------------
#endif // V3D_IVVERTEXSTREAM_2005_02_03_H

