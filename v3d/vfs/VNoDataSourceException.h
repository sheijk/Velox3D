///////////////////////////////////////////////////////////
//
//  VNoDataSourceException.h
//  Implementation of the Class VNoDataSourceException
//  Generated by Enterprise Architect
//  Created on:      25-Feb-2003 01:11:02
//  Original author: sheijk
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(VNoDataSourceException_9B929B2E_326A_4d06_B5CB_0BF1438AA048__INCLUDED_)
#define VNoDataSourceException_9B929B2E_326A_4d06_B5CB_0BF1438AA048__INCLUDED_

#include "VIOException.h"

class VNoDataSourceException : public VIOException
{

public:
	VNoDataSourceException(std::string in_strReason, std::string in_strFileName, vuint in_nLineNumber);

	virtual ~VNoDataSourceException();
};

#endif // !defined(VNoDataSourceException_9B929B2E_326A_4d06_B5CB_0BF1438AA048__INCLUDED_)