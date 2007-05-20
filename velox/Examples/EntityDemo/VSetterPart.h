#ifndef V3D_VSETTERPART_2004_10_10_H
#define V3D_VSETTERPART_2004_10_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>
#include <V3d/Entity/VEntityExceptions.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VSettingPart : public entity::IVPart
{
	entity::VNodeConnection<VDataPart> pData;
	//VDataPart* pData;
public:
	VSettingPart() :
		// create connection + make it known to parent
		pData(RegisterTo())
	{
	}

protected:
	void OnActivate()
	{
		if( pData.Get() == 0 )
			V3D_THROW(entity::VMissingPartException, "missing part 'data'");

		vout << "activating setter part" << vendl;
		vout << "data = " << pData->GetData() << vendl;
	}

	void OnDeactivate() 
	{
		vout << "deactivating setter part" << vendl;
	}

public:
	virtual vbool IsReady() const
	{
		return pData.Get() != 0;
	}

	void SetValue(int v)
	{
		V3D_ASSERT(pData.Get() != 0);

		pData->SetData(v);
	}

	static std::string GetDefaultId()
	{
		return std::string("setr");
	}

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
};

//-----------------------------------------------------------------------------
} // namespace v3d

V3D_TYPEINFO_WITHPARENT(v3d::VSettingPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VSETTERPART_2004_10_10_H
