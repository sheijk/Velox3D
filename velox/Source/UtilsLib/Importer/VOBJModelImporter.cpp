//-----------------------------------------------------------------------------
#include <v3d/VFS/IVFileSystem.h>
#include <v3d/Core/VObjectRegistry.h>

#include "VOBJModelImporter.h"
#include "VStreamReader.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace util{
//-----------------------------------------------------------------------------
VOBJModelImporter::VOBJModelImporter()
{
	m_bFinishedObject = false;
	m_bIsNewLine = false;
	m_bIsTextured = false;
	m_bIsFaceFinish = false;
	m_FileBuffer = NULL;
	m_Model = NULL;
	m_FileLenght = 0;
	m_iCurrentFileIndex = 0;
}
//-----------------------------------------------------------------------------

VOBJModelImporter::~VOBJModelImporter()
{
}
//-----------------------------------------------------------------------------
void VOBJModelImporter::Create(VStringParam sFilename, VModel3D* Model)
{
	// query vfs
	vfs::IVFileSystem& fileSys = *QueryObject<vfs::IVFileSystem>("vfs.fs");

	// open file
	vfs::IVFileSystem::FileStreamPtr fileStream = 
		fileSys.OpenFile(sFilename, vfs::VReadAccess);
	
	VStreamReader StreamReader(fileStream.Get());

	m_FileBuffer = (vchar*) StreamReader.GetStreamBuffer();
	m_FileLenght = StreamReader.GetSizeOfBuffer();

	m_Model = Model;

	ReadFile();



}
//-----------------------------------------------------------------------------
void VOBJModelImporter::ReadFile()
{
	for(vulong i=0; i < m_FileLenght; i++)
	{
		vchar cCurrentPosition;
		cCurrentPosition = m_FileBuffer[i];

		switch (cCurrentPosition)
		{
		//vertex, tex or normal
		case 'v':
            
			if(m_bIsNewLine)
			{
				
				if(m_bIsFaceFinish)
					SaveModel();
				

				ReadVertices(i);
			}
			m_bIsNewLine = false;

			break;
		//got to faces
		case 'f':

			if(m_bIsNewLine)
			{
				ReadFaces(i);
			}
			m_bIsNewLine = false;
			break;

		case '\n':
			m_bIsNewLine = true;
			break;

		default:
			m_bIsNewLine = false;
			
			break;
		}
	}

	SaveModel();

}

//-----------------------------------------------------------------------------
void VOBJModelImporter::ReadVertices(vulong& FileIndex)
{
	vchar cCurrentChar;
    //skip the v attribute indicator
	FileIndex++;
	cCurrentChar = m_FileBuffer[FileIndex];

	if(cCurrentChar == ' ')
	{
		vfloat32* fVertex = new vfloat32[3];

		sscanf(&m_FileBuffer[FileIndex], "%f %f %f", &fVertex[0], &fVertex[1], &fVertex[2]);
		//skip rest of the  line
		while(m_FileBuffer[FileIndex] != '\n')
			FileIndex++;
		//skip back to new line
		FileIndex--;

		// Add a new vertice to our list
		m_pVertices.push_back(fVertex);
	}
	else
		if(cCurrentChar == 't')
		{
			//yeah we got uv coordintes. save this we gonna need it later...
			m_bIsTextured = true;
			//skip one forward to get the coordinates
			FileIndex++;
			vfloat32* fTexCoord = new vfloat32[2];
			// Here we read in a texture coordinate.  The format is "vt u v"
			sscanf(&m_FileBuffer[FileIndex], "%f %f", &fTexCoord[0], &fTexCoord[1]);

			while(m_FileBuffer[FileIndex] != '\n')
				FileIndex++;
			//skip back to new line
			FileIndex--;


			// Add a new texture coordinates
			m_pTexCoords.push_back(fTexCoord);
		}
}
//-----------------------------------------------------------------------------

