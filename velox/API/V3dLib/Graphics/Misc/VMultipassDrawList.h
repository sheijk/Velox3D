#ifndef V3D_VMULTIPASSDRAWLIST_2004_04_10_H
#define V3D_VMULTIPASSDRAWLIST_2004_04_10_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Core/SmartPtr/VGuards.h>
#include <V3d/Graphics.h>

#include <map>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * @author sheijk
 */
class VMultipassDrawList : public IVDrawList
{
public:
	typedef vint PassId;

private:
	typedef VPointer<IVDrawList>::SharedPtr DrawListPtr;
	typedef std::map<PassId, DrawListPtr> RenderPassList;

	RenderPassList m_RenderPasses;
	IVDevice& m_Device;

	IVDrawList& GetDrawListForPass(PassId in_nPass)
	{
		RenderPassList::iterator passIter = m_RenderPasses.find(in_nPass);

		if( passIter != m_RenderPasses.end() )
		{
			return *(passIter->second);
		}
		else
		{
			m_RenderPasses[in_nPass] = 
				SharedPtr<IVDrawList>(new VSimpleDrawList(m_Device));

			return *m_RenderPasses[in_nPass];
		}
	}

public:
	VMultipassDrawList(IVDevice& in_Device)
		:
	m_Device(in_Device)
	{
	}

	void Add(VModel in_Model, PassId in_nId)
	{
		GetDrawListForPass(in_nId).Add(in_Model);
	}

	virtual void Add(VModel in_Model)
	{
		Add(in_Model, 0);
	}

	virtual void Remove(VModel in_Model)
	{
		RenderPassList::iterator begin = m_RenderPasses.begin();
		RenderPassList::iterator end = m_RenderPasses.end();

		// remove from all childs
		for(RenderPassList::iterator rpi = begin; rpi != end; ++rpi)
		{
            rpi->second->Remove(in_Model);
		}
	}

	virtual void Render()
	{
		RenderPassList::iterator begin = m_RenderPasses.begin();
		RenderPassList::iterator end = m_RenderPasses.end();

		for(RenderPassList::iterator rpi = begin; rpi != end; ++rpi)
		{
            rpi->second->Render();
		}
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMULTIPASSDRAWLIST_2004_04_10_H
