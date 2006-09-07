/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVSHAPEPART_2005_09_22_H
#define V3D_IVSHAPEPART_2005_09_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVGraphicsPart.h>
#include <V3d/Graphics/IVMaterial.h>
#include <V3d/Math/VRBTransform.h>

namespace v3d { namespace graphics {
	class IVDevice;
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A part containing arbitrary geometry which shared one material. Might be a
 * simple vertex buffer, a collection of vertex buffers or glVertex/.. calls
 *
 * @author sheijk
 */
class IVShapePart : public IVGraphicsPart
{
public:
	virtual ~IVShapePart() {}

	/** 
	 * Sends the geometry to OpenGL. Either renders a velox vertex buffer or
	 * uses custom glVertex/.. calls. Must not change any OpenGL state!
	 */
	virtual void SendGeometry(graphics::IVDevice& in_Device) const = 0;

	/**
	 * This material will be applied before rendering the shape's geometry
	 */
	//virtual const graphics::IVMaterial& GetMaterial() const = 0;

	virtual vuint GetPassCount() const = 0;
	virtual void ApplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const = 0;
	virtual void UnapplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const = 0;

	/**
	 * Will be converted to a matrix and set as the model matrix in the device
	 * before the geometry is rendered
	 */
	virtual const math::VRBTransform& GetModelTransform() const = 0;

	static std::string GetDefaultId() { return IVGraphicsPart::GetDefaultId(); }
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::IVShapePart, v3d::scene::IVGraphicsPart);
//-----------------------------------------------------------------------------
#endif // V3D_IVSHAPEPART_2005_09_22_H

