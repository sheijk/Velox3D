/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/Importer/VEffectLoader.h>
//-----------------------------------------------------------------------------
#include <V3d/Vfs.h>
#include <V3d/Core.h>
#include <V3d/Graphics/Materials/EffectUtils.h>
#include <V3d/Resource/VResource.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::xml;
using namespace v3d::resource;

//-----------------------------------------------------------------------------
class VStateParser : public IVXMLVisitor
{
	VState m_State;
	std::string m_IParamName;

public:
	VStateParser(VStringParam in_strStateName) : m_State(in_strStateName)
	{
	}
	
	VState& GetState() { return m_State; }

	virtual void OnElementClose(xml::IVXMLElement* pElement)
	{
	}

	virtual void OnElementOpen(xml::IVXMLElement* pElement)
	{
		if( pElement->GetName() == "param" )
		{
			std::string name = pElement->GetAttributeValue<std::string>("name");
			std::string value = pElement->GetAttributeValue<std::string>("value");

			m_State.SetParameter(name.c_str(), value);
		}
		else if( pElement->GetName() == "iparam" )
		{
			m_IParamName = pElement->GetAttributeValue<std::string>("name");
		}
	}

	virtual void OnFileEnd()
	{
	}

	virtual void OnComment(VStringParam pText)
	{
	}

	virtual void OnText(VStringParam pText)
	{
		if( ! m_IParamName.empty() )
		{
			m_State.SetParameter(m_IParamName.c_str(), pText);
			m_IParamName = "";
		}
	}
};

class VRenderPassParser : public IVXMLVisitor
{
	VRenderPass& m_RenderPass;
public:
	VRenderPassParser(VRenderPass& in_RenderPass) : m_RenderPass(in_RenderPass)
	{
	}

	virtual void OnElementClose(xml::IVXMLElement* pElement)
	{
	}

	virtual void OnElementOpen(xml::IVXMLElement* pElement)
	{
		if( pElement->GetName() == VString("state") )
		{
			std::string stateName = pElement->GetAttributeValue<std::string>("name");

			VStateParser parser(stateName.c_str());
			pElement->VisitChildren(parser);
			m_RenderPass.AddState(parser.GetState());
		}
	}

	virtual void OnFileEnd() {}
	virtual void OnComment(VStringParam pText) {}
	virtual void OnText(VStringParam pText) {}
};

class VShaderPathParser : public IVXMLVisitor
{
	VShaderPath& m_ShaderPath;

public:
	VShaderPathParser(VShaderPath& in_ShaderPath) :
		m_ShaderPath(in_ShaderPath)
	{
	}

	virtual void OnElementClose(xml::IVXMLElement* pElement)
	{
	}

	virtual void OnElementOpen(xml::IVXMLElement* pElement)
	{
		if( pElement->GetName() == VString("renderPass") )
		{
			VRenderPassParser parser(m_ShaderPath.AddRenderPass());
			pElement->VisitChildren(parser);
		}
	}

	virtual void OnFileEnd()
	{
		V3D_ASSERT(false);
	}

	virtual void OnComment(VStringParam pText) {}
	virtual void OnText(VStringParam pText) {}
};

//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VEffectLoader::VEffectLoader()
{
	m_State = NotParsing;
}

/**
 * d'tor
 */
VEffectLoader::~VEffectLoader()
{
}

VEffectDescription VEffectLoader::LoadEffect(VStringParam in_strEffectFile)
{
	m_Effect.Clear();

	// open xml file for reading
	vfs::IVFileSystem::FileStreamPtr pFile =
		vfs::VFileSystemPtr()->OpenFile(in_strEffectFile, vfs::VReadAccess);
	IVXMLService::IVXMLElementPtr pRootNode =
		VXMLServicePtr()->GetRootElement(&*pFile);

	// check version
	if( pRootNode->GetName() != VString("effect") )
	{
		V3D_THROWMSG(VEffectLoaderException, 
			"Error loading effect description '" << in_strEffectFile << "': "
			<< "root element must be 'effect' found '" << pRootNode->GetName()
			<< "'");
	}

	if( ! HasAttributeWithValue(&*pRootNode, "version", std::string("1.0")) )
	{
		V3D_THROWMSG(VEffectLoaderException,
			"Error loading effect description '" << in_strEffectFile << "': "
			<< "version must be 1.0 (<effect version=\"1.0\")");
	}

	m_State = ParsingEffect;
	m_strFileName = in_strEffectFile;

	pRootNode->VisitChildren(*this);

	return m_Effect;
}

void VEffectLoader::LoadEffect(
	VStringParam in_strEffectFile, 
	resource::VResourceId in_pResource )
{
	m_Effect = LoadEffect(in_strEffectFile);

	// put effect into resource
	in_pResource->AddData(new VEffectDescription(m_Effect));
}

void VEffectLoader::OnElementClose(IVXMLElement* pElement)
{
}

void VEffectLoader::OnElementOpen(IVXMLElement* pElement)
{
	if( pElement->GetName() == VString("shaderPath") )
	{
		VShaderPathParser parser(m_Effect.AddShaderPath());
		pElement->VisitChildren(parser);
	}
}

void VEffectLoader::OnFileEnd()
{
}

void VEffectLoader::OnComment(VStringParam pText)
{
}

void VEffectLoader::OnText(VStringParam pText)
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

