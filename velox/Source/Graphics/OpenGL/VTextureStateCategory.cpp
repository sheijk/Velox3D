#include "VTextureStateCategory.h"
//-----------------------------------------------------------------------------
#include <v3d/Graphics/GraphicsExceptions.h>

#include <V3dLib/Graphics/Materials/StateTypes.h>
#include "VCubemapTextureState.h"

#include <V3d/Image/VImage.h>
#include <V3d/Resource.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d::resource;

V3D_DECLARE_EXCEPTION(VInvalidEffectDescriptionException, VGraphicException);

VTextureStateCategory::VTextureStateCategory()
{
}

vfloat32 VTextureStateCategory::GetPriority() const
{
	return .9f;
}

/*const IVRenderState& VTextureStateCategory::GetDefault() const
{
	return 0;
}*/

VTexture2D* VTextureStateCategory::Create2DState(const VState* in_pTextureState)
{
	// if a texture is referenced by resource name
	if( in_pTextureState->ContainsParameter("res") )
	{
		using namespace resource;

		std::string resName;
		in_pTextureState->GetParameter("res", resName);

		// get texture state
		VResourceManagerPtr pResMan;

		VResourceId pRes = pResMan->GetResourceByName(resName.c_str());
		VResourceDataPtr<const VTexture2D> pState = 
			pRes->GetData<VTexture2D>();

		return const_cast<VTexture2D*>(&* pState);
	}
	// necessary state parameters are missing
	else
	{
		V3D_THROW(VMissingStateParameterException, "The effect description "
			"contained a 'texture' state which is missing 'res' "
			"reference parameters referencing a resource where the texture "
			"is located");
	}
}

template<typename DataType>
VResourceDataPtr<const DataType> GetDataFromResource(VStringParam in_strResName)
{
	VResourceId res = VResourceManagerPtr()->GetResourceByName(in_strResName);
	VResourceDataPtr<const DataType> data = res->GetData<DataType>();
	return data;
}

IVRenderState* VTextureStateCategory::CreateCubeMapState(
	const VState* in_pTextureState)
{
	using std::string;
	IVRenderState* pCubemapState = 0;

	if( in_pTextureState->ContainsParameter("posx") &&
		in_pTextureState->ContainsParameter("posy") &&
		in_pTextureState->ContainsParameter("posz") &&
		in_pTextureState->ContainsParameter("negx") &&
		in_pTextureState->ContainsParameter("negy") &&
		in_pTextureState->ContainsParameter("negz") )
	{
		// get states and state names for each side from resource manager
		string posxRes;
		in_pTextureState->GetParameter("posx", posxRes);
		VResourceDataPtr<const VCubemapPosX> pPosXState = 
			GetDataFromResource<VCubemapPosX>(posxRes.c_str());

		string posyRes;
		in_pTextureState->GetParameter("posy", posyRes);
		VResourceDataPtr<const VCubemapPosY> pPosYState = 
			GetDataFromResource<VCubemapPosY>(posyRes.c_str());

		string poszRes;
		in_pTextureState->GetParameter("posz", poszRes);
		VResourceDataPtr<const VCubemapPosZ> pPosZState = 
			GetDataFromResource<VCubemapPosZ>(poszRes.c_str());

		string negxRes;
		in_pTextureState->GetParameter("negx", negxRes);
		VResourceDataPtr<const VCubemapNegX> pNegXState = 
			GetDataFromResource<VCubemapNegX>(negxRes.c_str());

		string negyRes;
		in_pTextureState->GetParameter("negy", negyRes);
		VResourceDataPtr<const VCubemapNegY> pNegYState = 
			GetDataFromResource<VCubemapNegY>(negyRes.c_str());

		string negzRes;
		in_pTextureState->GetParameter("negz", negzRes);
		VResourceDataPtr<const VCubemapNegZ> pNegZState = 
			GetDataFromResource<VCubemapNegZ>(negzRes.c_str());

		// create a new state for the cube map
		pCubemapState = new VCubemapTextureState(
			pPosXState, pPosYState, pPosZState,
			pNegXState, pNegYState, pNegZState);
	}
	else
	{
		V3D_THROW(VInvalidEffectDescriptionException,
			"CubeMap texture effect description's node 'texture' must contain "
			"attributes named '[pos/neg][x/y/z]' which reference the six cube "
			"map textures");
	}

	V3D_ASSERT(0 != pCubemapState);
	return pCubemapState;
}

IVRenderState* VTextureStateCategory::CreateState(const VRenderPass& in_Pass)
{
	// if a texture is specified
	VState const* pTextureState = in_Pass.GetStateByName("texture");
	if( pTextureState != 0 )
	{
		// determine texture type
		std::string textureType = "2d";
		if( pTextureState->ContainsParameter("type") )
		{
			pTextureState->GetParameter("type", textureType);
		}

		if( textureType == "2d" )
		{
			return reinterpret_cast<IVRenderState*>(Create2DState(pTextureState));
		}
		if( textureType == "cubeMap" )
		{
			return CreateCubeMapState(pTextureState);			
		}
		else
		{
			V3D_THROW(VInvalidEffectDescriptionException,
				"Type 'TODO' is an invalid texture type");
		}
	}
	else
	{
		return 0;//reinterpret_cast<IVRenderState*>(&m_DefaultState);
	}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
