#include <V3dLib/Graphics/Importer/VEffectLoader.h>
//-----------------------------------------------------------------------------
#include <V3d/Vfs.h>

#include <V3d/Core.h>
#include <V3dLib/Graphics/Materials/EffectUtils.h>
#include <V3d/Resource/VResource.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::xml;
using namespace v3d::resource;

//-----------------------------------------------------------------------------
#define V3D_THROWMSG(exceptionType, message) \
{ std::stringstream cause; cause << message; throw exceptionType(cause.str().c_str(), __FILE__, __LINE__); }

//-----------------------------------------------------------------------------
class VStateParser : public IVXMLVisitor
{
	VState m_State;

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
		std::string name = pElement->GetAttributeValue<std::string>("name");
		std::string value = pElement->GetAttributeValue<std::string>("value");

		vout << "\t\t\t"
			<< name
			<< "="
			<< value
			<< vendl;

		m_State.SetParameter(name.c_str(), value);
	}

	virtual void OnFileEnd()
	{
	}

	virtual void OnComment(VStringParam pText)
	{
	}

	virtual void OnText(VStringParam pText)
	{
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

			vout << "\t\tState " << stateName << vendl;
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
			vout << "\tRenderPass" << vendl;
			
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

void VEffectLoader::LoadEffect(
	VStringParam in_strEffectFile, 
	resource::VResourceId in_pResource )
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

	vout << "Resulting effect description:" << vendl;
	PrintEffectDescription(m_Effect);

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
		vout << "ShaderPass" << vendl;
		VShaderPathParser parser(m_Effect.AddShaderPath());
		pElement->VisitChildren(parser);
	}
}

void VEffectLoader::OnFileEnd()
{
	vout << "Parsing effect file '" << m_strFileName << "' done" << vendl;
}

void VEffectLoader::OnComment(VStringParam pText)
{
	vout << "Found comment '" << pText << "'" << vendl;
}

void VEffectLoader::OnText(VStringParam pText)
{
	vout << "Found text '" << pText << "'" << vendl;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
