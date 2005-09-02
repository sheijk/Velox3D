#ifndef V3D_VSETTERPART_2004_10_10_H
#define V3D_VSETTERPART_2004_10_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VPartBase.h>
#include <V3d/Entity/VEntityExceptions.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VSettingPart : public entity::VPartBase
{
	entity::VPartConnection<VDataPart> pData;
	//VDataPart* pData;
public:
	VSettingPart() :
		// create connection + make it known to parent
		pData(entity::VPartDependency::Neighbour, RegisterTo())
	{
	}

	void Activate()
	{
		if( pData.Get() == 0 )
			V3D_THROW(entity::VMissingPartException, "missing part 'data'");

		vout << "activating setter part" << vendl;
		vout << "data = " << pData->GetData() << vendl;
	}

	void Deactivate() 
	{
		vout << "deactivating setter part" << vendl;
	}

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
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSETTERPART_2004_10_10_H
