#include <V3d/Scene/VDefaultRenderStepPart.h>
//-----------------------------------------------------------------------------

namespace v3d { namespace graphics {
	std::istream& operator>>(std::istream& str, graphics::VColor4f& color);
	std::ostream& operator<<(std::ostream& str, const graphics::VColor4f& color);
}}

#include <V3d/Scene/IVShapePart.h>
#include <V3d/Math/VRBTransform.h>
#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3dLib/Utils/VStringValue.h>
#include <V3d/Messaging/VMessageInterpreter.h>

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace graphics;

/**
 * standard c'tor
 */
VDefaultRenderStepPart::VDefaultRenderStepPart()
{
}

/**
 * d'tor
 */
VDefaultRenderStepPart::~VDefaultRenderStepPart()
{
}

void VDefaultRenderStepPart::Render(IVGraphicsPart* in_pScene)
{
	V3D_ASSERT(in_pScene != 0);

	glClearColor(m_BackgroundColor.red, m_BackgroundColor.green,
		m_BackgroundColor.blue, m_BackgroundColor.alpha);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	VRangeIterator<const IVShapePart> shape = in_pScene->GetVisibleMeshes();
	while( shape.HasNext() )
	{
		const IVMaterial& material = shape->GetMaterial();

		for(vuint pass = 0; pass < material.PassCount(); ++pass)
		{
			math::VRBTransform transform = shape->GetModelTransform();

			GetOutputDevice()->SetMatrix(IVDevice::ModelMatrix, transform.AsMatrix());

			ApplyMaterial(*GetOutputDevice(), &material.GetPass(pass));
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			shape->SendGeometry(*GetOutputDevice());
		}

		++shape;
	}
}

/*
class VOption
{
public:
	VOption(const std::string& name) { m_strName = name; }
	virtual ~VOption() {}

	virtual void Write(const std::string& value, void* object) = 0;
	virtual std::string Read(void* object) = 0;

	std::string GetName() const { return m_strName; }
	void SetName(const std::string& in_Value) { m_strName = in_Value; }
private:
	std::string m_strName;
};

template<typename T>
class VMemberVarOption : public VOption
{
public:
	VMemberVarOption(const std::string& name, void* object, T* member) :
		VOption(name)
	{
		m_nOffsetBytes = BytesDistance(object, member);
	}

	virtual void Write(const std::string& value, void* object)
	{
		T* address = MemberAddress(object);

		utils::VStringValue val(value);
		T newValue = val.Get<T>();
		*address = newValue;
	}

	virtual std::string Read(void* object)
	{
		T* address = MemberAddress(object);

		utils::VStringValue val;
		val.Set(*address);
		return val.Get<std::string>();
	}

private:
	T* MemberAddress(void* object)
	{
		vbyte* objectAddress = reinterpret_cast<vbyte*>(object);
		vbyte* memberAddress = objectAddress + m_nOffsetBytes;
		return reinterpret_cast<T*>(memberAddress);
	}

	vuint BytesDistance(void* a, void* b)
	{
		return (vbyte*)b - (vbyte*)a;
	}

	vuint m_nOffsetBytes;
};

/*
class VMessageInterpreter
{
public:
	void AddOption(VOption* option)
	{
		m_Options.insert(make_pair(option->GetName(), SharedPtr(option)));
	}

	vbool HandleMessage(void* object,
		const messaging::VMessage& in_Message,
		messaging::VMessage* io_pAnswer)
	{
		if( ! in_Message.HasProperty("type") )
			return false;

		std::string request = in_Message.Get("type").Get<std::string>();

		if( request == "getSettings" )
		{
			if( io_pAnswer == 0 )
				return false;

			OptionMap::iterator option = m_Options.begin();
			for( ; option != m_Options.end(); ++option)
			{
				std::string name = option->first;
				std::string value = option->second->Read(object);

				io_pAnswer->AddProperty(name, value);
			}

			return true;
		}
		else if( request == "update" )
		{
			const std::string name = in_Message.Get("name").Get<std::string>();
			const std::string value = in_Message.Get("value").Get<std::string>();

			OptionMap::iterator option = m_Options.find(name);

			if( option != m_Options.end() )
			{
				option->second->Write(value, object);
				return true;
			}
			else
				return false;
		}
		else
		{
			return false;
		}
	}

	vbool GetInitialized() const { return m_bInitialized; }
	void SetInitialized(const vbool& in_Value) { m_bInitialized = in_Value; }

private:
	typedef std::map<std::string, VSharedPtr<VOption> > OptionMap;
	OptionMap m_Options;

	vbool m_bInitialized;
};
/**/

void VDefaultRenderStepPart::OnMessage(
	const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	namespace g = v3d::graphics;

	static messaging::VMessageInterpreter interpreter;

	if( ! interpreter.IsInitialized() )
	{
		interpreter.AddOption(new messaging::VMemberVarOption<g::VColor4f>("clearColor", this, &m_BackgroundColor));
	}

	interpreter.HandleMessage(this, in_Message, in_pAnswer);
}

namespace {
	entity::VPartParser<VDefaultRenderStepPart> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
