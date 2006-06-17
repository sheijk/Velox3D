#ifndef V3D_VTAG_2006_05_31_H
#define V3D_VTAG_2006_05_31_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace tags {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VTag
{
public:
	~VTag();

	vuint32 GetId() const;
	std::string GetName() const;

	vbool operator==(const VTag& other) const;
	vbool operator!=(const VTag& other) const;
private:
	friend class VTagRegistry;

	VTag(const std::string& name, vuint32 id);

	std::string m_strName;
	vuint32 m_Id;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::tags
//-----------------------------------------------------------------------------
#endif // V3D_VTAG_2006_05_31_H
