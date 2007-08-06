#include <V3d/Scene/Shapes/VSkyPart.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glfw.h>
#include <V3d/Core/VException.h>
#include <V3d/Graphics/Importer/Base/VImportedBufferDescription.h>
#include <V3d/Entity/VGenericPartParser.h>

#include <V3d/Graphics/Geometry/VColor4f.h>

using namespace gmtl;
using namespace v3d;
using namespace v3d::utils;
using namespace v3d::entity;
using namespace v3d::resource;
using namespace v3d::graphics;
namespace v3d {
namespace scene {

VSkyDomeGenerator::VSkyDomeGenerator()
{
  Generate();
}

void VSkyDomeGenerator::Generate()
{ 
	m_pVertexBuffer = 0;
	m_pTexCoords = 0;
	m_pIndexBuffer = 0;
	
	m_fRadius = 20;
	m_nSides = 40;
	m_nSlices = 40;

	GenerateVertices();
}

void VSkyDomeGenerator::GenerateVertices()
{
	m_nVertexCount = (m_nSlices+ 1) * (m_nSides + 1);
	m_nIndexCount = m_nSlices * (m_nSides + 1) * 2;

	m_pVertexBuffer = new float [m_nVertexCount * 3];
	m_pIndexBuffer = new uint[m_nIndexCount];

	float polyAng = (2.0f * Math::PI / m_nSides);
	float angle = 0.0f;
	float x, y, z;

	for (uint j = 0; j <= m_nSlices; j++)
	{
		float val = static_cast<float>(j) / static_cast<float>(m_nSlices);
		angle = val * val * Math::PI * 0.5f;
		for (uint i = 0; i <= m_nSides; i++)
		{						
			x = cos(i * polyAng) * cos(angle);
			y = sin(angle);
			z = sin(i * polyAng) * cos(angle);

			m_pVertexBuffer[3*(j * (m_nSides + 1) + i )+ 0] = x * m_fRadius;
			m_pVertexBuffer[3*(j * (m_nSides + 1) + i )+ 1] = y * m_fRadius;	
			m_pVertexBuffer[3*(j * (m_nSides + 1) + i )+ 2] = z * m_fRadius;
		}
	}

	int nCount = 0;
	for (uint j = 1; j <= m_nSlices; j++)
	{
		for (uint i = 0; i <= m_nSides; i++)
		{			
			m_pIndexBuffer[nCount++] = j * (m_nSides + 1) + i;
			m_pIndexBuffer[nCount++] = (j - 1) * (m_nSides + 1) + i;
		}
	}
}

VSkyDomeGenerator::~VSkyDomeGenerator()
{
  delete [] m_pVertexBuffer;
  delete [] m_pIndexBuffer;
  delete [] m_pTexCoords;
}

vuint VSkyDomeGenerator::GetVertexCount()
{
  return m_nVertexCount;
}

float* VSkyDomeGenerator::GetVertexBuffer()
{
  return m_pVertexBuffer;
}

float* VSkyDomeGenerator::GetTextureBuffer()
{
  return m_pTexCoords;
}

vuint* VSkyDomeGenerator::GetIndexBuffer()
{
  return m_pIndexBuffer;
}

void VSkyDomeGenerator::SetRadius(float in_fRadius)
{
	m_fRadius = in_fRadius;
}

void VSkyDomeGenerator::SetSides(uint in_Sides)
{
	m_nSides = in_Sides;
}

void VSkyDomeGenerator::SetSlices(uint in_Slices)
{
	m_nSlices = in_Slices;
}

vfloat32 VSkyDomeGenerator::GetRadius() const
{
	return m_fRadius;
}

vuint VSkyDomeGenerator::GetSlices() const 
{
	return m_nSlices;
}

vuint VSkyDomeGenerator::GetSides() const 
{
	return m_nSides;
}
//TODO: SkyPlane generation code
//void VSkyDomeGenerator::GenerateVertices()
//{
//  m_pVertexBuffer = new float[3 * m_VertexCount];
//  m_pTexCoords = new float[2 * m_VertexCount ];
//  
//  m_pIndexBuffer = new uint[2 * 3 * m_DivSteps*m_DivSteps];
//  m_pColorBuffer = new Col4f[m_VertexCount];
//  
//  uint nVertexCount = 0;
//  uint nIndexCount = 0;
//
//  float planeSize = 2 * gmtl::Math::sqrt(m_Width*m_Width - m_Height * m_Height);
//  float planeDelta = planeSize / m_DivSteps;
//  float texDelta = 1.0f / m_DivSteps;
//  Vec3f vertex;
//  uint nTexCoord = 0;
//
//  for(uint i = 0; i <= m_DivSteps; i++)
//  {
//    for(uint j = 0; j <= m_DivSteps; j++)
//    {
//      vertex[0] = (-0.5f * planeSize) + j*planeDelta;
//      vertex[2] = (-0.5f * planeSize) + i*planeDelta;
//
//      float x_height = vertex[0] * vertex[0] / m_Width;
//      float z_height = vertex[2] * vertex[2] / m_Width;
//      float height = x_height + z_height;
//
//      m_pVertexBuffer[nVertexCount] = vertex[0];
//      m_pVertexBuffer[nVertexCount+1] = -height;
//      m_pVertexBuffer[nVertexCount+2] = vertex[2];
//      nVertexCount +=3;
//      
//      float uTile = 1;
//      float vTile = 1;
//      float u = uTile * (float)j * texDelta;
//      float v = vTile * (1.0f - (i* texDelta));
//      m_pTexCoords[nTexCoord*2] = u;
//      m_pTexCoords[nTexCoord*2+1] = v;
//      nTexCoord++;
//    }
//  }
//  m_VertexCount = nVertexCount / 3;
//
//  for(uint i = 0; i < m_DivSteps;  i++)
//  {
//    for(uint j = 0; j < m_DivSteps; j++)
//    {
//      int start = (i*(m_DivSteps+1) +j);
//      
//      m_pIndexBuffer[nIndexCount] = start;
//      nIndexCount++;
//      m_pIndexBuffer[nIndexCount] = start+1;
//      nIndexCount++;
//      m_pIndexBuffer[nIndexCount] = start+m_DivSteps+1;
//      nIndexCount++;
//
//      m_pIndexBuffer[nIndexCount] = start+1;
//      nIndexCount++;
//      m_pIndexBuffer[nIndexCount] = start+m_DivSteps + 2;
//      nIndexCount++;
//      m_pIndexBuffer[nIndexCount] = start+m_DivSteps + 1;
//      nIndexCount++;
//    }
//  }
//  m_IndexCount = nIndexCount;
//}

vuint VSkyDomeGenerator::GetIndexCount()
{
  return m_nIndexCount;
}

VSkyPart::VSkyPart()
{
  BuildResources();
}

VSkyPart::VSkyPart(const v3d::graphics::VColor4f& in_Color)
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
  m_pSkyDome = new VSkyDomeGenerator();
  VResourceId res = VResourceManagerPtr()->CreateRandomNamedResource("sky");
  
