#ifndef V3D_VMATERIALMAP_2005_08_29_H
#define V3D_VMATERIALMAP_2005_08_29_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <map>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * hold a map of materials associated with faces
 * can be quried for a list of faces associated with a material
 *
 * @author: ins
 */

class VImportedMaterialDescription;

class VMaterialMap
{
public:
	typedef std::list<vuint32> FaceIDList;
private:
	
	typedef VImportedMaterialDescription* MaterialKey;

	struct MatFacePair
	{
		MaterialKey key;
		FaceIDList* listForKey;
	};

public:
    
	typedef std::list<MatFacePair> MaterialList;

private:

	MaterialList m_MaterialList;
    	 
public:

	MaterialList& GetMaterialFaceMap();

	void AddMaterialFacePair(MaterialKey in_Key, vuint32 in_Id);
	FaceIDList* GetFaceList(MaterialKey in_Key);

	~VMaterialMap();
	VMaterialMap();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VMATERIALMAP_2005_08_29_H
