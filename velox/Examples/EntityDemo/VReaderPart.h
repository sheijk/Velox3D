#ifndef V3D_VREADERPART_2004_10_10_H
#define V3D_VREADERPART_2004_10_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>
#include <V3d/Entity/VEntityExceptions.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VReaderPart : public entity::IVPart
{
	VDataPart* pData;

public:
	void Activate()
	{
		if( pData == 0 )
			V3D_THROW(entity::VMissingPartException, "missing part 'data'");

		vout << "activating VReaderPart" << vendl;
	}

	void Deactivate()
	{
		vout << "deactivating VReaderPart" << vendl;
	}

	void TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part)
	{
		if( in_Part.IsOfType<VDataPart>() )
			pData = in_Part.Convert<VDataPart>();
	}

	void PrintValue()
	{
		vout << "value = " << pData->GetData() << vendl;
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VREADERPART_2004_10_10_H
