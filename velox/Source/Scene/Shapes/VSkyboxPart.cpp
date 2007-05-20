/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Shapes/VSkyboxPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/RangeIter.h>

#include <V3d/Graphics/IVDevice.h>
#include <V3d/Graphics.h>
#include <V3d/Graphics.h>
#include <V3d/OpenGL.h>

#include <V3d/Entity/VGenericPartParser.h>

#include <V3d/Messaging/VMessageInterpreter.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indentespace entity;
using namespace entity;
using namespace resource;
using namespace graphics;
using namespace math;

namespace {
	const std::string vertexShader =
		"varying vec2 texCoord;"
		"void main() {"
		"	gl_Position = ftransform();"
		"	texCoord = gl_MultiTexCoord0.st;"
		"}"
		"";
	const std::string fragmentShader =
		"uniform sampler2D texture;"
		"uniform vec4 baseColor;"
		"varying vec2 texCoord;"
		"void main() {"
		"	gl_FragDepth = .999;"
		"	gl_FragColor = texture2D(texture, texCoord);"
//		"	gl_FragColor = texture2D(texture, texCoord) * baseColor;"
//		"	gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);"
		"}";
	const std::string TEX_PARAM_NAME = "texture";
	const std::string COLOR_PARAM_NAME = "baseColor";

	const std::string VERTEX_RES = "/system/graphics/skybox/vertex";
	const std::string FRAGMENT_RES = "/system/graphics/skybox/fragment";

	VResourceId CreateResource(const std::string& name)
	{
		return VResourceManagerPtr()->CreateResource(name.c_str());
	}

	VResourceDataPtr<const IVMaterial> CreateTextureMaterial(const std::string& in_strTextureResource)
	{
		// store fragment and vertex program into resources
		static VResourceId fragmentRes = CreateResource(FRAGMENT_RES);
		static VResourceId vertexRes = CreateResource(VERTEX_RES);
		static vbool initalized = false;
		if( ! initalized )
		{
			fragmentRes->AddData(new VTextFile(fragmentShader));
			vertexRes->AddData(new VTextFile(vertexShader));

			initalized = true;
		}

		VResourceId res = VResourceId(in_strTextureResource.c_str())->AddRandomNamedSubResource("skybox");

		VEffectDescription effect = GLSLEffect(VERTEX_RES, FRAGMENT_RES);
		effect.ShaderPath(0).RenderPass(0).AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthReadOnly));
		res->AddData(CopyPtr(effect));

		VResourceDataPtr<IVMaterial> material = res->GetMutableData<IVMaterial>();
		IVParameter* textureParam = material->GetParameterByName(TEX_PARAM_NAME);
		if( textureParam != 0 )
			textureParam->ApplyTexture(in_strTextureResource.c_str());

		IVParameter* colorParam = material->GetParameterByName(COLOR_PARAM_NAME);
		if( colorParam != 0 )
			colorParam->Apply(ToVector4f(0, 1, 0, 1));

		return res->GetData<IVMaterial>();

		//VResourceId res = VResourceId(in_strTextureResource.c_str())->AddRandomNamedSubResource("skybox");
		//VEffectDescription effect;
		//VRenderPass& pass(effect.AddShaderPath().AddRenderPass());
		//pass.AddState(TextureState(in_strTextureResource.c_str()));
		//pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthReadOnly));
		//pass.AddState(LightingState(false));
		//res->AddData(CopyPtr(effect));
		//return res->GetData<IVMaterial>();
	}
}

//-----------------------------------------------------------------------------

class VSkyboxPart::VSide : public IVShapePart
{
public:
	VSide(VSkyboxPart* in_pContainer, 
		math::VVector3f in_Pos,
		math::VVector3f in_Right, 
		math::VVector3f in_Up);

	void SetMaterial(
		resource::VResourceDataPtr<const graphics::IVMaterial> in_hMaterial);

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;
	virtual const graphics::IVMaterial& GetMaterial() const;
	virtual vuint GetPassCount() const;
	virtual void ApplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const;
	virtual void UnapplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const;
	virtual const math::VRBTransform& GetModelTransform() const;
	virtual void UpdateAndCull(const graphics::IVCamera& in_Camera);
	virtual VRangeIterator<const IVShapePart> GetVisibleMeshes() const;

