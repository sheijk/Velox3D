#ifndef IVFileStream_h
#define IVFileStream_h

#include "IVStream.h"

//! interface for streams that are connected to files or other external data sources
class IVFileStream : public IVStream  
{
public:
	//! close the connected data source
	virtual void Close() = 0;
};

#endif // IVFileStream_h
