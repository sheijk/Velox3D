#include <v3dLib/Graphics/Importer/Base/VMaterialMap.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;

VMaterialMap::VMaterialMap()
{
}

VMaterialMap::~VMaterialMap()
{
	MaterialList::iterator begin = m_MaterialList.begin();

	for(; begin != m_MaterialList.end(); ++begin)
	{
		delete (*begin).listForKey;
	}
}

void VMaterialMap::AddMaterialFacePair(MaterialKey in_Key, vuint32 in_Id)
{
	//look if we have an entry for this material
	MaterialList::iterator begin = m_MaterialList.begin();

	for(; begin != m_MaterialList.end(); ++begin)
	{
		//do we have one?
		if((*begin).key == in_Key)
		{
			(*begin).listForKey->push_back(in_Id);
			return;
		}
	}

	//nothing found create entry
	MatFacePair entry;
	entry.key = in_Key;
	entry.listForKey = new FaceIDList();
	entry.listForKey->push_back(in_Id);

	m_MaterialList.push_back(entry);
}

VMaterialMap::MaterialList& VMaterialMap::GetMaterialFaceMap()
{
	return m_MaterialList;
}

VMaterialMap::FaceIDList* VMaterialMap::GetFaceList(MaterialKey in_Key)
{
	MaterialList::iterator begin = m_MaterialList.begin();

	for(; begin != m_MaterialList.end(); ++begin)
	{
		//do we have one?
		if((*begin).key == in_Key)
		{
			return (*begin).listForKey;
		}
	}

	return 0;
}


//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
