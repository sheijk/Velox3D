/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VVertexShaderCategory.h"
//-----------------------------------------------------------------------------

#include <V3d/Graphics/Materials/StateTypes.h>
#include <V3d/Graphics/Materials/VModeTypeInfo.h>
#include <V3d/Vfs.h>

#include <string>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace std;

//namespace {
//	void LoadFileToString(std::string& out_Content, VStringParam in_strFileName)
//	{
//		vfs::VFileSystemPtr pFS;
//		vfs::IVFileSystem::FileStreamPtr pFile = pFS->OpenFile(
//			in_strFileName, vfs::VReadAccess);
//		std::vector<vchar> buffer;
//		const vfs::IVStream::ByteCount nFileSize = pFile->GetSize();
//		buffer.resize(nFileSize + 1);
//		pFile->Read(&buffer[0], nFileSize);
//		buffer[nFileSize] = '\0';
//		out_Content = &buffer[0];
//	}
//} // anonymous namespace

IVRenderState* VCGShaderCategory::CreateShaderState(
	const VState* in_pState,
	VCGVertexShaderState::ShaderMode in_DisableMode)
{
	if( in_pState != 0 )
	{
		// get state from resource
		string res;
		in_pState->GetParameter("file", res);

		string profileName;
		in_pState->GetParameter("profile", profileName);

		CGprofile profile = GetShaderTypeInfo().GetGLEnum(profileName);

		// get shader from resource manager
		VCGVertexShaderState* pShaderState = 
			new VCGVertexShaderState(res.c_str(), profile, this);

		// get all parameters
		const vuint paramCount = in_pState->GetParameterCount();
		for(vuint paramNum = 0; paramNum < paramCount; ++paramNum)
		{
			VStateParameter param = in_pState->GetParameter(paramNum);
			string name = param.GetName();
			string val = param.GetValue<string>();

			if( val.length() > 0 && val[0] == '$' )
			{
				VCGVertexShaderState::AutoVariable type =
					param.GetValue<VCGVertexShaderState::AutoVariable>();

				pShaderState->AddAutoVar(name, type);
			}
		}

		return pShaderState;
	}
	else
	{
		return new VCGVertexShaderState(in_DisableMode, this);
	}
}

IVRenderState* VVertexShaderCategory::CreateState(const VRenderPass& in_Pass)
{
	const VState* pVShaderState = in_Pass.GetStateByName("vshader");

	return CreateShaderState(
		pVShaderState, 
		VCGVertexShaderState::DisableVertexShader);
}

IVRenderState* VPixelShaderCategory::CreateState(const VRenderPass& in_Pass)
{
	const VState* pPShaderState = in_Pass.GetStateByName("pshader");

	return CreateShaderState(
		pPShaderState,
		VCGVertexShaderState::DisablePixelShader);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

