#ifndef V3D_VOPTION_2006_07_18_H
#define V3D_VOPTION_2006_07_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <string>

//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Base class for an option of VMessageInterpreter
 *
 * @author sheijk
 * @see v3d::scene::VMessageInterpreter
 * @see v3d::entity::IVPart
 */
class VOption
{
public:
	VOption(const std::string& name);
	virtual ~VOption();

	virtual void Write(const std::string& value, void* object) = 0;
	virtual std::string Read(void* object) = 0;

	std::string GetName() const;
	void SetName(const std::string& in_Value);
private:
	std::string m_strName;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------
#endif // V3D_VOPTION_2006_07_18_H
