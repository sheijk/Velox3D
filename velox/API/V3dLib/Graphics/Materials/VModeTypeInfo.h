#ifndef V3D_VMODETYPEINFO_2004_09_23_H
#define V3D_VMODETYPEINFO_2004_09_23_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Graphics/GraphicsExceptions.h>
#include <V3dLib/Graphics/Materials/StateTypes.h>

#include <sstream>
#include <string>
#include <vector>

#include <windows.h>
#include <gl/GL.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

template<typename ModeType>
class VModeTypeInfo
{
	struct ModeInfo
	{
		std::string name;
		ModeType mode;
		GLenum glenum;
	};

	std::vector<ModeInfo> m_Modes;

public:
	void AddModeInfo(ModeType mode, const std::string& name, GLenum glmode);

	ModeType GetMode(const std::string& name);
	ModeType GetMode(GLenum glmode);

	GLenum GetGLEnum(ModeType mode);
	GLenum GetGLEnum(const std::string& name);

	std::string GetName(ModeType mode);
	std::string GetName(GLenum glmode);
};

// info about mode names and gl enums
VModeTypeInfo<VPolygonMode>	GetPolygonModeInfo();
VModeTypeInfo<VDepthTest>	GetDepthTestInfo();
VModeTypeInfo<VBlendFactor>	GetBlendFactorInfo();
VModeTypeInfo<VTextureWrapMode> GetTextureWrapModeInfo();
VModeTypeInfo<VTextureFilter>	GetTextureFilterInfo();

//-----------------------------------------------------------------------------

template<typename ModeType>
void VModeTypeInfo<ModeType>::AddModeInfo(
	ModeType mode, const std::string& name, GLenum glmode)
{
	ModeInfo info;
	info.name = name;
	info.mode = mode;
	info.glenum = glmode;

	m_Modes.push_back(info);
}

template<typename ModeType>
ModeType VModeTypeInfo<ModeType>::GetMode(const std::string& name)
{
	for(vuint i = 0; i < m_Modes.size(); ++i)
	{
		if( m_Modes[i].name == name )
		{
			return m_Modes[i].mode;
		}
	}

	std::stringstream str;
	str << "Mode name '" << name << "' is not valid\n";

	V3D_THROW(VInvalidModeException, str.str().c_str());
}

template<typename ModeType>
ModeType VModeTypeInfo<ModeType>::GetMode(GLenum glmode)
{
	for(vuint i = 0; i < m_Modes.size(); ++i)
	{
		if( m_Modes[i].glenum == glmode )
		{
			return m_Modes[i].mode;
		}
	}

	std::stringstream str;
	str << "OpenGL enum '" << glmode << "' is not valid\n";

	V3D_THROW(VInvalidModeException, str.str().c_str());
}

template<typename ModeType>
GLenum VModeTypeInfo<ModeType>::GetGLEnum(const std::string& name)
{
	for(vuint i = 0; i < m_Modes.size(); ++i)
	{
		if( m_Modes[i].name == name )
		{
			return m_Modes[i].glenum;
		}
	}

	std::stringstream str;
	str << "Mode name '" << name << "' is not valid\n";

	V3D_THROW(VInvalidModeException, str.str().c_str());
}

template<typename ModeType>
GLenum VModeTypeInfo<ModeType>::GetGLEnum(ModeType mode)
{
	for(vuint i = 0; i < m_Modes.size(); ++i)
	{
		if( m_Modes[i].mode == mode )
		{
			return m_Modes[i].glenum;
		}
	}

	std::stringstream str;
	str << "Mode type '" << mode << "' is not valid\n";

	V3D_THROW(VInvalidModeException, str.str().c_str());
}

template<typename ModeType>
std::string VModeTypeInfo<ModeType>::GetName(ModeType mode)
{
	for(vuint i = 0; i < m_Modes.size(); ++i)
	{
		if( m_Modes[i].mode == mode )
		{
			return m_Modes[i].name;
		}
	}

	std::stringstream str;
	str << "Mode type '" << mode << "' is not valid\n";

	V3D_THROW(VInvalidModeException, str.str().c_str());
}

template<typename ModeType>
std::string VModeTypeInfo<ModeType>::GetName(GLenum glmode)
{
	for(vuint i = 0; i < m_Modes.size(); ++i)
	{
		if( m_Modes[i].glenum == glmode )
		{
			return m_Modes[i].name;
		}
	}

	std::stringstream str;
	str << "OpenGL enum '" << glmode << "' is not valid\n";

	V3D_THROW(VInvalidModeException, str.str().c_str());
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VMODETYPEINFO_2004_09_23_H
