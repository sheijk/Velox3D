/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VGLSLPARAMETER_2005_11_26_H
#define V3D_VGLSLPARAMETER_2005_11_26_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVParameter.h>
#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VGLSLParameter : public IVParameter
{
public:
	VGLSLParameter(GLhandleARB in_hProgram, VStringParam in_strName, Type in_Type);
	virtual ~VGLSLParameter();

	virtual std::string GetName() const;
	virtual Type GetType() const;

	virtual void Apply(vfloat32 in_fNewValue) const;
	virtual vfloat32 AsFloat() const;
	virtual void Apply(const math::VVector2f& in_NewValue) const;
	virtual math::VVector2f AsFloat2() const;
	virtual void Apply(const math::VVector4f& in_NewValue) const;
	virtual math::VVector4f AsFloat4() const;

	virtual math::VMatrix44f AsFloat44() const;
	virtual void Apply(const math::VMatrix44f& in_NewValue) const;

	virtual void Apply(vint in_nNewValue) const;
	virtual vint AsInt() const;

	virtual void Apply(vbool in_bNewValue) const;
	virtual vbool AsBool() const;

	virtual void ApplyTexture(VStringParam in_strResourceName) const;
	virtual std::string TextureResource() const;

protected:
	GLint GetLocation() const;
	GLhandleARB GetProgram() const;

private:
	std::string m_strName;

	GLint m_Location;
	GLhandleARB m_hProgram;

	Type m_Type;

	static GLfloat m_fTempBuffer[16];
	static GLint m_iTempBuffer[16];
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VGLSLPARAMETER_2005_11_26_H

