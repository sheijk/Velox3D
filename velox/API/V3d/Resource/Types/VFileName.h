//TODO: add file creation date to file guard
#ifndef V3D_VFILENAME_H
#define V3D_VFILENAME_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VFileName
{
public:
	VFileName(VStringParam in_strName);
	virtual ~VFileName();

	const std::string& AsString() const;

private:
	std::string m_strName;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
#endif // V3D_VFILENAME_H