#ifndef V3D_VREADERPART_2004_10_10_H
#define V3D_VREADERPART_2004_10_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VPartBase.h>
#include <V3d/Entity/VEntityExceptions.h>

#include "VDataPart.h"
#include "VManagerPart.h"

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VReaderPart : public entity::VPartBase
{
	entity::VPartConnection<VDataPart> pData;
	entity::VPartConnection<VManagerPart> pManager;
	//VDataPart* pData;

public:
	VReaderPart() :
		pData(entity::VPartDependency::Neighbour, RegisterTo()),
		pManager(entity::VPartDependency::Ancestor, RegisterTo())
	{
	}

	void Activate()
	{
		if( pData.Get() == 0 )
			V3D_THROW(entity::VMissingPartException, "missing part 'data'");

		vout << "activating VReaderPart" << vendl;

		pManager->Register(this);
	}

	void Deactivate()
	{
		vout << "deactivating VReaderPart" << vendl;
		pManager->Unregister(this);
	}

	virtual vbool IsReady() const
	{
		return pData.Get() != 0 &&
			pManager.Get() != 0;
	}

	//void TellNeighbourPart(const std::string& in_Id, IVPart& in_Part)
	//{
	//	if( in_Part.IsOfType<VDataPart>() )
	//		pData = in_Part.Convert<VDataPart>();
	//}

	void PrintValue()
	{
		V3D_ASSERT(pData.Get() != 0);

		vout << "value = " << pData->GetData() << vendl;
	}

	static std::string GetDefaultId()
	{
		return std::string("read");
	}

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
};

//-----------------------------------------------------------------------------
} // namespace v3d

V3D_TYPEINFO_WITHPARENT(v3d::VReaderPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VREADERPART_2004_10_10_H
