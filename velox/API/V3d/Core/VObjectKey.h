#ifndef V3D_VOBJECTKEY_H
#define V3D_VOBJECTKEY_H
//------------------------------------------------------------------------
#include <string>

#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * key to identify registered objects in the object registry
 */
class VObjectKey
{
private:

	// the name of it..
	std::string m_strName;
public:
	VObjectKey();

	/** create with name */
	VObjectKey(const std::string& in_strName);

	/** create with name */
	VObjectKey(const char* in_pcName);

	/** destructor.. */
	virtual ~VObjectKey();

	/** convert to string */
	const std::string& ToString() const;

	bool operator<(const VObjectKey& in_Other) const
	{
		return m_strName < in_Other.m_strName;
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//------------------------------------------------------------------------
#endif // V3D_VOBJECTKEY_H
