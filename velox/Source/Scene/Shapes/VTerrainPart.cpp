#include <V3d/Scene/Shapes/VTerrainPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Graphics.h>
#include <V3dLib/Graphics/Geometry.h>

#include <V3d/OpenGL.h>

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace graphics;
using namespace resource;

/**
 * standard c'tor
 */
VTerrainPart::VTerrainPart() : VMeshPartBase(IVDevice::GetDefaultMaterial())
{
	const vfloat32 size = 100.0f;
	m_XZMax = ToVector2f(size, size);
	m_XZMin = ToVector2f(-size, -size);
	//m_XZMax = ToVector2f(30, 5);
	//m_XZMin = ToVector2f(-10, -3);

	SetVertexCount(256, 256);
}

/**
 * d'tor
 */
VTerrainPart::~VTerrainPart()
{
}

void VTerrainPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	//ApplyParameterValues(in_Device);

	// draw border
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex3f(m_XZMin[0], 0, m_XZMin[1]);
	glVertex3f(m_XZMin[0], 0, m_XZMax[1]);
	glVertex3f(m_XZMax[0], 0, m_XZMax[1]);
	glVertex3f(m_XZMax[0], 0, m_XZMin[1]);
	glEnd();
	//const vfloat32 size = 10.0f;

	//glBegin(GL_QUADS);
	//glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	//glTexCoord2f(1, 0); glVertex3f(size, 0, 0);
	//glTexCoord2f(1, 1); glVertex3f(size, 0, size);
	//glTexCoord2f(0, 1); glVertex3f(0, 0, size);
	//glEnd();

	glColor3f(1, 1, 1);
	in_Device.RenderMesh(&*m_hMesh);
}

vuint VTerrainPart::GetVertexCount() const
{
	return m_nVertexCountHor * m_nVertexCountVert;
}

vuint VTerrainPart::GetIndexCount() const
{
	return m_nVertexCountHor * (m_nVertexCountVert-1) * 2 + ((m_nVertexCountVert-1) * 2);
}

vuint VTerrainPart::GetVertexNum(vuint x, vuint y) const
{
	return y * m_nVertexCountHor + x;
}

void VTerrainPart::ApplyHeightValues(const VArray2d<vfloat32>& in_Array)
{
	V3D_ASSERT(m_nVertexCountHor <= in_Array.GetWidth());
	V3D_ASSERT(m_nVertexCountVert <= in_Array.GetHeight());

	for(vuint y = 0; y < m_nVertexCountVert; ++y)
	for(vuint x = 0; x < m_nVertexCountHor; ++x)
	{
		VVertex3f coord = m_hVertexBuffer->GetCoordinate(GetVertexNum(x, y));
		coord.y = in_Array.Get(x, y) + 20;
		m_hVertexBuffer->SetCoordinate(coord, GetVertexNum(x, y));
	}

	GenerateNormals();
}

typedef vfloat32 (*Function2d)(vfloat32, vfloat32);

vfloat32 SinCosMult(vfloat32 x, vfloat32 y)
{
	using math::Pi;

	//return sin(x * Pi()) * cos(y * Pi());

	return sin(2 * x * Pi()) * cos(2 * y * Pi());
}

vfloat32 Hill(vfloat32 n)
{
	return 1.0f + cos(math::Pi() * 1.8f * (n - .5f));
}

vfloat32 Hill(vfloat32 x, vfloat32 y)
{
	return - Hill(x) * Hill(y);
}

