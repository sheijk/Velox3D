//-----------------------------------------------------------------------------
#ifndef V3D_VOBJMODELIMPORTER_H
#define V3D_VOBJMODELIMPORTER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
#include "IVModelImporter.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace util{
//-----------------------------------------------------------------------------

/**
 * @version 1.0
 * @created 13-Jan-2004 23:58:21
 * @author ins
 */
class VOBJModelImporter : public IVModelImporter 
{

public:
	VOBJModelImporter();
	virtual ~VOBJModelImporter();
	
	void Create(VStringParam sFilename, VModel3D* Model);
	
private:

	vchar* m_FileBuffer;
	vulong m_FileLenght;

	void ReadFile();
	void ReadVertices(vulong& FileIndex);
	void ReadFaces(vulong& FileIndex);
	void SaveModel();

	std::vector<vfloat32*> m_pVertices;
	std::vector<vfloat32*> m_pTexCoords;
	std::vector<VModelFace*> m_pFaces;

	vbool m_bFinishedObject;
	vbool m_bIsTextured;
	vbool m_bIsNewLine;
	vbool m_bIsFaceFinish;
	vulong m_iCurrentFileIndex;

	VModel3D* m_Model;


};
//-----------------------------------------------------------------------------
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VOBJMODELIMPORTER_H