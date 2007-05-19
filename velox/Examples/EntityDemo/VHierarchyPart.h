#ifndef V3D_VHIERARCHYPART_2005_09_12_H
#define V3D_VHIERARCHYPART_2005_09_12_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VPartBase.h>

#include <set>
//-----------------------------------------------------------------------------
namespace v3d { 
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Demonstrate how to do parts which want to get a connection to their parent
 * if one exists (which have an optional ancestor connection)
 *
 * @author sheijk
 */
class VHierarchyPart : public entity::VPartBase
{
	entity::VPartConnection<VHierarchyPart> m_pParent;

	std::set<VHierarchyPart*> m_Childs;
public:
	VHierarchyPart() : 
	  m_pParent(
		  entity::VPartDependency::Ancestor,
		  entity::VPartDependency::Optional,
		  RegisterTo())
	{
	}

	void Print(const std::string prefix)
	{
		vout << prefix << "hierarchical part (" << m_Childs.size() << " childs)" << vendl;
		for(std::set<VHierarchyPart*>::iterator child = m_Childs.begin();
			child != m_Childs.end(); ++child)
		{
            (*child)->Print(prefix + "\t");
		}
	}

	static std::string GetDefaultId() { return "hierarchyPart"; }
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	void OnActivate()
	{
		if( m_pParent.IsConnected() )
			m_pParent->Register(this);
	}

	void OnDeactivate()
	{
		if( m_pParent.IsConnected() )
			m_pParent->Unregister(this);
	}

private:
	void Register(VHierarchyPart* child)
	{
		m_Childs.insert(child);
	}

	void Unregister(VHierarchyPart* child)
	{
		m_Childs.erase(child);
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d

V3D_TYPEINFO_WITHPARENT(v3d::VHierarchyPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VHIERARCHYPART_2005_09_12_H