void MakeFractal(VArray2d<vfloat32>* in_pArray, vuint in_nOctaves, vfloat32 in_fLacunarity, Function2d in_pBaseFunction)
{
	const vfloat32 width = in_pArray->GetWidth();
	const vfloat32 height = in_pArray->GetHeight();

	for(vfloat32 y = 0; y < in_pArray->GetWidth(); ++y)
	for(vfloat32 x = 0; x < in_pArray->GetHeight(); ++x)
	{
		vfloat32 val= .0f;
		vfloat32 scale = 4.0f;

        // for each octave add noise
		//for(vfloat32 oct = 1; oct < 33; ++oct)
		//for(vfloat32 oct = 1; oct > 0; --oct)
		for(vuint oct = 1; oct <= in_nOctaves; ++oct)
		//vuint oct = 4;
		{
			const vfloat32 noise = in_pBaseFunction(x / (width-1) * oct, y / (height-1) * oct);
			//const vfloat32 noise = Noise(vfloat32((y/oct) * in_pArray->GetWidth() + (x/oct)));
			//const vfloat32 noise = Noise((vfloat32(y)/vfloat32(oct)) * vfloat32(in_pArray->GetWidth()) + (vfloat32(x)/vfloat32(oct)));
			//const vfloat32 noise = math::PseudoRandom((y/oct) * in_pArray->GetWidth() + (x/oct), .0f, 1.0f);
			val += noise * scale;
			scale *= in_fLacunarity;
		}

		in_pArray->Set(x, y, val);
	}
}

void VTerrainPart::SetVertexCount(vuint in_nWidth, vuint in_nHeight)
{
	m_nVertexCountHor = in_nWidth;
	m_nVertexCountVert = in_nHeight;

	const vuint vertexCount = GetVertexCount();
	const vuint indexCount = GetIndexCount();

	VResourceId res = VResourceManagerPtr()->CreateRandomNamedResource("terrain");

	VVertexFormat format(
		VVertexFormat::Coordinates | VVertexFormat::TexCoords | VVertexFormat::Normals, 
		vertexCount, 0);

	VVertexBuffer* pVertexBuffer = new VVertexBuffer(format);
	res->AddData(pVertexBuffer);
	m_hVertexBuffer = res->GetMutableData<VVertexBuffer>();

	VVertexFormat indexFormat(VVertexFormat::Indices, 0, indexCount);
	VVertexBuffer* pIndexBuffer = new VVertexBuffer(indexFormat);
	VResourceId indexRes = res->AddSubResource("indices");
	indexRes->AddData(pIndexBuffer);
	m_hIndexBuffer = indexRes->GetMutableData<VVertexBuffer>();

	GenerateVertices();
	GenerateIndices();
	GenerateNormals();

	VMeshDescription* pMeshDescription = new VMeshDescription(VVertexFormat(
		VVertexFormat::Coordinates | VVertexFormat::TexCoords | VVertexFormat::Indices | VVertexFormat::Normals, 
		vertexCount, 
		indexCount));
	pMeshDescription->SetGeometryType(VMeshDescription::TriangleStrip);
	pMeshDescription->SetCoordinateResource(res->GetQualifiedName());
	pMeshDescription->SetCoordinateFormat(format.GetCoordinateFormat());
	pMeshDescription->SetTexCoordFormat(0, format.GetTexCoordFormat(0));
	pMeshDescription->SetTexCoordResource(0, res->GetQualifiedName());
	pMeshDescription->SetIndexResource(indexRes->GetQualifiedName());
	pMeshDescription->SetIndexFormat(indexFormat.GetIndexFormat());
	pMeshDescription->SetNormalFormat(format.GetNormalFormat());
	pMeshDescription->SetNormalResource(res->GetQualifiedName());
	res->AddData(pMeshDescription);

	m_hMesh = res->GetData<IVMesh>();

	VArray2d<vfloat32> heightField;
	heightField.ResizeUninit(m_nVertexCountHor, m_nVertexCountVert);
	MakeFractal(&heightField, 4, .712f, Hill);
	ApplyHeightValues(heightField);	
}

void VTerrainPart::GenerateIndices()
{
	vuint num = 0;
	for(vuint y = 0; y < m_nVertexCountVert - 1; ++y)
	{
		for(vuint x = 0; x < m_nVertexCountHor; ++x)
		{
			m_hIndexBuffer->SetIndex(GetVertexNum(x, y), num);
			++num;

			m_hIndexBuffer->SetIndex(GetVertexNum(x, y+1), num);
			++num;
		}

		const vuint x = m_nVertexCountHor;

		// add degenerated triangle
		m_hIndexBuffer->SetIndex(GetVertexNum(x-1, y+1), num);
		++num;
		m_hIndexBuffer->SetIndex(GetVertexNum(0, y+1), num);
		++num;
	}

	V3D_ASSERT(num == GetIndexCount());
}

