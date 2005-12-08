#include <V3d/Scene/Shapes/VSkyboxPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>

#include <V3d/OpenGL.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace entity;
using namespace resource;
using namespace graphics;

/**
 * standard c'tor
 */
VSkyboxPart::VSkyboxPart() :
	m_pRigidBodyPart(VPartDependency::Neighbour, RegisterTo()),
	m_pSceneManager(VPartDependency::Ancestor, RegisterTo())
{
	const float size = 10.0f;

	// left side
	m_Sides.push_back(VSide(this, VVector3f(-size, -size, size), VVector3f(0, 0, -size*2), VVector3f(0, size*2, 0)));
	// right side
	m_Sides.push_back(VSide(this, VVector3f(size, -size, -size), VVector3f(0, 0, size*2), VVector3f(0, size*2, 0)));
	// front side
	m_Sides.push_back(VSide(this, VVector3f(size, -size, size), VVector3f(-size*2, 0, 0), VVector3f(0, size*2, 0)));
	// back side
	m_Sides.push_back(VSide(this, VVector3f(-size, -size, -size), VVector3f(size*2, 0, 0), VVector3f(0, size*2, 0)));
	// top side
	m_Sides.push_back(VSide(this, VVector3f(size, size, size), VVector3f(-size*2, 0, 0), VVector3f(0, 0, -size*2)));
	// bottom side
	m_Sides.push_back(VSide(this, VVector3f(size, -size, -size), VVector3f(-size*2, 0, 0), VVector3f(0, 0, size*2)));
}

/**
 * d'tor
 */
VSkyboxPart::~VSkyboxPart()
{
}

template<typename ResourceData>
VResourceDataPtr<const ResourceData> GetResourceData(const std::string& in_strResource)
{
	return resource::GetResourceData<ResourceData>(in_strResource.c_str());
}

VResourceDataPtr<const IVMaterial> CreateTextureMaterial(const std::string& in_strTextureResource)
{
	VResourceId res = VResourceId(in_strTextureResource.c_str())->AddRandomNamedSubResource("skybox");
	VEffectDescription effect;
	VRenderPass& pass(effect.AddShaderPath().AddRenderPass());
	pass.AddState(TextureState(in_strTextureResource.c_str()));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthReadOnly));
	res->AddData(CopyPtr(effect));
	return res->GetData<IVMaterial>();
}

void VSkyboxPart::SetTextureDir(
	const std::string& in_strDirectory, 
	const std::string& in_strExtension)
{
	V3D_ASSERT(in_strDirectory[in_strDirectory.size()-1] == '/');
	V3D_ASSERT(in_strExtension.size() >= 1);
	V3D_ASSERT(in_strExtension[0] == '.');

	m_Sides[0].SetMaterial(CreateTextureMaterial(in_strDirectory + "left" + in_strExtension));
	m_Sides[1].SetMaterial(CreateTextureMaterial(in_strDirectory + "right" + in_strExtension));
	m_Sides[2].SetMaterial(CreateTextureMaterial(in_strDirectory + "front" + in_strExtension));
	m_Sides[3].SetMaterial(CreateTextureMaterial(in_strDirectory + "back" + in_strExtension));
	m_Sides[4].SetMaterial(CreateTextureMaterial(in_strDirectory + "top" + in_strExtension));
	m_Sides[5].SetMaterial(CreateTextureMaterial(in_strDirectory + "bottom" + in_strExtension));
}

void VSkyboxPart::UpdateAndCull(const graphics::IVCamera& in_Camera)
{
	m_pRigidBodyPart->SetPosition(in_Camera.GetPosition());
}

VRangeIterator<const IVShapePart> VSkyboxPart::GetVisibleMeshes() const
{
	return CreateIterator2<const IVShapePart>(m_Sides.begin(), m_Sides.end());
}

const math::VRBTransform& VSkyboxPart::GetModelTransform() const
{
	V3D_ASSERT(m_pRigidBodyPart.Get() != 0);
	return m_pRigidBodyPart->GetTransform();
}

void VSkyboxPart::Activate()
{
	m_pSceneManager->Add(this);
}

void VSkyboxPart::Deactivate()
{
	m_pSceneManager->Remove(this);
}

//-----------------------------------------------------------------------------

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

void VSkyboxPart::VSide::Activate()
{
}

void VSkyboxPart::VSide::Deactivate()
{
}

void glVertex(const math::VVector3f& vertex)
{
	glVertex3f(vertex[0], vertex[1], vertex[2]);
}

void VSkyboxPart::VSide::SendGeometry(graphics::IVDevice& in_Device) const
{
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(1, 1); glVertex(m_Position);
	glTexCoord2f(0, 1); glVertex(m_Position + m_Right);
	glTexCoord2f(0, 0); glVertex(m_Position + m_Right + m_Up);
	glTexCoord2f(1, 0); glVertex(m_Position + m_Up);
	glEnd();
}
//glTexCoord2f(0, 0); glVertex(m_Position);
//glTexCoord2f(1, 0); glVertex(m_Position + m_Right);
//glTexCoord2f(1, 1); glVertex(m_Position + m_Right + m_Up);
//glTexCoord2f(0, 1); glVertex(m_Position + m_Up);

const graphics::IVMaterial& VSkyboxPart::VSide::GetMaterial() const
{
	return *m_hMaterial;
	//return *graphics::IVDevice::GetDefaultMaterial();
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
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
