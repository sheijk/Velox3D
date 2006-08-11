#include <V3d/Resource/Types/VFileName.h>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VFileName::VFileName(VStringParam in_strName)
{
	m_strName = in_strName;
}

VFileName::VFileName(const std::string& in_strName)
{
	m_strName = in_strName;
}

/**
 * d'tor
 */
VFileName::~VFileName()
{
}

const std::string& VFileName::AsString() const
{
	return m_strName;
}

VFileName VFileName::Append(const std::string& in_strName) const
{
    std::string fileName = m_strName;
	char last = '/';
	if( fileName.size() > 1 )
		last = fileName[fileName.size()-1];

	if( last != '/' && last != '\\' )
		fileName += "/";

	return VFileName(fileName + in_strName);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