void VTerrainPart::GenerateVertices()
{
	const VVector2f  sizeXZ = m_XZMax - m_XZMin;
	const VVector3f scale = VVector3f(
		sizeXZ[0] / m_nVertexCountHor, 
		1, 
		sizeXZ[1] / m_nVertexCountVert);
	const VVector3f offset(m_XZMin[0], 0, m_XZMin[1]);
	//const VVector3f offset(-(m_nVertexCountHor/2.0f), 0, -(m_nVertexCountVert/2.0f));

	for(vuint x = 0; x < m_nVertexCountHor; ++x)
	for(vuint y = 0; y < m_nVertexCountVert; ++y)
	{
		const vuint vertexNum = GetVertexNum(x, y);
		const float h = math::PseudoRandom(GetVertexNum(x, y), .0f, .3f);
		VVector3f coord(x * scale[0], h * scale[1], y * scale[2]);
		coord += offset;
		m_hVertexBuffer->SetCoordinate(coord, vertexNum);

		VTexCoord2f texCoord;
		texCoord.u = float(x) / float(m_nVertexCountHor-1);
		texCoord.v = float(y) / float(m_nVertexCountVert-1);
		m_hVertexBuffer->SetTexCoord(0, vertexNum, texCoord);
	}
}

VVector3f VTerrainPart::GetVertexAt(vuint x, vuint y)
{
	VVertex3f coord = m_hVertexBuffer->GetCoordinate(GetVertexNum(x, y));
	return ToVector3f(coord.x, coord.y, coord.z);
}

namespace {
	VNormal3f ToNormal3f(const VVector3f& vec)
	{
		VNormal3f normal;
		normal.x = vec[0];
		normal.y = vec[1];
		normal.z = vec[2];
		return normal;
	}
}

void VTerrainPart::GenerateNormals()
{
	const vuint biggestX = m_nVertexCountHor - 1;
	const vuint biggestY = m_nVertexCountVert - 1;

	for(vuint x = 0; x < m_nVertexCountHor; ++x)
	{
		m_hVertexBuffer->SetNormal(VNormal3f(0, 1, 0), GetVertexNum(x, 0));
		m_hVertexBuffer->SetNormal(VNormal3f(0, 1, 0), GetVertexNum(x, biggestY));
	}

	for(vuint y = 0; y < m_nVertexCountVert; ++y)
	{
		m_hVertexBuffer->SetNormal(VNormal3f(0, 1, 0), GetVertexNum(0, y));
		m_hVertexBuffer->SetNormal(VNormal3f(0, 1, 0), GetVertexNum(biggestX, y));
	}

	for(vuint x = 1; x < biggestX; ++x)
	for(vuint y = 1; y < biggestY; ++y)
	{
        VVector3f xprev = GetVertexAt(x-1, y);
		VVector3f xnext = GetVertexAt(x+1, y);
		VVector3f yprev = GetVertexAt(x, y-1);
		VVector3f ynext = GetVertexAt(x, y+1);

		//VVector3f normal = xprev - xnext;
		VVector3f normal = Normalized(Cross(yprev - ynext, xprev - xnext));
		//VVector3f normal = Cross(xnext - xprev, yprev - ynext);
		m_hVertexBuffer->SetNormal(ToNormal3f(normal), GetVertexNum(x, y));
	}

	//for(vuint x = 0; x < m_nVertexCountHor; ++x)
	//for(vuint y = 0; y < m_nVertexCountVert; ++y)
	//{
	//	const vuint vertexNum = GetVertexNum(x, y);
	//	m_hVertexBuffer->SetNormal(VNormal3f(0, 1, 0), vertexNum);
	//}
}

resource::VResourceDataPtr<graphics::VVertexBuffer> VTerrainPart::GetVertexBuffer()
{
	return m_hVertexBuffer;
}

resource::VResourceDataPtr<graphics::VVertexBuffer> VTerrainPart::GetIndexBuffer()
{
	return m_hIndexBuffer;
}

namespace {
	entity::VPartParser<VTerrainPart> parser;
}



//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
