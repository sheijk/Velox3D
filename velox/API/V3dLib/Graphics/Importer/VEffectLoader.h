//TODO: add file creation date to file guard
#ifndef V3D_VEFFECTLOADER_2005_02_15_H
#define V3D_VEFFECTLOADER_2005_02_15_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource/VResourceId.h>
#include <V3d/XML.h>
#include <V3d/Graphics/VEffectDescription.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

V3D_DECLARE_EXCEPTION(VEffectLoaderException, VException);

/**
 */
class VEffectLoader : private xml::IVXMLVisitor
{
public:
	VEffectLoader();
	virtual ~VEffectLoader();

	void LoadEffect(
		VStringParam in_strEffectFile,
		resource::VResourceId in_pResource
		);

private:
	std::string m_strFileName;
	VEffectDescription m_Effect;

	enum State { 
		NotParsing,
		ParsingEffect,
		ParsingShaderPath,
		ParsingRenderPass,
		ParsingState
	};

	State m_State;

	virtual void OnElementClose(xml::IVXMLElement* pElement);
	virtual void OnElementOpen(xml::IVXMLElement* pElement);
	virtual void OnFileEnd();
	virtual void OnComment(VStringParam pText);
	virtual void OnText(VStringParam pText);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VEFFECTLOADER_2005_02_15_H