	virtual const VTypeInfo& GetTypeInfo() const { return IVShapePart::GetTypeInfo(); }

private:
	resource::VResourceDataPtr<const graphics::IVMaterial> m_hMaterial;
	VSkyboxPart* m_pContainer;

	math::VVector3f m_Position;
	math::VVector3f m_Right;
	math::VVector3f m_Up;
};

VSkyboxPart::VSide::VSide(
	VSkyboxPart* in_pContainer, 
	math::VVector3f in_Pos,
	math::VVector3f in_Right, 
	math::VVector3f in_Up)
{
	m_Position = in_Pos;
	m_Right = in_Right;
	m_Up = in_Up;
	m_pContainer = in_pContainer;

	m_hMaterial = graphics::IVDevice::GetDefaultMaterial();
}

void VSkyboxPart::VSide::SetMaterial(
	resource::VResourceDataPtr<const graphics::IVMaterial> in_hMaterial)
{
	m_hMaterial = in_hMaterial;
}

void glVertex(const math::VVector3f& vertex)
{
	glVertex3f(vertex[0], vertex[1], vertex[2]);
}

void VSkyboxPart::VSide::SendGeometry(graphics::IVDevice& in_Device) const
{
	VResourceDataPtr<IVMaterial> mat =
		GetMutableResourceData<IVMaterial>(
		m_hMaterial.GetEnclosingResource()->GetQualifiedName().c_str());

	IVParameter* baseColorParam = mat->GetParameterByName(COLOR_PARAM_NAME);
	if( baseColorParam != 0 )
	{
		baseColorParam->Apply(ToVector4f(m_pContainer->m_BaseColor));
	}

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(1, 1); glVertex(m_Position);
	glTexCoord2f(0, 1); glVertex(m_Position + m_Right);
	glTexCoord2f(0, 0); glVertex(m_Position + m_Right + m_Up);
	glTexCoord2f(1, 0); glVertex(m_Position + m_Up);
	glEnd();
}

const graphics::IVMaterial& VSkyboxPart::VSide::GetMaterial() const
{
	return *m_hMaterial;
}

vuint VSkyboxPart::VSide::GetPassCount() const
{
	if( m_hMaterial != 0 )
		return m_hMaterial->PassCount();
	else
		return 0;
}

void VSkyboxPart::VSide::ApplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const
{
	ApplyMaterial(in_Device, &m_hMaterial->GetPass(in_nPassNum));
}

void VSkyboxPart::VSide::UnapplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const
{
	//nothing..
}

const math::VRBTransform& VSkyboxPart::VSide::GetModelTransform() const
{
	return m_pContainer->GetModelTransform();
}

void VSkyboxPart::VSide::UpdateAndCull(const graphics::IVCamera& in_Camera)
{
}

VRangeIterator<const IVShapePart> VSkyboxPart::VSide::GetVisibleMeshes() const
{
	return CreateSingleValueIterator<const IVShapePart>(this);
}

//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VSkyboxPart::VSkyboxPart() :
	m_pRigidBodyPart(RegisterTo()),
	m_pSceneManager(RegisterTo())
{
	const float size = 100.0f;
	m_BaseColor = VColor4f(1, 1, 1, 1);

	// left side
	m_Sides.push_back(SharedPtr(new VSide(this, VVector3f(-size, -size, size), VVector3f(0, 0, -size*2), VVector3f(0, size*2, 0))));
	// right side
	m_Sides.push_back(SharedPtr(new VSide(this, VVector3f(size, -size, -size), VVector3f(0, 0, size*2), VVector3f(0, size*2, 0))));
	// front side
	m_Sides.push_back(SharedPtr(new VSide(this, VVector3f(size, -size, size), VVector3f(-size*2, 0, 0), VVector3f(0, size*2, 0))));
	// back side
	m_Sides.push_back(SharedPtr(new VSide(this, VVector3f(-size, -size, -size), VVector3f(size*2, 0, 0), VVector3f(0, size*2, 0))));
	// top side
	m_Sides.push_back(SharedPtr(new VSide(this, VVector3f(size, size, size), VVector3f(-size*2, 0, 0), VVector3f(0, 0, -size*2))));
	// bottom side
	m_Sides.push_back(SharedPtr(new VSide(this, VVector3f(size, -size, -size), VVector3f(-size*2, 0, 0), VVector3f(0, 0, size*2))));
}

