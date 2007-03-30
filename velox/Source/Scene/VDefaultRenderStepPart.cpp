/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/VDefaultRenderStepPart.h>
//-----------------------------------------------------------------------------

namespace v3d { namespace graphics {
	std::istream& operator>>(std::istream& str, graphics::VColor4f& color);
	std::ostream& operator<<(std::ostream& str, const graphics::VColor4f& color);
}}

#include <V3d/Scene/IVShapePart.h>
#include <V3d/Math/VRBTransform.h>
#include <V3d/Graphics.h>
#include <V3d/Graphics/IVGraphicsService.h>
#include <V3d/Utils/VStringValue.h>
#include <V3d/Messaging/VMessageInterpreter.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Tags/VTagRegistry.h>

#include <sstream>
#include <string>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace graphics;
using namespace tags;
using std::string;
using std::stringstream;

namespace {
	const string excludePropertyName = "exclude-tags";
	const string includePropertyName = "include-tags";
}

/**
 * standard c'tor
 */
VDefaultRenderStepPart::VDefaultRenderStepPart()
{
	m_bIncludeAll = true;
	m_fFOV = 45.0f;
	m_fNearPlane = 1.0f;
	m_fFarPlane = 1000.0f;
}

/**
 * d'tor
 */
VDefaultRenderStepPart::~VDefaultRenderStepPart()
{
}

vfloat32 GetAspect(graphics::IVDevice& in_Device)
{
	const graphics::VDisplaySettings& displaySettings =
		*in_Device.GetRenderContext()->GetDisplaySettings();

	const vuint width = displaySettings.GetWidth();
	const vuint height = displaySettings.GetWidth();

	return vfloat32(width) / vfloat32(height);
}

void VDefaultRenderStepPart::Render(IVGraphicsPart* in_pScene)
{
	V3D_ASSERT(in_pScene != 0);

	static VServicePtr<graphics::IVGraphicsService> pGfxService;

	const vfloat32 aspect = GetAspect(*GetOutputDevice());
	math::VMatrix44f projectionMatrix;
	math::MakeProjectionMatrix(&projectionMatrix, m_fFOV, aspect, m_fNearPlane, m_fFarPlane);
	GetOutputDevice()->SetMatrix(graphics::IVDevice::ProjectionMatrix, projectionMatrix);

	glClearColor(m_BackgroundColor.red, m_BackgroundColor.green,
		m_BackgroundColor.blue, m_BackgroundColor.alpha);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	VRangeIterator<const IVShapePart> shape = in_pScene->GetVisibleMeshes();
	while( shape.HasNext() )
	{
		if( IsShapeToBeRendered(*shape) )
		{
			for(vuint pass = 0; pass < shape->GetPassCount(); ++pass)
			{
				const IVShapePart* pShape = &*shape;
				IVDevice& device(*GetOutputDevice());

				math::VRBTransform transform = shape->GetModelTransform();
				GetOutputDevice()->SetMatrix(
					IVDevice::ModelMatrix, transform.AsMatrix());

				shape->ApplyPassStates(pass, device);
				glCullFace(GL_BACK);
				glEnable(GL_CULL_FACE);
				shape->SendGeometry(*GetOutputDevice());
				shape->UnapplyPassStates(pass, device);
			}
		}

		++shape;
	}
}

vbool IntersectionEmpty(
	VRangeIterator<const VTag> tags1,
	const std::vector<VTag>& tags2)
{
	while( tags1.HasNext() )
	{
		std::vector<VTag>::const_iterator iter = 
			std::find(tags2.begin(), tags2.end(), *tags1);

		if( iter != tags2.end() )
			return false;

		++tags1;
	}

	return true;
}

vbool VDefaultRenderStepPart::IsShapeToBeRendered(const IVGraphicsPart& shape) const
{
	if( m_bIncludeAll || ! IntersectionEmpty(shape.Tags(), m_IncludeTags) )
	{
		return IntersectionEmpty(shape.Tags(), m_ExcludeTags);
	}
	else
		return false;
}

string TagNames(const std::vector<VTag>& tags)
{
	string tagNames;

	for(
		std::vector<VTag>::const_iterator tagIter = tags.begin();
		tagIter != tags.end();
	++tagIter)
	{
		tagNames += " ";
		tagNames += tagIter->GetName();
	}

	return tagNames;
}

void SetTags(const std::string& tagNames, std::vector<VTag>* tags)
{
	tags->clear();

	stringstream tagList(tagNames);

	while( ! tagList.eof() )
	{
		string tag;
		tagList >> tag;
		tags->push_back(VTagRegistryPtr()->GetTagWithName(tag));
	}
}

void VDefaultRenderStepPart::OnMessage(
	const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	namespace g = v3d::graphics;

	static messaging::VMessageInterpreter interpreter;

	if( ! interpreter.IsInitialized() )
	{
		interpreter.AddOption(SharedPtr(new messaging::VMemberVarOption<g::VColor4f>(
			"clearColor", this, &m_BackgroundColor)));
		interpreter.AddMemberOption("include-all", this, &m_bIncludeAll);
		interpreter.AddMemberOption("fov", this, &m_fFOV);
		interpreter.AddMemberOption("near-plane", this, &m_fNearPlane);
		interpreter.AddMemberOption("far-plane", this, &m_fFarPlane);
	}

	switch( interpreter.HandleMessage(this, in_Message, in_pAnswer) )
	{
	case messaging::VMessageInterpreter::GetSettings:
		{
			in_pAnswer->AddProperty(excludePropertyName, TagNames(m_ExcludeTags));
			in_pAnswer->AddProperty(includePropertyName, TagNames(m_IncludeTags));

		} break;

	case messaging::VMessageInterpreter::ApplySetting:
		{
			const string name = in_Message.GetAs<string>("name");
			const string tagList = in_Message.GetAs<string>("value");

			if( name == excludePropertyName )
				SetTags(tagList, &m_ExcludeTags);
			else if( name == includePropertyName )
				SetTags(tagList, &m_IncludeTags);
				
		} break;
	}
}

V3D_REGISTER_PART_PARSER(VDefaultRenderStepPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

