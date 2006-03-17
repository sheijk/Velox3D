#include <V3d/Scene/Shapes/VSphereMeshPart.h>
//-----------------------------------------------------------------------------
#include <V3d/OpenGL.h>
#include <GL/glut.h>

#include <v3d/Graphics/IVDevice.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Messaging/VMessageInterpreter.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VSphereMeshPart::VSphereMeshPart(vfloat32 in_fRadius, vuint in_nDetail) :
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
	m_fRadius = in_fRadius;
	m_nDetail = in_nDetail;
}

void VSphereMeshPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	ApplyParameterValues();
	glutSolidSphere(m_fRadius, m_nDetail, m_nDetail);
}

void VSphereMeshPart::OnMessage(const messaging::VMessage& in_Message, 
	messaging::VMessage* in_pAnswer)
{
	static messaging::VMessageInterpreter interpreter;

	if( ! interpreter.IsInitialized() )
	{
		interpreter.AddMemberOption("radius", this, &m_fRadius);

		interpreter.SetInitialized(true);
	}

	interpreter.HandleMessage(this, in_Message, in_pAnswer);
}

namespace {
	//class VSphereMeshParser : public entity::VGenericPartParser
	//{
	//public:
	//	VSphereMeshParser()
	//		: VGenericPartParser()
	//	{
	//	}

	//	virtual VSharedPtr<entity::IVPart> CreatePart()
	//	{
	//		return SharedPtr(new VSphereMeshPart());
	//	}

	//	virtual std::string GetType() const
	//	{
	//		return GetTypeInfo<VSphereMeshPart>().GetName();
	//	}
	//};

	//VSphereMeshParser parser;
	entity::VPartParser<VSphereMeshPart> g_SphereMeshParser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------