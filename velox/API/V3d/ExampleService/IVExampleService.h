#ifndef V3D_IVEXAMPLESERVICE_H
#define V3D_IVEXAMPLESERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace example {
//-----------------------------------------------------------------------------

/**
 * An example service. Provides a function which returns the number 5
 */
class IVExampleService : public VNamedObject
{
//	IVExampleService();
public:
	IVExampleService(std::string in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent)
	{
	}

	virtual vint GiveMeFive() = 0;
};

//-----------------------------------------------------------------------------
} // example 
} // v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVEXAMPLESERVICE_H