void VOBJModelImporter::ReadFaces(vulong& FileIndex)
{
	VModelFace* ModelFace = new VModelFace;
	FileIndex++;

	if(m_bIsTextured)
	{
		sscanf(&m_FileBuffer[FileIndex], "%d/%d %d/%d %d/%d",
			&ModelFace->m_iVertexIndex[0], &ModelFace->m_iTextureUVIndex[0],
			&ModelFace->m_iVertexIndex[1], &ModelFace->m_iTextureUVIndex[1],
			&ModelFace->m_iVertexIndex[2], &ModelFace->m_iTextureUVIndex[2]);

			
	}
	//no uv coordinates, model will suck ;0
	else
	{
		sscanf(&m_FileBuffer[FileIndex], "%d %d %d",
			&ModelFace->m_iVertexIndex[0],
			&ModelFace->m_iVertexIndex[1],
			&ModelFace->m_iVertexIndex[2]
			);
			
	}
	while(m_FileBuffer[FileIndex] != '\n')
		FileIndex++;
	//skip back to new line
	FileIndex--;

	m_bIsFaceFinish = true;


	// Add the new face to our face list
	m_pFaces.push_back(ModelFace);



}
//-----------------------------------------------------------------------------

void VOBJModelImporter::SaveModel()
{
	VModelObject3D* pObject = new VModelObject3D;

	pObject->m_iNumFaces = (vuint32)m_pFaces.size();
	pObject->m_iNumVertices = (vuint32)m_pVertices.size();
	pObject->m_iNumTexCoords2f = (vuint32)m_pTexCoords.size();

	//copy data from our list into a single buffer for the object

	vfloat32* pVertexBuffer = new vfloat32[pObject->m_iNumVertices*3];

	for(vuint i = 0; i<pObject->m_iNumVertices; i++)
	{
		pVertexBuffer[i*3] = m_pVertices[i][0];
		pVertexBuffer[i*3+1] = m_pVertices[i][1];
		pVertexBuffer[i*3+2] = m_pVertices[i][2];

		delete m_pVertices[i];
	}

	//assign to object
	pObject->m_VerticesList = pVertexBuffer;
	//clear vector
	m_pVertices.clear();

	//same to uv info
	if(m_bIsTextured)
	{
		vfloat32* pTexCoords = new vfloat32[pObject->m_iNumTexCoords2f*2];
		for(vuint i = 0; i < pObject->m_iNumTexCoords2f; i++)
		{
			pTexCoords[i*2] = m_pTexCoords[i][0];
			pTexCoords[i*2+1] = m_pTexCoords[i][1];

			delete m_pTexCoords[i];
		}

		pObject->m_TextureCoordsList = pTexCoords;

		m_pTexCoords.clear();
	}
	else
	{
		pObject->m_TextureCoordsList = NULL;
	}

	VModelFace* pFaces = new VModelFace[pObject->m_iNumFaces];
	vuint32* pVertexIndex = new vuint32[pObject->m_iNumFaces*3];
	for(vuint i = 0; i < pObject->m_iNumFaces; i++)
	{
		pFaces[i].m_iVertexIndex[0] = m_pFaces[i]->m_iVertexIndex[0];
		pFaces[i].m_iVertexIndex[1] = m_pFaces[i]->m_iVertexIndex[1];
		pFaces[i].m_iVertexIndex[2] = m_pFaces[i]->m_iVertexIndex[2];

		pVertexIndex[i*3] = m_pFaces[i]->m_iVertexIndex[0];
		pVertexIndex[i*3+1] = m_pFaces[i]->m_iVertexIndex[1];
		pVertexIndex[i*3+2] = m_pFaces[i]->m_iVertexIndex[2];

		pFaces[i].m_iTextureUVIndex[0] = m_pFaces[i]->m_iVertexIndex[0];
		pFaces[i].m_iTextureUVIndex[1] = m_pFaces[i]->m_iVertexIndex[1];
		pFaces[i].m_iTextureUVIndex[2] = m_pFaces[i]->m_iVertexIndex[2];

		delete m_pFaces[i];
	}

	pObject->m_ModelFaces = pFaces;
	pObject->m_pVertexIndex = pVertexIndex;

	m_Model->m_Objects.push_back(pObject);

	m_bIsTextured = false;
	m_bIsFaceFinish = false;

}

//-----------------------------------------------------------------------------
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------


