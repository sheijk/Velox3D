#ifndef V3D_EXAMPLESERVICE_H
#define V3D_EXAMPLESERVICE_H
//-----------------------------------------------------------------------------
#include <Kernel/ObjReg/VNamedObject.h>
//-----------------------------------------------------------------------------
#include <string>

/**
 * An example service
 */
class VExampleService : public VNamedObject  
{
private:
	/** The service's identifier */
	static const std::string s_strId;

public:
	VExampleService();
	virtual ~VExampleService();

	/** get the id under which the service can be accessed */
	static const std::string& GetServiceId();
};

//-----------------------------------------------------------------------------
#endif // V3D_EXAMPLESERVICE_H
