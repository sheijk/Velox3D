#ifndef V3D_SHEIJKUTILS20040407_H
#define V3D_SHEIJKUTILS20040407_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
#include <v3d/Image.h>
#include <v3d/Graphics.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * achtung: diese funktion erzeugt buffer, welche nicht automatisch wieder
 * freigegeben werden.
 *
 * matDesc = BuildTextureMaterial(device, fileName);
 * ...
 * device.DeleteBuffer(mat.Desc.pTextureList.hData);
 *
 * @author sheijk
 */
VMaterialDescription BuildTextureMaterial(
	IVDevice* in_pDevice,
	VStringParam in_pcTextureFile);

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_SHEIJKUTILS20040407_H
