#ifndef V3D_VXMLSERVICE_H
#define V3D_VXMLSERVICE_H
//-----------------------------------------------------------------------------
#include <V3d/XML/IVXMLService.h>
//-----------------------------------------------------------------------------
#include "VXMLWriter.h"
#include "tinyxml/tinyxml.h"
#include "VXMLAttribute.h"
#include "VXMLElement.h"
#include "VStreamReader.h"
//-----------------------------------------------------------------------------
#include <string.h>
#include <stdarg.h>
#include <string>
#include <stack>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * Implements the XML service interface
 */
class VXMLService :	public IVXMLService
{
public:
	VXMLService();
	virtual	~VXMLService();

	virtual void ParseXMLFile(IVStream* in_pStream, IVXMLVisitor* in_pVisitor);

	virtual void ParseLocalXMLFile(
		VStringParam in_pcName, IVXMLVisitor* in_pVisitor);
	
	virtual void ParseVfsXMLFile(
		VStringParam in_pcName, IVXMLVisitor* in_pVisitor);
	
	virtual IVXMLWriterPtr CreateXMLWriter(VStringParam FileName);
	
	virtual IVXMLWriterPtr CreateXMLWriter(IVStreamPtr pStream);

private: 
	void TraversalNodes(TiXmlNode* node);
	VXMLElement* TraversalAttributes(TiXmlElement* Element);

	IVXMLVisitor* m_Vistor;
	vbool m_bRecursionFirstCall;
	std::stack<std::string> m_LastElementNameList;

};

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLSERVICE_H
