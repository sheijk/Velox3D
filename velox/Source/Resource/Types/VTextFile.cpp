#include <V3d/Resource/Types/VTextFile.h>
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
VTextFile::VTextFile()
{
}

VTextFile::VTextFile(const std::string& in_strContent)
{
	m_strContent = in_strContent;
}

/**
 * d'tor
 */
VTextFile::~VTextFile()
{
}

std::string VTextFile::GetContent() const
{
	return m_strContent;
}

void VTextFile::SetContent(const std::string& in_TrContent)
{
	m_strContent = in_TrContent;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