  VVertexFormat format(
	VVertexFormat::Coordinates,
	m_pSkyDome->GetVertexCount(),
	0);

  VVertexBuffer* pVertexBuffer = new VVertexBuffer(
	m_pSkyDome->GetVertexBuffer(),
	m_pSkyDome->GetVertexCount() * 3, format);
  
  res->AddData(pVertexBuffer);
  
  

 // texCoordBufferFormat.SetTexCoordFormat(0,VDataFormat(0, m_pVSkyPlanePart->GetVertexCount(), 2));

  VVertexFormat indexFormat(VVertexFormat::Indices, 0, m_pSkyDome->GetIndexCount());
  VVertexBuffer* pIndexBuffer = new VVertexBuffer(m_pSkyDome->GetIndexBuffer(),
  m_pSkyDome->GetIndexCount(), indexFormat);
  VResourceId indexRes = res->AddSubResource("indices");
  indexRes->AddData(pIndexBuffer);
    
  VMeshDescription* pMeshDescription = new VMeshDescription(VVertexFormat(
	VVertexFormat::Coordinates /*| VVertexFormat::TexCoords*/ | VVertexFormat::Indices, 
	m_pSkyDome->GetVertexCount(), 
	m_pSkyDome->GetIndexCount()));

  pMeshDescription->SetGeometryType(VMeshDescription::TriangleStrip);
  pMeshDescription->SetCoordinateResource(res->GetQualifiedName());
  pMeshDescription->SetCoordinateFormat(format.GetCoordinateFormat());
  //pMeshDescription->SetTexCoordFormat(0, format.GetTexCoordFormat(0));
  //pMeshDescription->SetTexCoordResource(0, res->GetQualifiedName());
  pMeshDescription->SetIndexResource(indexRes->GetQualifiedName());
  pMeshDescription->SetIndexFormat(indexFormat.GetIndexFormat());
  res->AddData(pMeshDescription);

  m_hMesh = res->GetData<IVMesh>();
}
void VSkyPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	//glPolygonMode(GL_BACK,GL_LINE);
	//glPolygonMode(GL_FRONT,GL_LINE);
	glDisable( GL_CULL_FACE );

	graphics::VColor4f m_Color(1,1,1,1);
	glColor4f(m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha);
	
  	in_Device.RenderMesh(&*m_hMesh);
	
	glPopAttrib();
	glPopMatrix();

	//glPolygonMode(GL_BACK,GL_FILL);
	//glPolygonMode(GL_FRONT,GL_FILL);	
}
messaging::VMessageInterpreter* VSkyPart::GetMessageInterpreterForClass()
{
  static messaging::VMessageInterpreter interpreter;

  return &interpreter;
}

void VSkyPart::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	/*interpreter.AddAccessorOption<VSkyDomeGenerator, vuint>(
	"Slices",
	&VSkyDomeGenerator::GetSlices,
	&VSkyDomeGenerator::SetSlices);*/
 // interpreter.AddAccessorOption<VSkyPlanePartPart, VVector3f>(
	//"MaxPoint",
	//&VBoxMeshPart::GetMaxPoint,
	//&VBoxMeshPart::SetMaxPoint);

 // VMeshPartBase::SetupProperties( interpreter );
}

V3D_REGISTER_PART_PARSER(VSkyPart);
}
}