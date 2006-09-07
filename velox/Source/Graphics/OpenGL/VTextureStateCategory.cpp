/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VTextureStateCategory.h"
//-----------------------------------------------------------------------------
#include <v3d/Graphics/GraphicsExceptions.h>
#include <V3d/Graphics/Materials/StateTypes.h>
//#include "VCubemapTextureState.h"

#include "Textures/VCubeMapTexture.h"

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
	:
	m_DefaultState(new VUntextured())
{
	VTextureState::SetCategory(this);
}

//vfloat32 VTextureStateCategory::GetPriority() const
//{
//	return .9f;
//}
//
//const IVRenderState& VTextureStateCategory::GetDefault() const
//{
//	return (IVRenderState&)m_DefaultState;
//}

IVRenderState* VTextureStateCategory::Create2DState(const VState* in_pTextureState)
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

		VTextureState* pTextureState = new VTextureState(pRes->GetData<IVTexture>());

		return pTextureState;
		//VResourceDataPtr<const VTextureState> pState = 
		//	pRes->GetData<VTextureState>();

		//return const_cast<VTextureState*>(&* pState);
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

namespace {
	const image::VImage& GetImage(const VState& state, VStringParam paramName)
	{
		return *GetResourceData<image::VImage>(state.GetParameterByName(paramName).GetValue<std::string>().c_str());
	}
}

IVRenderState* VTextureStateCategory::CreateCubeMapState(
	const VState* in_pTextureState)
{
	using std::string;
	IVRenderState* pCubemapState = 0;

	if( in_pTextureState->ContainsParameter("front") &&
		in_pTextureState->ContainsParameter("back") &&
		in_pTextureState->ContainsParameter("left") &&
		in_pTextureState->ContainsParameter("right") &&
		in_pTextureState->ContainsParameter("top") &&
		in_pTextureState->ContainsParameter("bottom") )
	{
		VCubeMapTexture* pTexture = new VCubeMapTexture(
			GetImage(*in_pTextureState, "front"),
			GetImage(*in_pTextureState, "back"),
			GetImage(*in_pTextureState, "left"),
			GetImage(*in_pTextureState, "right"),
			GetImage(*in_pTextureState, "top"),
			GetImage(*in_pTextureState, "bottom"));

		pCubemapState = new VTextureState(pTexture);
	}
	else
	{
		V3D_THROW(VInvalidEffectDescriptionException,
			"CubeMap texture effect description's node 'texture' must contain "
			"attributes named front, back, left, right, top, bottom which "
			"reference the six cube map textures");
	}

	V3D_ASSERT(0 != pCubemapState);
	return pCubemapState;
}

/*
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
*/

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
			return Create2DState(pTextureState);
		}
		if( textureType == "cube" )
		{
			return CreateCubeMapState(pTextureState);			
		}
		else
		{
			V3D_THROWMSG(VInvalidEffectDescriptionException,
				"Type '" << textureType << "' is an invalid texture type");
		}
	}
	else
	{
		return reinterpret_cast<IVRenderState*>(&m_DefaultState);
	}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------

