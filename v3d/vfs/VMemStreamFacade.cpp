#include <vfs/VMemStreamFacade.h>


// the destructor
VMemStreamFacade::~VMemStreamFacade()
{

}

//the constructor
// isn't used, because VMemStreamFacade should only work with extern buffers
VMemStreamFacade::VMemStreamFacade()
{

}

//the second constructor
//the only one you can use
//see first constructor for describe
VMemStreamFacade::VMemStreamFacade(void* pBuffer,vlong sizeofbuffer)
{
	m_pBuffer=pBuffer; // get the pointer to the extern buffer
	m_SizeofBuffer=sizeofbuffer; // how big is the buffer?
	m_Position=0; // set the fileposition counter
}

//the write to buffer function
VRESULT VMemStreamFacade::Write(const void* in_pSource, vulong const in_cnBytesToWrite)
{
	vulong nBytesToWrite = in_cnBytesToWrite;

	// if we are at end of buffer, abort
	if( m_Position >= m_SizeofBuffer ) return VOK;

	// if not all data fits in buffer
	if( m_Position + in_cnBytesToWrite > m_SizeofBuffer )
	{
		// adjust the number of bytes to write
		nBytesToWrite = m_SizeofBuffer - m_Position;
	}

	// if any data has to be copied
	if( nBytesToWrite > 0 )
	{
		// copy data
		memcpy((char*)m_pBuffer + m_Position, in_pSource, nBytesToWrite);				

		m_Position += nBytesToWrite;
	}

	return VOK;
}

//the read fkt
VRESULT VMemStreamFacade::Read(void* in_pDest, vlong const in_cnBytesToRead)
{
	vlong nBytesToRead = in_cnBytesToRead;

	// if data behind end of buffer would be read, read only until end of buffer
	if( in_cnBytesToRead > m_SizeofBuffer - m_Position )
	{
		nBytesToRead = m_SizeofBuffer - m_Position;
	}

	// if there is something to be read...
	if( nBytesToRead > 0 )
	{
		// copy data
		memcpy(in_pDest, (char*)m_pBuffer+m_Position, nBytesToRead );

		m_Position += nBytesToRead;
	}

	return VOK;
}

//this fkt. sets the fileposition counter, to an specific position
void VMemStreamFacade::SetPos(EAnchor nFromWhere, StreamPos nDiff)
{
	//switch threw the opportunities of nFromWhere
	switch(nFromWhere)
	{
	case begin:
		m_Position=nDiff;//set the fileposition counter at nDiff from the beginning
		break;
	case end:
		//! Set the position, like the user want to have it
		m_Position=m_SizeofBuffer+nDiff;
		break;
	case current:
		m_Position+=nDiff;
		break;
	}
}

//this fkt. returns the actuall position of the fileposition counter
vuint64 VMemStreamFacade::GetPos()
{
	return m_Position;
}