#include <v3dLib/Graphics/Importer/Base/VImportedMaterialContainer.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;

VImportedMaterialContainer::VImportedMaterialContainer()
{
	//create a default material for this list
	VImportedMaterialDescription* pDefaultMaterial =
		new VImportedMaterialDescription("default", "");
	
	m_MaterialList.push_back(pDefaultMaterial);
}

VImportedMaterialContainer::~VImportedMaterialContainer()
{
	MaterialList::iterator begin = m_MaterialList.begin();

	for(; begin != m_MaterialList.end(); begin++)
	{
		delete (*begin);
	}
}

void VImportedMaterialContainer::Add(VImportedMaterialDescription* in_pMaterial)
{
	m_MaterialList.push_back(in_pMaterial);
}

void VImportedMaterialContainer::Remove(VImportedMaterialDescription* in_pMaterial)
{
	m_MaterialList.remove(in_pMaterial);
}

vbool VImportedMaterialContainer::FindMaterialByName(VStringParam in_sName)
{
	MaterialList::iterator begin = m_MaterialList.begin();

	for(; begin != m_MaterialList.end(); begin++)
	{
		std::string theName = (*begin)->GetMaterialName();
		std::string queryName = in_sName;

		if(theName == queryName)
			return true;
	}

	//nothing found
	return false;
}

VImportedMaterialDescription* VImportedMaterialContainer::GetMaterialByName(
	VStringParam in_sName)
{
	MaterialList::iterator begin = m_MaterialList.begin();

	for(; begin != m_MaterialList.end(); begin++)
	{
		std::string theName = (*begin)->GetMaterialName();
		std::string queryName = in_sName;

		if(theName == queryName)
			return (*begin);
	}

	//nothing found
	return 0;
}

void VImportedMaterialContainer::CreateResources()
{
	MaterialList::iterator begin = m_MaterialList.begin();

	for(; begin != m_MaterialList.end(); begin++)
		(*begin)->CreateResource();
	

}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
