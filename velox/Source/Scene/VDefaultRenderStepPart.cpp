#include <V3d/Scene/VDefaultRenderStepPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Scene/IVShapePart.h>
#include <V3d/Math/VRBTransform.h>
#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace graphics;

/**
 * standard c'tor
 */
VDefaultRenderStepPart::VDefaultRenderStepPart()
{
}

/**
 * d'tor
 */
VDefaultRenderStepPart::~VDefaultRenderStepPart()
{
}

void VDefaultRenderStepPart::Render(IVGraphicsPart* in_pScene)
{
	V3D_ASSERT(in_pScene != 0);

	VRangeIterator<const IVShapePart> shape = in_pScene->GetVisibleMeshes();
	while( shape.HasNext() )
	{
		const IVMaterial& material = shape->GetMaterial();

		for(vuint pass = 0; pass < material.PassCount(); ++pass)
		{
			math::VRBTransform transform = shape->GetModelTransform();

			GetOutputDevice()->SetMatrix(IVDevice::ModelMatrix, transform.AsMatrix());

			ApplyMaterial(*GetOutputDevice(), &material.GetPass(pass));
			shape->SendGeometry(*GetOutputDevice());
		}

		++shape;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
