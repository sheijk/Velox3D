#ifndef V3D_VTEXTFILE_2005_10_31_H
#define V3D_VTEXTFILE_2005_10_31_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/VTypeInfo.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VTextFile
{
public:
	VTextFile();
	VTextFile(const std::string& in_strContent);
	virtual ~VTextFile();

	std::string GetContent() const;
	void SetContent(const std::string& in_strContent);

private:
	std::string m_strContent;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource

V3D_TYPEINFO(v3d::resource::VTextFile);
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTFILE_2005_10_31_H