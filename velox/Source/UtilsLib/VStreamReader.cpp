/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Utils/VStreamReader.h>
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace utils{
//-----------------------------------------------------------------------------
using namespace v3d::vfs;
VStreamReader::VStreamReader(IVStream* in_pStream)
{
	// allgemein in dieser fkt: naming conventions beachten,
	// kein m_ fuer lok. vars, kein grossbuchst. am anfang -sheijk
    CharList m_BufferPartList;
	iSizeOfBuffer = 0;
	iSizeOfBufferElements = 0;
	
	for(;;)
	{
		//Create a buffer for our data
		vchar* BufferPart = NULL;
		BufferPart = new char[BufferSize];
		
		if( ! BufferPart)
			V3D_THROW(VException, "could not allocated buffer for stream reading!");
								   
		//Read from stream into buffer
		 iSizeOfBuffer = in_pStream->Read(BufferPart, BufferSize);
		
		//We didn't got all the bytes yet
		if(iSizeOfBuffer == BufferSize)
			m_BufferPartList.push_back(BufferPart);
		
		//Reached the end of the stream
		else
		{
			//alloc buffer in full size	+1 for "\0" terminating
			vuint iNumParts = (vuint) m_BufferPartList.size();
			m_Buffer = new vchar[(iSizeOfBuffer+1) + iNumParts * BufferSize];

			iSizeOfBufferElements = (iSizeOfBuffer+1) + iNumParts * BufferSize;
			
			
			//iterate the whole thing
			CharList::iterator ListIterator;
			CharList::iterator ListIteratorEnd;

			ListIterator = m_BufferPartList.begin();
			ListIteratorEnd = m_BufferPartList.end();

			if(ListIterator == ListIteratorEnd)
			{
				memcpy(m_Buffer, BufferPart, (iSizeOfBuffer*sizeof(vchar)));
				m_Buffer[iSizeOfBuffer] = '\0';
			}
							
			else
			{
				vuint iCount = 0;
				while(ListIterator != ListIteratorEnd)
				{
                    memcpy(m_Buffer + iCount*BufferSize*sizeof(vchar),
						*ListIterator, (BufferSize*sizeof(vchar)));
					ListIterator++;
					iCount++;
				}


				//copy rest of the buffer
				memcpy(m_Buffer+ iCount*BufferSize*sizeof(vchar), BufferPart, 
					(iSizeOfBuffer * sizeof(vchar)));
				m_Buffer[iSizeOfBuffer + iNumParts*BufferSize] = '\0';
		
				//free our mem from the stl container
				for(ListIterator = m_BufferPartList.begin();
				ListIterator == m_BufferPartList.end(); ListIterator++)
				delete [] *ListIterator;
			}
			break;
		}
	}
}

VStreamReader::~VStreamReader()
{
	delete[] m_Buffer;
}

void* VStreamReader::GetStreamBuffer()
{
	if(m_Buffer)
		return (void*) m_Buffer;
	else
		return NULL;
}

vulong VStreamReader::GetSizeOfBuffer() const
{
	return iSizeOfBufferElements;
}

void VStreamReader::CopyToString(std::string* in_pString) const
{
	if( iSizeOfBuffer > 0 )
	{
		const char lastChar = m_Buffer[iSizeOfBuffer-1];

		m_Buffer[iSizeOfBuffer-1] = '\0';

		*in_pString = m_Buffer;
		*in_pString += lastChar;

		m_Buffer[iSizeOfBuffer-1] = lastChar;
	}
	else
	{
		*in_pString = "";
	}
}

//-----------------------------------------------------------------------------
} // util
} // v3d
//-----------------------------------------------------------------------------
