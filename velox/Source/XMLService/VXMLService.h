#ifndef VXMLSERVICE_H
#define VXMLSERVICE_H

#include "IVXMLService.h" //TODO
#include "VXMLWriter.h"

#include <string.h>
#include <stdarg.h>

//#include <v3d/Core/Wrappers/VString.h>

namespace v3d
{
namespace xml
{

using namespace v3d::vfs;

class VXMLService :	public IVXMLService
{
public:
	VXMLService(void);
	virtual	~VXMLService(void);

//	virtual void ParseXMLFile(IVStream* in_pStream, IVXMLVisitor* in_pVisitor);
//	virtual void ParseXMLFile(char* in_pcName, IVXMLVisitor* in_pVisitor);
	//virtual IVXMLWriter* CreateXMLWriter(IVStream* in_pStream);
	virtual IVXMLWriter* CreateXMLWriter();

};

}
}


#endif
