#ifndef V3D_IVEXAMPLESERVICE_H
#define V3D_IVEXAMPLESERVICE_H
//-----------------------------------------------------------------------------
#include <Kernel/ObjReg/VNamedObject.h>

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
#endif // V3D_IVEXAMPLESERVICE_H