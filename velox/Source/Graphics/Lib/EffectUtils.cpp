#include <V3dLib/Graphics/Materials/EffectUtils.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/VIOStream.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------

VState DefaultColorState(VColor4f in_Color)
{
	VState colorState("color");
	colorState.SetParameter(VStateParameter("red", in_Color.red));
	colorState.SetParameter(VStateParameter("green", in_Color.green));
	colorState.SetParameter(VStateParameter("blue", in_Color.blue));
	colorState.SetParameter(VStateParameter("alpha", in_Color.alpha));

	return colorState;
}

VState DefaultColorState(
	vfloat32 red, vfloat32 green, vfloat32 blue, vfloat32 alpha)
{
	return DefaultColorState(VColor4f(red, green, blue, alpha));
}

VState ColorBufferWriteMaskState(VColorBufferMask in_Mask)
{
	VState colorMaskState("colormask");
	colorMaskState.SetParameter("red",		in_Mask.writeRed);
	colorMaskState.SetParameter("green",	in_Mask.writeGreen);
	colorMaskState.SetParameter("blue",		in_Mask.writeBlue);
	colorMaskState.SetParameter("alpha",	in_Mask.writeAlpha);
	
	return colorMaskState;
}

VState ColorBufferWriteMaskState(
	vbool writeRed, vbool writeGreen, vbool writeBlue, vbool writeAlpha)
{
	return ColorBufferWriteMaskState(
		VColorBufferMask(writeRed, writeGreen, writeBlue, writeAlpha));
}

VState TextureState(
	IVBuffer<vbyte>* hBuffer,
	vuint width, vuint height,
	VTextureFilter magnificationFilter, VTextureFilter minificationFilter,
	VTextureWrapMode texCoordWrapU, VTextureWrapMode texCoordWrapV,
	const VMatrix44f* pTextureMatrix
	)
{
	VState textureState("texture");

	void* hData = static_cast<void*>(hBuffer);
	textureState.SetParameter("bufferref", hData);
	textureState.SetParameter("width", width);
	textureState.SetParameter("height", height);
	textureState.SetParameter("wrapu", texCoordWrapU);
	textureState.SetParameter("wrapv", texCoordWrapV);
	textureState.SetParameter("magnification.filter", magnificationFilter);
	textureState.SetParameter("minification.filter", minificationFilter);

	if( pTextureMatrix != 0 )
	{
		textureState.SetParameter("matrix", *pTextureMatrix);
	}
	
	return textureState;
}

VState TextureState(
	VStringParam in_strResourceName,
	VTextureFilter magnificationFilter, 
	VTextureFilter minificationFilter,
	VTextureWrapMode texCoordWrapU, 
	VTextureWrapMode texCoordWrapV,
	const VMatrix44f* pTextureMatrix
	)
{
	VState textureState("texture");

	textureState.SetParameter("res", in_strResourceName);
	textureState.SetParameter("wrapu", texCoordWrapU);
	textureState.SetParameter("wrapv", texCoordWrapV);
	textureState.SetParameter("magnification.filter", magnificationFilter);
	textureState.SetParameter("minification.filter", minificationFilter);

	if( pTextureMatrix != 0 )
	{
		textureState.SetParameter("matrix", *pTextureMatrix);
	}

	return textureState;
}

VState PolygonModeState(VPolygonMode frontMode, VPolygonMode backMode)
{
	VState polymode("polygonmode");
	polymode.SetParameter("front", frontMode);
	polymode.SetParameter("back", backMode);

	return polymode;
}

VState DepthBufferState(
	VDepthTest depthTest, 
	VDepthTestEnable enableDepthTest, 
	VDepthWriteMode writeMode)
{
	VState depthState("depth");
	depthState.SetParameter("function", depthTest);
	depthState.SetParameter("write", writeMode);
	depthState.SetParameter("enable", enableDepthTest);

	return depthState;
}

VState BlendingState(
	VBlendEnable enable,
	VBlendFactor source,
	VBlendFactor dest)
{
	VState blendState("blending");
	blendState.SetParameter("enable", enable);
	blendState.SetParameter("source", source);
	blendState.SetParameter("dest", dest);

	return blendState;
}

//-----------------------------------------------------------------------------
void MakeDefaultMaterial(VRenderPass& pass)
{
	pass.Clear();
}

void MakeWireFrameMaterial(VRenderPass& pass)
{
	pass.Clear();

	pass.AddState(PolygonModeState(PMLine, PMLine));
}

VEffectDescription ColorEffect(const VColor4f& in_Color)
{
	VEffectDescription effect;

	VRenderPass& pass(effect.AddShaderPath().AddRenderPass());
	pass.AddState(DefaultColorState(in_Color));
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));

	return effect;
}

//-----------------------------------------------------------------------------

void PrintEffectDescription(const VEffectDescription& effect)
{
	// for each shader path
	for(vuint spathId = 0; spathId < effect.GetShaderPathCount(); ++spathId)
	{
		const VShaderPath& path(effect.ShaderPath(spathId));

		vout << "Shader Path " << spathId + 1 << "/" << effect.GetShaderPathCount()
			<< ":" << vendl;

		// for each render pass
		for(vuint rpassId = 0; rpassId < path.GetRenderPassCount(); ++rpassId)
		{
			const VRenderPass& pass(path.RenderPass(rpassId));

			vout << "  Render pass " << rpassId + 1 << "/" 
				<< path.GetRenderPassCount() << ":" << vendl;

			// for each state
			for(vuint stateId = 0; stateId < pass.GetStateCount(); ++stateId)
			{
				const VState& state(pass.State(stateId));

				vout << "    State \"" << state.GetName() << "\"" << vendl;

				// for each parameter
				for(vuint paramId = 0; paramId < state.GetParameterCount(); ++paramId)
				{
					const VStateParameter& param(state.GetParameter(paramId));

					vout << "      Param " << param.GetName() << "=" 
						<< param.GetValue<std::string>() << vendl;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
