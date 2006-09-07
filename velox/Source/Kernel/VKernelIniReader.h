/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VKERNELINIREADER_H
#define V3D_VKERNELINIREADER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/XML/IVXMLVisitor.h>
//-----------------------------------------------------------------------------
#include "VServiceProxy.h"
//-----------------------------------------------------------------------------
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace kernel{
//-----------------------------------------------------------------------------


/**
 * Parsers the kernel init file with help of the xml service
 */

class VKernelIniReader : public xml::IVXMLVisitor
{
private:

	typedef VPointer<VServiceProxy>::SharedPtr ServicePointer;
	typedef std::list<ServicePointer> ServiceList;

	virtual void OnElementClose(xml::IVXMLElement* pElement);
	virtual void OnElementOpen(xml::IVXMLElement* pElement);
	virtual void OnFileEnd();
	virtual void OnComment(VStringParam pText);
	virtual void OnText(VStringParam pText);

	enum State
	{
		ConfigState,
		ServiceState,
		ServiceElementState,
		MainState
	};

	vuint m_State;
	ServiceList* m_pServiceList;
	std::string m_AppName;


public:

	VKernelIniReader(ServiceList* in_pServiceList);
	virtual ~VKernelIniReader();
	VStringParam GetAppName();
};

//-----------------------------------------------------------------------------
} // namespace v3d
} // namespace kernel
//-----------------------------------------------------------------------------
#endif // V3D_VKERNELINIREADER_H

