/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VERRORSTREAM_H
#define V3D_VERRORSTREAM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//#include <v3d/Error/IVErrorService.h>
#include "VErrorService.h"
#include <sstream>
//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

class VErrorStream : public IVErrorStream
{
public:
			VErrorStream(VStringParam in_strName, VErrorService* in_pErrorService);
	virtual ~VErrorStream();
	
	virtual void BeginProgressbar();
	virtual void UpdateProgressbar(vfloat32 in_fIndex);
	virtual void EndProgressbar();
	virtual void UpdateState(VStringParam in_strText );
	virtual VStringRetVal GetName();

	virtual void SetLine( vuint in_nLine );
	virtual void SetFile( VStringParam in_strLine );
	virtual void SetMessageType( VMessageType in_MessageType );
	
	virtual void Write( VStringParam in_strString );
	virtual void Flush();

protected:
	std::string			m_strName;
	VErrorService*		m_pParent;
	std::string			m_strFile;
	vuint				m_nLine;
	VMessageType		m_MessageType;
	std::ostringstream	m_oStream;
};

//-----------------------------------------------------------------------------
} // namespace error
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VERRORSTREAM_H

