#include <V3dLib/Graphics/Misc/VMultipassDrawList.h>
//-----------------------------------------------------------------------------
#include <V3dLib/Graphics/Misc/VSimpleDrawList.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

VMultipassDrawList::VMultipassDrawList(IVDevice& in_Device)
	:
m_Device(in_Device)
{
}

VMultipassDrawList::DrawListPtr 
VMultipassDrawList::GetDrawListForPass(PassId in_nPass)
{
	RenderPassList::iterator passIter = m_RenderPasses.find(in_nPass);

	if( passIter != m_RenderPasses.end() )
	{
		return passIter->second;
	}
	else
	{
		m_RenderPasses[in_nPass] = 
			SharedPtr<IVDrawList>(new VSimpleDrawList(m_Device));

		return m_RenderPasses[in_nPass];
	}
}

void VMultipassDrawList::ReplacePass(PassId in_nPassId, DrawListPtr in_pNewPass)
{
	m_RenderPasses.erase(in_nPassId);
	m_Subpasses.erase(in_nPassId);

	m_RenderPasses[in_nPassId] = in_pNewPass;
}

void VMultipassDrawList::Add(VModelMesh in_Model, PassId in_nId)
{
	GetDrawListForPass(in_nId)->Add(in_Model);
}

void VMultipassDrawList::Add(VModelMesh in_Model)
{
	Add(in_Model, 0);
}

//void VMultipassDrawList::Remove(VModelMesh in_Model)
//{
//	RenderPassList::iterator begin = m_RenderPasses.begin();
//	RenderPassList::iterator end = m_RenderPasses.end();
//
//	// remove from all childs
//	for(RenderPassList::iterator rpi = begin; rpi != end; ++rpi)
//	{
//        rpi->second->Remove(in_Model);
//	}
//}

IVDrawList& VMultipassDrawList::GetPass(PassId in_nPass)
{
	return *GetDrawListForPass(in_nPass);
}

VMultipassDrawList& VMultipassDrawList::MakeSubpassList(PassId in_nPassId)
{
	MultipassList::iterator passIter = m_Subpasses.find(in_nPassId);

	// if the pass is already a multipass
	if( passIter != m_Subpasses.end() )
	{
		// return it
		return *passIter->second;
	}
    // if subpass does not exist yet
	else
	{
		// create new multipass list
		MultipassListPtr pMultiList(new VMultipassDrawList(m_Device));
		DrawListPtr pMultiListAsDrawList(pMultiList);

		// get sub pass and insert it as default pass into new mp list
		DrawListPtr pOldSinglePass = GetDrawListForPass(in_nPassId);
		pMultiList->ReplacePass(0, pOldSinglePass);

		// replace pass by subpass
		ReplacePass(in_nPassId, pMultiListAsDrawList);
		m_Subpasses[in_nPassId] = pMultiList;

		return *pMultiList;
	}
}

void VMultipassDrawList::Render()
{
	RenderPassList::iterator begin = m_RenderPasses.begin();
	RenderPassList::iterator end = m_RenderPasses.end();

	for(RenderPassList::iterator rpi = begin; rpi != end; ++rpi)
	{
        rpi->second->Render();
	}
}

IVDevice& VMultipassDrawList::GetDevice()
{
	return m_Device;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
