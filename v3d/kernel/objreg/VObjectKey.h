#ifndef VOBJECTKEY_H
#define VOBJECTKEY_H
//------------------------------------------------------------------------
#include <string>

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

	/** destructor.. */
	virtual ~VObjectKey();

	/** convert to string */
	const std::string& toString() const;

	bool operator<(const VObjectKey& in_Other) const
	{
		return m_strName < in_Other.m_strName;
	}
};

//------------------------------------------------------------------------
#endif // VOBJECTKEY_H
