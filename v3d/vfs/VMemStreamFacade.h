#ifndef VMEMSTREAMFACADE_H
#define VMEMSTREAMFACADE_H

#include <vfs\\IVStream.h>
#include <memory.h>

class VMemStreamFacade : public IVStream
{
private:
	//! thats the main buffer
	void* m_pBuffer;

	//! length of the buffer
	vlong m_SizeofBuffer;

	//! position in the buffer
	vlong m_Position;

	//! constructor
	VMemStreamFacade();
public:
	//! constructor
	VMemStreamFacade(void* pBuffer,vlong sizeofbuffer);

	//! deconstructor
	~VMemStreamFacade();

	//!	Read Data for Stream
	VRESULT Read(void* pDest, vlong const nBytesToRead);

	//! Write to Stream
	VRESULT Write(const void* pSource, vulong const nBytesToWrite);

	//! set position in the stream
	void SetPos(EAnchor nFromWhere, StreamPos nDiff);

	//! returns the current position of the pointer
	StreamPos GetPos();
protected:
};

#endif

//! Dokumentation starts here

/*	file: VMemStreamFacade.h
*/			

/*	class VMemStreamFacade : IVStream
	brief: This class is used to handle extern buffers in Memory
		   The class is not allowed to change the size of the buffer
*/

/*  fn VMemStreamFacade(void* pBuffer,vlong sizeofbuffer); //constructor
	param pBuffer - this is a pointer to the extern buffer
	param sizeofbuffer - this parameter specific the size of the buffer
*/

/* fn ~VMemStreamFacade(); //destructor
*/

/* fn VRESULT Read(void* pDest,vlong const nBytesToRead);
   param pDest - this is the buffer were the read data should be copied to
   param nBytesToRead - this param specifie the length to read
   return VOK if succeded
   return VCANCEL is failed
   Comment: the Position of the cursor in the buffer is influenced by this fn
*/

/* fn VRESULT Write(void* const pSource,vulong const nBytesToWrite); 
   param pSource - this is the buffer where the data is stored wich we should write into the buffer	
   param nBytesToWrite - this param specifie the length of pSource
   return VOK if succeded
   return VCANCEL if failes
   Comment: the cursor in the buffer is influenced by this fn
*/

/* fn void SetPos(EAnchor nFromWhere, SreamPos nDiff);
   param nFromWhere - specific where the cursor should put ( begin, current or end)
   param nDiff - specific how much the cursor should move from nFromWhere
*/

/* fn StreamPos GetPos();
   return - the actuall position of the cursor in the Stream
*/