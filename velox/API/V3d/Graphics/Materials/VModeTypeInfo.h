#ifndef V3D_VMODETYPEINFO_2004_09_23_H
#define V3D_VMODETYPEINFO_2004_09_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/GraphicsExceptions.h>
#include <V3d/Graphics/Materials/StateTypes.h>
#include <V3d/OpenGL.h>
#include <V3d/CG.h>

#include <sstream>
#include <string>
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * Stores triples of gl enums, names and a user defined type
 * The corresponding name, gl enum or user type can be retrieved from each of
 * the two other types.
 * 
 * @author sheijk
 */
template<typename ModeType, typename Enum = GLenum>
class VModeTypeInfo
{
	struct ModeInfo
	{
		std::string name;
		ModeType mode;
		Enum glenum;
	};

	std::vector<ModeInfo> m_Modes;

public:
	void AddModeInfo(ModeType mode, const std::string& name, Enum glmode);

	ModeType GetMode(const std::string& name);
	ModeType GetMode(Enum glmode);

	Enum GetGLEnum(ModeType mode);
	Enum GetGLEnum(const std::string& name);

	std::string GetName(ModeType mode);
	std::string GetName(Enum glmode);
};

// info about mode names and gl enums
VModeTypeInfo<VPolygonMode> GetPolygonModeInfo();
VModeTypeInfo<VDepthTest> GetDepthTestInfo();
VModeTypeInfo<VBlendFactor> GetBlendFactorInfo();
VModeTypeInfo<VTextureWrapMode> GetTextureWrapModeInfo();
VModeTypeInfo<VTextureFilter> GetTextureFilterInfo();
VModeTypeInfo<VTexGenMode> GetTexGenModeInfo();
VModeTypeInfo<VShaderType, CGprofile> GetShaderTypeInfo();
//-----------------------------------------------------------------------------

template<typename ModeType, typename Enum>
void VModeTypeInfo<ModeType, Enum>::AddModeInfo(
	ModeType mode, const std::string& name, Enum glmode)
{
	ModeInfo info;
	info.name = name;
	info.mode = mode;
	info.glenum = glmode;

	m_Modes.push_back(info);
}

template<typename ModeType, typename Enum>
ModeType VModeTypeInfo<ModeType, Enum>::GetMode(const std::string& name)
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

template<typename ModeType, typename Enum>
ModeType VModeTypeInfo<ModeType, Enum>::GetMode(Enum glmode)
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

template<typename ModeType, typename Enum>
Enum VModeTypeInfo<ModeType, Enum>::GetGLEnum(const std::string& name)
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

template<typename ModeType, typename Enum>
Enum VModeTypeInfo<ModeType, Enum>::GetGLEnum(ModeType mode)
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

template<typename ModeType, typename Enum>
std::string VModeTypeInfo<ModeType, Enum>::GetName(ModeType mode)
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

template<typename ModeType, typename Enum>
std::string VModeTypeInfo<ModeType, Enum>::GetName(Enum glmode)
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
