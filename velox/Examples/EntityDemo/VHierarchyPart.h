#ifndef V3D_VHIERARCHYPART_2005_05_20_H
#define V3D_VHIERARCHYPART_2005_05_20_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>
#include <V3d/Entity/VEntityExceptions.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Demonstrates how to get the 'parent' part by overriding TellParentPart
 *
 * @author sheijk
 */
class VHierarchyPart : public entity::IVPart
{
public:
	VHierarchyPart(const std::string& in_Name) : m_Name(in_Name)
	{
		m_pParent = 0;
	}

	void Activate()
	{
		vout << "VHierarchyPart '" << m_Name << "' activated";

		if( m_pParent ) 
		{
			vout << ", parent: " << m_pParent->m_Name;
		}

		vout << vendl;
	}

	void Deactivate()
	{
		vout << "VHierarchyPart '" << m_Name << "' deactivated" << vendl;
	}

	void TellParentPart(const utils::VFourCC& in_Id, entity::IVPart& in_Part)
	{
		m_pParent = in_Part.Convert<VHierarchyPart>();
	}

private:
	std::string m_Name;
	VHierarchyPart* m_pParent;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VHIERARCHYPART_2005_05_20_H
