#include <V3d/Core.h>
#include <V3d/Entity/VEntityManager.h>

using namespace v3d;
using namespace v3d::entity;
using v3d::utils::VFourCC;

//-----------------------------------------------------------------------------

class VDataPart : public IVPart
{
	vint data;
public:
	VDataPart(vint d) { data = d; }

	void Activate()
	{
		vout << "activating VDataPart, " << data << vendl;
	}

	void Deactivate()
	{
		vout << "deactivating VDataPart" << vendl;
	}

	vint GetData() { return data; }
	void SetData(int d) { data = d; }
};

class VSettingPart : public IVPart
{
	VDataPart* pData;
public:
	void Activate()
	{
		if( pData == 0 )
			V3D_THROW(VMissingPartException, "missing part 'data'");

		vout << "activating setter part" << vendl;
		vout << "data = " << pData->GetData() << vendl;
	}

	void Deactivate() 
	{
		vout << "deactivating setter part" << vendl;
	}

	virtual void TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part)
	{
		pData = in_Part.Convert<VDataPart>();
	}
};

/**
 * Rudimentary demo of the entity system.
 *
 * @author sheijk
 */
class VEntityDemoApp : public VVeloxApp
{
public:
	virtual vint Main(std::vector<std::string> args);
};

vint VEntityDemoApp::Main(std::vector<std::string> args)
{
	VEntity ent;
	VEntity::PartPtr pDataPart(new VDataPart(5));
	VEntity::PartPtr pSettingPart(new VSettingPart());
	ent.AddPart(VFourCC("data"), pDataPart);
	ent.AddPart(VFourCC("sett"), pSettingPart);

	ent.Activate();
	ent.Deactivate();
	
	return 0;
}

//-----------------------------------------------------------------------------
namespace {
	VEntityDemoApp g_theApp;
}
