/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDEPTHSTATE_2006_01_21_H
#define V3D_VDEPTHSTATE_2006_01_21_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VRenderPass;

/**
 * @author sheijk
 */
class VDepthState
{
public:
	VDepthState();
	virtual ~VDepthState();

	void Parse(const VRenderPass& in_Pass);

	void Apply() const;
	void Unapply() const;

	vuint GetDepthFunction() const { return m_DepthFunction; }
	void SetDepthFunction(const vuint& in_Value) { m_DepthFunction = in_Value; }
	vbool GetDepthWrite() const { return m_bDepthWrite; }
	void SetDepthWrite(const vbool& in_Value) { m_bDepthWrite = in_Value; }
	vbool GetDepthTestEnabled() const { return m_bDepthTestEnabled; }
	void SetDepthTestEnabled(const vbool& in_Value) { m_bDepthTestEnabled = in_Value; }
private:
	vuint m_DepthFunction;
	vbool m_bDepthWrite;
	vbool m_bDepthTestEnabled;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VDEPTHSTATE_2006_01_21_H

