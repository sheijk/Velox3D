/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VXMLSERVICE_H
#define V3D_VXMLSERVICE_H
//-----------------------------------------------------------------------------
#include <V3d/XML/IVXMLService.h>
//-----------------------------------------------------------------------------
#include "VXMLWriter.h"
#include "TinyXml/tinyxml.h"
#include "VXMLAttribute.h"
#include "VXMLElement.h"
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
    
	virtual IVXMLElementPtr GetRootElement(IVStream* in_pStream); 
	virtual IVXMLElementPtr GetRootElement(VStringParam in_strName); 

	virtual bool Visit(IVXMLVisitor& in_Visitor, IVStream& in_Stream);
	virtual bool Visit(IVXMLVisitor& in_Visitor, VStringParam in_strFile);
	
	virtual IVXMLWriterPtr CreateXMLWriter(VStringParam FileName);
	virtual IVXMLWriterPtr CreateXMLWriter(IVStreamPtr pStream);

	virtual VSharedPtr<IVXMLElement> CreateEmptyElement(VStringParam in_strName = 0);
private: 
	VXMLElement* BeginTranslation(TiXmlDocument& in_Doc);

	IVXMLNode* TranslateNode(TiXmlNode* in_pNode);
	VXMLElement* TranslateElement(TiXmlElement* in_pElement);

	IVXMLVisitor* m_Vistor;
	vbool m_bRecursionFirstCall;
	std::stack<std::string> m_LastElementNameList;
};

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLSERVICE_H

