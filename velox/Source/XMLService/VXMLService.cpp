#include "VXMLService.h"

namespace v3d
{
namespace xml
{

VXMLService::VXMLService(void) : IVXMLService("XmlService", 0)
{
}

VXMLService::~VXMLService(void)
{
}

IVXMLWriter* VXMLService::CreateXMLWriter()
{
	VXMLWriter* Writer = new VXMLWriter();
	return Writer;

}

/*IVXMLWriter* VXMLService::CreateXMLWriter(IVStream* in_pStream)
{
	return NULL;
}

void VXMLService::ParseXMLFile(char* in_pcName, IVXMLVisitor* in_pVisitor)
{
}

void VXMLService::ParseXMLFile(IVStream* in_pStream, IVXMLVisitor* in_pVisitor)
{
}

*/







}
}