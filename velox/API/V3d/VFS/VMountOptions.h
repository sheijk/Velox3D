#ifndef V3D_VMountOptions_H
#define V3D_VMountOptions_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Information for mounting something (i.e. a directory) to the virtual
 * file system.
 */
struct VMountOptions
{
	VString m_strName;
	VString m_strSource;
	VString m_strOptions;
	VString m_strType;

public:
	VMountOptions();

	VMountOptions(
		VStringParam name, VStringParam source, 
		VStringParam options, VStringParam type)
		: m_strName(name), m_strSource(source), m_strOptions(options),
		m_strType(type)
	{}

	virtual ~VMountOptions() {}

	const VString& GetName() const;
	const VString& GetType() const;
	const VString& GetOptions() const;
	const VString& GetSource() const;

	void SetName(VStringParam name) { m_strName = name; }
	void SetSource(VStringParam source) { m_strSource = source; }
	void SetOptions(VStringParam opt) { m_strOptions = opt; }
	void SetType(VStringParam type) { m_strType = type; }
};

//-----------------------------------------------------------------------------
#include "VMountOptions.inl"
//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMountOptions_H
