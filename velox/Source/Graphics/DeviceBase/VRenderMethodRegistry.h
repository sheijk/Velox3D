#ifndef V3D_VRENDERMETHODREGISTRY_H
#define V3D_VRENDERMETHODREGISTRY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VMeshDescription.h>

#include "VMeshBase.h"

#include <list>
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // does nothing.. only stops vs from auto indenting :)

/**
 * Interface for a rendering method (glVertex style, VBO, etc)
 *
 * @author sheijk
 */
struct IVRenderMethod
{
	typedef vuint32 MeshCreationFlags;

	/** 
	 * creates a mesh implementation which will render with the render
	 * method of the IVRenderMethod derived class
	 */
	 virtual VMeshBase* CreateMesh(
		 const VMeshDescription& in_MeshDescr,
		 MeshCreationFlags in_Flags,
		 std::vector<IVMaterial*> in_Materials
		 ) = 0;
};

/**
 * A registry for different rendering methods.
 *
 * @author sheijk
 */
class VRenderMethodRegistry
{
	typedef std::list<IVRenderMethod*> RenderMethodList;

	RenderMethodList m_RenderMethods;

public:
	VRenderMethodRegistry();
	~VRenderMethodRegistry();

	typedef IVRenderMethod::MeshCreationFlags MeshCreationFlags;

	/**
	 * TODO: sollte vllt. nur Register() im allgemeinen heissen? Einheitliche
	 * standard methoden fuer die api in die guidelines aufnehmen!?
	 * Waere sinnvoll fuer die einfache erlernbarkeit der api.
	
	/** registers a rendering method */
	void RegisterRenderMethod(IVRenderMethod& in_RenderMethod);

	/**
	 * creates a new mesh, automatically selects appropriate 
	 * rendering method
	 */
	VMeshBase* CreateMesh(
		const VMeshDescription& in_MeshDescr, 
		MeshCreationFlags in_Flags,
		std::vector<IVMaterial*> in_Materials
		);

	// frage: wie wird entschieden, welche render methode benutzt wird? (wer?)
	// abwaegung performance/recourcen?
	// fkt fuer "kosten", sowie konstante fuer performance
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VRENDERMETHODREGISTRY_H
