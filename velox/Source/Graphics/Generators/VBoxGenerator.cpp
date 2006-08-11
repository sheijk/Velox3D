#include <V3d/Graphics/Generators/VBoxGenerator.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics/Geometry/VTexCoord2f.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

VBoxGenerator::VBoxGenerator(vfloat32 in_fSize)
{
	m_fWidth = in_fSize;
	m_fHeight = in_fSize;
	m_fDepth = in_fSize;
}

VBoxGenerator::VBoxGenerator(
	vfloat32 in_fWidth, vfloat32 in_fHeight, vfloat32 in_fDepth)
{
	m_fWidth = in_fWidth;
	m_fHeight = in_fHeight;
	m_fDepth = in_fDepth;
}

/**
 * d'tor
 */
VBoxGenerator::~VBoxGenerator()
{
}

VVertexBuffer* VBoxGenerator::CreateVertexBuffer() const
{
	std::auto_ptr<VVertexBuffer> pVB(new VVertexBuffer(VVertexFormat(
		VVertexFormat::Coordinates | VVertexFormat::TexCoords, 6*6, 0)));

	vfloat32 fHeightHalf = m_fHeight / 2.0f;
	vfloat32 fWidthHalf = m_fWidth / 2.0f;
	vfloat32 fDepthHalf = m_fDepth / 2.0f;

	//front face
	pVB->SetCoordinate(VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf), 0);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf), 1);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf), 2);

	pVB->SetCoordinate(VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf), 3);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf), 4);
	pVB->SetCoordinate(VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf), 5);

	//top face
	pVB->SetCoordinate(VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf), 6);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf), 7);
	pVB->SetCoordinate(VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf), 8);

	pVB->SetCoordinate(VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf), 9);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf), 10);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf), 11);


	//back face
	pVB->SetCoordinate(VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf), 12);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf), 13);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf), 14);

	pVB->SetCoordinate(VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf), 15);
	pVB->SetCoordinate(VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf), 16);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf), 17);

	//bottom face
	pVB->SetCoordinate(VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf), 18);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf), 19);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf), 20);

	pVB->SetCoordinate(VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf), 21);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf), 22);
	pVB->SetCoordinate(VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf), 23);

	//right face
	pVB->SetCoordinate(VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf), 24);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf), 25);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf), 26);


	pVB->SetCoordinate(VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf), 27);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf), 28);
	pVB->SetCoordinate(VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf), 29);


	//left face
	pVB->SetCoordinate(VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf), 30);
	pVB->SetCoordinate(VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf), 31);
	pVB->SetCoordinate(VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf), 32);

	pVB->SetCoordinate(VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf), 33);
	pVB->SetCoordinate(VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf), 34);
	pVB->SetCoordinate(VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf), 35);

	//front face
	pVB->SetTexCoord(0, 0, VTexCoord2f(0.0f, 0.0f));
	pVB->SetTexCoord(0, 1, VTexCoord2f(1.0f, 0.0f));
	pVB->SetTexCoord(0, 2, VTexCoord2f(1.0f, 1.0f));

	pVB->SetTexCoord(0, 3, VTexCoord2f(0.0f, 0.0f));
	pVB->SetTexCoord(0, 4, VTexCoord2f(1.0f, 1.0f));
	pVB->SetTexCoord(0, 5, VTexCoord2f(0.0f, 1.0f));

	//top face
	pVB->SetTexCoord(0, 6, VTexCoord2f(0.0f, 0.0f));
	pVB->SetTexCoord(0, 7, VTexCoord2f(1.0f, 1.0f));
	pVB->SetTexCoord(0, 8, VTexCoord2f(0.0f, 1.0f));

	pVB->SetTexCoord(0, 9, VTexCoord2f(0.0f, 0.0f));
	pVB->SetTexCoord(0, 10, VTexCoord2f(1.0f, 0.0f));
	pVB->SetTexCoord(0, 11, VTexCoord2f(1.0f, 1.0f));

	//back face

	pVB->SetTexCoord(0, 12, VTexCoord2f(1.0f, 0.0f));
	pVB->SetTexCoord(0, 13, VTexCoord2f(0.0f, 1.0f));
	pVB->SetTexCoord(0, 14, VTexCoord2f(0.0f, 0.0f));

	pVB->SetTexCoord(0, 15, VTexCoord2f(1.0f, 0.0f));
	pVB->SetTexCoord(0, 16, VTexCoord2f(1.0f, 1.0f));
	pVB->SetTexCoord(0, 17, VTexCoord2f(0.0f, 1.0f));

	//bottom face
	pVB->SetTexCoord(0, 18, VTexCoord2f(1.0f, 0.0f));
	pVB->SetTexCoord(0, 19, VTexCoord2f(0.0f, 0.0f));
	pVB->SetTexCoord(0, 20, VTexCoord2f(0.0f, 1.0f));

	pVB->SetTexCoord(0, 21, VTexCoord2f(1.0f, 0.0f));
	pVB->SetTexCoord(0, 22, VTexCoord2f(0.0f, 1.0f));
	pVB->SetTexCoord(0, 23, VTexCoord2f(1.0f, 1.0f));

	//right face
	pVB->SetTexCoord(0, 24, VTexCoord2f(0.0f, 0.0f));
	pVB->SetTexCoord(0, 25, VTexCoord2f(1.0f, 1.0f));
	pVB->SetTexCoord(0, 26, VTexCoord2f(0.0f, 1.0f));

	pVB->SetTexCoord(0, 27, VTexCoord2f(0.0f, 0.0f));
	pVB->SetTexCoord(0, 28, VTexCoord2f(1.0f, 0.0f));
	pVB->SetTexCoord(0, 29, VTexCoord2f(1.0f, 1.0f));

	//bottom face
	pVB->SetTexCoord(0, 30, VTexCoord2f(0.0f, 0.0f));
	pVB->SetTexCoord(0, 31, VTexCoord2f(1.0f, 1.0f));
	pVB->SetTexCoord(0, 32, VTexCoord2f(0.0f, 1.0f));

	pVB->SetTexCoord(0, 33, VTexCoord2f(0.0f, 0.0f));
	pVB->SetTexCoord(0, 34, VTexCoord2f(1.0f, 0.0f));
	pVB->SetTexCoord(0, 35, VTexCoord2f(1.0f, 1.0f));

	return pVB.release();
}

VVertexBuffer* VBoxGenerator::CreateIndexBuffer() const
{
	return 0;
}

VMeshDescription::GeometryType VBoxGenerator::GetGeometryType() const
{
	return VMeshDescription::Triangles;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
