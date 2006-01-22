#ifndef V3D_VMISCSTATE_H
#define V3D_VMISCSTATE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "States/VDepthState.h"

#include <v3d/Graphics/VEffectDescription.h>

#include <V3dLib/Graphics/Geometry/VColor4f.h>
#include <V3dLib/Graphics/Materials/StateTypes.h>

#include <V3dLib/Property.h>

#include "IVOpenGLRenderState.h"
#include <V3d/Math.h>

#include <V3d/OpenGL.h>

#include <memory>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

template<typename T>
class VPropertyConnection
{
	mutable T m_Value;
	std::auto_ptr< property::VProperty<T> > m_pProperty;

public:
	void Connect(std::string value)
	{
		if( value[0] == '@' )
		{
			std::string propertyName(++value.begin(), value.end());
			m_pProperty.reset(new property::VProperty<T>(propertyName));
		}
		else
		{
			m_pProperty.reset(0);
			utils::VStringValue v(value.c_str());
			m_Value = v.Get<T>();
		}
	}

	void Set(T val)
	{
		m_pProperty.reset(0);
		m_Value = val;
	}

	T Get() const
	{
		if( m_pProperty.get() != 0 )
		{
			m_Value = m_pProperty->Get();
		}

		return m_Value;
	}
};

/**
 * @author sheijk
 */
class VMiscState : public IVOpenGLRenderState
{
public:
	VMiscState(const VRenderPass& in_Pass);

	virtual const IVStateCategory* GetCategory() const;

	virtual void Apply() const;

	static void SetCategory(IVStateCategory* in_pCategory);
private:
	typedef VPolygonMode PolygonMode;
	typedef VDepthTest DepthTest;
	typedef VBlendFactor BlendMode;

	static IVStateCategory* m_pStateCategory;

	// texture matrix state
	VPropertyConnection<VMatrix44f> m_TextureMatrix;

	// texture generation mode
	VTexGenMode m_TextureGenerationMode;

	// alpha blending
	vuint m_SourceFactor;
	vuint m_DestFactor;
	vbool m_bBlendingEnabled;

	// polygon mode (lines, filled, points,..)
	vuint m_nFrontPolygonMode;
	vuint m_nBackPolygonMode;

	// z buffer / depth test
	VDepthState m_DepthState;
	//vuint m_DepthFunction;
	//vbool m_bDepthWrite;
	//vbool m_bDepthTestEnabled;

	// lighting
	vbool m_bEnableLighting;

	VColorBufferMask m_ColorMask;

	VPropertyConnection<vfloat32> m_Red;
	VPropertyConnection<vfloat32> m_Green;
	VPropertyConnection<vfloat32> m_Blue;
	VPropertyConnection<vfloat32> m_Alpha;
	//v3d::graphics::VColor4f m_DefaultColor;

	static vuint GetGLModeNum(const DepthTest in_Test);
	static vuint GetGLModeNum(const PolygonMode in_Mode);
	static vuint GetGLModeNum(BlendMode in_Mode);

	void ReadColor(const VRenderPass& in_Pass);
	static vuint GetPolygonMode(const std::string& in_strMode);
	static vuint GetDepthFunction(const std::string& in_strFunction);
	static vuint GetBlendFunction(const std::string& in_strFunction);
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMISCSTATE_H
