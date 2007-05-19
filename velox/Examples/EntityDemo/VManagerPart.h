#ifndef V3D_VMANAGERPART_2005_05_20_H
#define V3D_VMANAGERPART_2005_05_20_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Core/VIOStream.h>

#include <V3d/Entity/VUnconnectedPart.h>
#include <V3d/Entity/VEntityExceptions.h>

#include <string>
#include <set>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VReaderPart;

/**
 * @author sheijk
 */
class VManagerPart : public entity::VUnconnectedPart
{
protected:
	void OnActivate()
	{
		vout << "VManagerPart activated" << vendl;
	}

	void OnDeactivate()
	{
		vout << "VManagerPart deactivated" << vendl;
	}

public:
	void Register(VReaderPart* in_pPart)
	{
		m_Readers.insert(in_pPart);
	}

	void Unregister(VReaderPart* in_pPart)
	{
		m_Readers.erase(in_pPart);
	}

	static std::string GetDefaultId()
	{
		return std::string("mngr");
	}

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

	void PrintAllValues();

private:
	std::set<VReaderPart*> m_Readers;
};

//-----------------------------------------------------------------------------
} // namespace v3d

V3D_TYPEINFO_WITHPARENT(v3d::VManagerPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VMANAGERPART_2005_05_20_H