/**
 * d'tor
 */
VSkyboxPart::~VSkyboxPart()
{
}

void VSkyboxPart::SetBaseColor(const VColor4f& in_Color)
{
	m_BaseColor = in_Color;
}

void VSkyboxPart::SetTextureDir(
	const std::string& in_strDirectory, 
	const std::string& in_strExtension)
{
	if( in_strDirectory[in_strDirectory.size()-1] == '/' &&
		in_strExtension.size() >= 1 &&
		in_strExtension[0] == '.' )
	{
		m_Sides[0]->SetMaterial(CreateTextureMaterial(in_strDirectory + "left" + in_strExtension));
		m_Sides[1]->SetMaterial(CreateTextureMaterial(in_strDirectory + "right" + in_strExtension));
		m_Sides[2]->SetMaterial(CreateTextureMaterial(in_strDirectory + "front" + in_strExtension));
		m_Sides[3]->SetMaterial(CreateTextureMaterial(in_strDirectory + "back" + in_strExtension));
		m_Sides[4]->SetMaterial(CreateTextureMaterial(in_strDirectory + "top" + in_strExtension));
		m_Sides[5]->SetMaterial(CreateTextureMaterial(in_strDirectory + "bottom" + in_strExtension));

		m_strTextureDir = in_strDirectory;
	}
}

void VSkyboxPart::UpdateAndCull(const graphics::IVCamera& in_Camera)
{
	m_pRigidBodyPart->SetPosition(in_Camera.GetPosition());
}

VRangeIterator<const IVShapePart> VSkyboxPart::GetVisibleMeshes() const
{
	return CreateDerefIterator<const IVShapePart>(m_Sides.begin(), m_Sides.end());
}

const math::VRBTransform& VSkyboxPart::GetModelTransform() const
{
	V3D_ASSERT(m_pRigidBodyPart.Get() != 0);
	return m_pRigidBodyPart->GetTransform();
}

void VSkyboxPart::OnActivate()
{
	m_pSceneManager->Add(this);
}

void VSkyboxPart::OnDeactivate()
{
	m_pSceneManager->Remove(this);
}

namespace {
	// property names
	const std::string PN_TEXTURE_DIR = "texture-dir";
}

messaging::VMessageInterpreter* VSkyboxPart::GetMessageInterpreterForClass()
{
	static messaging::VMessageInterpreter interpreter;

	return &interpreter;
}

std::string VSkyboxPart::GetTextureDir() const
{
	return m_strTextureDir;
}

void VSkyboxPart::SetTextureDir(const std::string& dirname)
{
	SetTextureDir(dirname, ".jpg");
}

void VSkyboxPart::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	interpreter.AddAccessorOption<VSkyboxPart, std::string>(
		PN_TEXTURE_DIR,
		&VSkyboxPart::GetTextureDir,
		&VSkyboxPart::SetTextureDir);

	IVGraphicsPart::SetupProperties( interpreter );
}

//void VSkyboxPart::OnMessage(
//	const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
//{
//	using std::string;
//
//	if( ! in_Message.HasProperty("type") )
//		return;
//
//	string request = in_Message.Get("type").Get<string>();
//
//	if( request == "getSettings" )
//	{
//		if( in_pAnswer == 0 )
//			return;
//
//		in_pAnswer->AddProperty(PN_TEXTURE_DIR, m_strTextureDir);
//	}
//	else if( request == "update" )
//	{
//		const string name = in_Message.Get("name").Get<string>();
//		const string value = in_Message.Get("value").Get<string>();
//
//		if( name == PN_TEXTURE_DIR )
//		{
//			SetTextureDir(value, ".jpg");
//		}
//	}
//}

V3D_REGISTER_PART_PARSER(VSkyboxPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

