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
using namespace v3d::vfs;
//-----------------------------------------------------------------------------

/**
 * Implements the XML service interface
 */
class VXMLService :	public IVXMLService
{
public:

	typedef VException VXMLException;
	VXMLService(void);
	virtual	~VXMLService(void);

	virtual void ParseXMLFile(IVStream* in_pStream, IVXMLVisitor* in_pVisitor);
	virtual void ParseXMLFile(VStringParam in_pcName, IVXMLVisitor* in_pVisitor);
	virtual IVXMLWriterPtr CreateXMLWriter(VStringParam FileName);
	virtual IVXMLWriterPtr CreateXMLWriter(IVStream* pStream);

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
