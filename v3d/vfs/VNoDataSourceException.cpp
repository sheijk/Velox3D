///////////////////////////////////////////////////////////
//
//  VNoDataSourceException.cpp
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

#include "VNoDataSourceException.h"

using std::string;

VNoDataSourceException::~VNoDataSourceException(){

}
 
VNoDataSourceException::VNoDataSourceException(string in_strReason, string in_strFileName, vuint in_nLineNumber)
	: VIOException(in_strReason, in_strFileName, in_nLineNumber)
{

}
