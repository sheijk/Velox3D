#ifndef VXMLSERVICE_H
#define VXMLSERVICE_H

#include <V3d/XML/IVXMLService.h>
#include "VXMLWriter.h"
#include "tinyxml/tinyxml.h" //TODO [ins]
#include "VXMLAttribute.h"
#include "VXMLElement.h"


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
	virtual void ParseXMLFile(VStringParam in_pcName, IVXMLVisitor* in_pVisitor);
	//virtual IVXMLWriter* CreateXMLWriter(IVStream* in_pStream);
	virtual IVXMLWriter* CreateXMLWriter();

private:


	void TraversalNodes(TiXmlNode* node);
	VXMLElement* TraversalAttributes(TiXmlElement* Element);

	IVXMLVisitor* m_Vistor;

};

}
}


#endif
