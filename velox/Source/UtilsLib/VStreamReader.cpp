#include <v3dLib/Utils/VStreamReader.h>
#include <v3d/Core/MemManager.h>
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
vulong VStreamReader::GetSizeOfBuffer()
{
	return iSizeOfBufferElements;
}
//-----------------------------------------------------------------------------
} // util
} // v3d
//-----------------------------------------------------------------------------