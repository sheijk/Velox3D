#include <V3d/Core/VException.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Scene/Shapes/VSkyPart.h>

using namespace gmtl;
using namespace v3d;
using namespace v3d::utils;
using namespace v3d::entity;
using namespace v3d::resource;
using namespace v3d::graphics;

namespace v3d {
namespace scene {


VSkyPart::VSkyPart(
				   std::string in_Mode,
				   vuint in_Sides,
				   vuint in_Slices,
				   vuint in_DivSteps,
				   vfloat32 in_fRadius,
				   vfloat32 in_fWidth,
				   vfloat32 in_fHeight,
				   vbool in_ShowAsLine
				   )
				   : m_ModeString(in_Mode),
				   m_Sides(in_Sides),
				   m_Slices(in_Slices),
				   m_DivSteps(in_DivSteps),
				   m_fRadius(in_fRadius),
				   m_fWidth(in_fWidth),
				   m_fHeight(in_fHeight),
				   m_ShowAsLine(in_ShowAsLine)
{
	BuildResources();
}

VSkyPart::~VSkyPart()
{
  delete m_pSkyDome;
}

void VSkyPart::SetColor(const graphics::VColor4f& in_Color)
{
	;
}

void VSkyPart::BuildResources()
{
	if(m_ModeString == "Dome")
		m_Mode = VSkyDomeGenerator::Dome;
	else
		m_Mode = VSkyDomeGenerator::Plane;

	m_pSkyDome = new VSkyDomeGenerator(
		m_Mode,
		m_Slices,
		m_Sides,
		m_DivSteps,
		m_fRadius,
		m_fWidth,
		m_fHeight);

	VResourceId res = VResourceManagerPtr()->CreateRandomNamedResource("sky");

	VVertexFormat format(
		VVertexFormat::Coordinates,
		m_pSkyDome->GetVertexCount(),
		0);

	VVertexBuffer* pVertexBuffer = new VVertexBuffer(
		m_pSkyDome->GetVertexBuffer(),
		m_pSkyDome->GetVertexCount() * 3, format);
  
	res->AddData(pVertexBuffer);
 
	VVertexFormat indexFormat(VVertexFormat::Indices, 0, m_pSkyDome->GetIndexCount());
	VVertexBuffer* pIndexBuffer = new VVertexBuffer(m_pSkyDome->GetIndexBuffer(),
		m_pSkyDome->GetIndexCount(), indexFormat);
	VResourceId indexRes = res->AddSubResource("indices");
	indexRes->AddData(pIndexBuffer);

	VMeshDescription* pMeshDescription = new VMeshDescription(VVertexFormat(
	  VVertexFormat::Coordinates | VVertexFormat::Indices, 
	  m_pSkyDome->GetVertexCount(), 
	  m_pSkyDome->GetIndexCount()));

	if (m_Mode == VSkyDomeGenerator::Dome)
	{
		pMeshDescription->SetGeometryType(VMeshDescription::TriangleStrip);
	}
	else
	{
		pMeshDescription->SetGeometryType(VMeshDescription::Triangles);
	}

	pMeshDescription->SetCoordinateResource(res->GetQualifiedName());
	pMeshDescription->SetCoordinateFormat(format.GetCoordinateFormat());
	pMeshDescription->SetIndexResource(indexRes->GetQualifiedName());
	pMeshDescription->SetIndexFormat(indexFormat.GetIndexFormat());
	res->AddData(pMeshDescription);

	m_hMesh = res->GetData<IVMesh>();
}

void VSkyPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	if(m_ShowAsLine)
	{
		glPolygonMode(GL_BACK,GL_LINE);
		glPolygonMode(GL_FRONT,GL_LINE);
	}
	
	glDisable( GL_CULL_FACE );

	graphics::VColor4f m_Color(1,1,1,1);
	glColor4f(m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha);
	
  	in_Device.RenderMesh(&*m_hMesh);
	
	glPopAttrib();
	glPopMatrix();

	if(m_ShowAsLine)
	{
		glPolygonMode(GL_BACK,GL_FILL);
		glPolygonMode(GL_FRONT,GL_FILL);
	}
}

void VSkyPart::SetSides(const vuint& in_Sides)
{
	m_pSkyDome->SetSides(in_Sides);
}

vuint VSkyPart::GetSides() const
{
	return m_pSkyDome->GetSides();
}

void VSkyPart::SetSlices(const vuint& in_Slices)
{
	m_Slices = in_Slices;
}

vuint VSkyPart::GetSlices() const
{
	return m_Slices;
}

std::string VSkyPart::GetMode() const
{
	return m_ModeString;
}

void VSkyPart::SetMode(const std::string& in_Mode)
{
	m_ModeString = in_Mode;
}

void VSkyPart::SetWidth(const vfloat32& in_fWidth)
{
	m_fWidth = in_fWidth;
}

vfloat32 VSkyPart::GetWidth() const
{
	return m_fWidth;
}

void VSkyPart::SetHeight(const vfloat32& in_fHeight)
{
	m_fHeight = in_fHeight;
}

vfloat32 VSkyPart::GetHeight() const
{
	return m_fHeight;
}

void VSkyPart::SetRadius(const float& in_fRadius)
{
	m_fRadius = in_fRadius;
}

vfloat32 VSkyPart::GetRadius() const
{
	return m_fRadius;
}

void VSkyPart::SetDivSteps(const vuint& in_DivSteps)
{
	m_DivSteps = in_DivSteps;
}

vuint VSkyPart::GetDivSteps() const
{
	return m_DivSteps;
}

messaging::VMessageInterpreter* VSkyPart::GetMessageInterpreterForClass()
{
  static messaging::VMessageInterpreter interpreter;

  return &interpreter;
}

void VSkyPart::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	interpreter.AddAccessorOption<VSkyPart, std::string>(
		"mode",
		&VSkyPart::GetMode,
		&VSkyPart::SetMode);

	interpreter.AddAccessorOption<VSkyPart, vuint>(
		"sides",
		&VSkyPart::GetSides,
		&VSkyPart::SetSides);

	interpreter.AddAccessorOption<VSkyPart, vuint>(
		"slices",
		&VSkyPart::GetSlices,
		&VSkyPart::SetSlices);

	interpreter.AddAccessorOption<VSkyPart, vuint>(
		"divSteps",
		&VSkyPart::GetDivSteps,
		&VSkyPart::SetDivSteps);
	
	interpreter.AddAccessorOption<VSkyPart, vfloat32>(
		"radius",
		&VSkyPart::GetRadius,
		&VSkyPart::SetRadius);

	interpreter.AddAccessorOption<VSkyPart, vfloat32>(
		"width",
		&VSkyPart::GetWidth,
		&VSkyPart::SetWidth);
	
	interpreter.AddAccessorOption<VSkyPart, vfloat32>(
		"height",
		&VSkyPart::GetHeight,
		&VSkyPart::SetHeight);

	VMeshPartBase::SetupProperties( interpreter );
}

V3D_REGISTER_PART_PARSER(VSkyPart);
}
}