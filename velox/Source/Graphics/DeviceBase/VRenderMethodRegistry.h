#ifndef V3D_VRENDERMETHODREGISTRY_H
#define V3D_VRENDERMETHODREGISTRY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VMeshDescription.h>
#include "VBaseMesh.h"

#include <list>
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
	/** 
	 * creates a mesh implementation which will render with the render
	 * method of the IVRenderMethod derived class
	 */
	 virtual VBaseMesh* CreateMesh(VMeshDescription& in_MeshDescr) = 0;
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

	typedef vuint32 MeshCreationFlags;

	/** registers a rendering method */
	void RegisterRenderMethod(IVRenderMethod& in_RenderMethod);

	/**
	 * creates a new mesh, automatically selects appropriate 
	 * rendering method
	 */
	VBaseMesh* CreateMesh(
		VMeshDescription& in_MeshDescr, 
		MeshCreationFlags in_Flags
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
