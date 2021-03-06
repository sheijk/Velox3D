/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VERRORSERVICE_H
#define V3D_VERRORSERVICE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VNamedObject.h>
#include <V3d/Error/IVErrorService.h>
#include <list>
#include <utility>

//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

class IVErrorListener;

/**
 * A service which implements the error interface
 */
class VErrorService : public IVErrorService
{
private:
	//typedef VPointer<IVErrorStream>::SharedPtr ErrorStreamPtr;
	typedef std::pair< IVErrorFilter*, IVErrorListener*> FLPair;

	ErrorStreamPtr m_GlobalErrorStream;

	std::list< FLPair >	m_Listeners;
	std::list< FLPair >::iterator m_Iter;

public:
	VErrorService();
	virtual ~VErrorService();

	virtual vbool RegisterListener( IVErrorListener* in_pListener, IVErrorFilter* in_pFilter );
	virtual void  UnregisterListener( IVErrorListener* in_pListener );

	virtual ErrorStreamPtr GetGlobalErrorStream();
	virtual ErrorStreamPtr CreateErrorStream( VStringParam in_strName );

	void BeginProgressbar( VStringParam in_strStreamName );
	void UpdateProgressbar( VStringParam in_strStreamName, vfloat32 in_fIndex );
	void EndProgressbar( VStringParam in_strStreamName );

	void UpdateState( VStringParam in_strStreamName, VStringParam in_strText );

	void Message( VStringParam in_strStreamName,
				  VStringParam in_strMessage,
				  VMessageType inMessageType,
				  VStringParam in_strFile,
				  vuint in_nLine );
};

//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------
#endif // V3D_VERRORSERVICE_H

