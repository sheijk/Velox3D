#include <v3dlib/Graphics/Renderers/Sky/VSkyDome.h>
#include <v3d/Math/VMatrixOps.h>
#include <v3d/Image.h>
//-----------------------------------------------------------------------------

using namespace v3d;
using namespace v3d::image;
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {

VVertexDataLayout VSkyDome::SkyVertex::layout;
       

VSkyDome::VSkyDome( v3d::graphics::IVDevice& in_Device, 
 		    vfloat32 in_fRadius,
		    vfloat32 in_fScale,
			vuint in_nDetail,
			VStringParam in_strImage )
	: m_fRadius(in_fRadius),
	  m_fScale(in_fScale),
	  m_HalfSphere(in_nDetail, in_nDetail, 1.0f, 0.0f),
	  m_strImage(in_strImage)
{
	//V3D_ASSERT(in_fRadius > 0.0f)
	m_HalfSphere.GenerateCoordinates();
	m_HalfSphere.GenerateTexCoords();

	InverseIndexBuffer();
	CreateMesh(in_Device);
}

VSkyDome::~VSkyDome()
{
}

void VSkyDome::InverseIndexBuffer()
{

	vuint nSize = m_HalfSphere.GetIndexBuffer().GetSize();
	vuint* pTemp = new vuint[nSize];
	vuint* pBuffer = m_HalfSphere.GetIndexBuffer().GetDataAddress();
	vuint nIndex = 0;

	for (int i=0; i<nSize; ++i)
		pTemp[i] = pBuffer[nSize-1-i];

	for (int i=0; i<nSize; ++i)
		pBuffer[i] = pTemp[i];

	delete pTemp;
}

void VSkyDome::CreateMesh(IVDevice& in_Device)
{
	// Scale halfsphere with m_fRadius
	ForEachVertex( m_HalfSphere.GetVertexBuffer(), ScaleVertex<SkyVertex>(m_fRadius,
															   m_fRadius*m_fScale,
															   m_fRadius) );

	IVImageFactory* pFactory = QueryObject<IVImageFactory>("image.service");
	IVImageFactory::ImagePtr myImage = pFactory->CreateImage(m_strImage);


	VMaterialDescription::TextureRef* pTexRef =
		new VMaterialDescription::TextureRef();

	IVDevice::BufferHandle hTextureBuffer = in_Device.CreateBuffer(
		IVDevice::Texture,
		myImage->pData,
		IVDevice::Buffer::DropData
		);

	pTexRef->nWidth = myImage->iWidth;
	pTexRef->nHeight = myImage->iHeight;
	pTexRef->hData = hTextureBuffer;

	m_MaterialDescription.frontPolyMode = VMaterialDescription::PolygonMode::Line;
	m_MaterialDescription.backPolyMode = VMaterialDescription::PolygonMode::Line;
	//m_MaterialDescription.frontPolyMode = VMaterialDescription::PolygonMode::Point;
	//m_MaterialDescription.backPolyMode = VMaterialDescription::PolygonMode::Point;
	//m_MaterialDescription.frontPolyMode = VMaterialDescription::PolygonMode::Filled;
	//m_MaterialDescription.backPolyMode = VMaterialDescription::PolygonMode::Filled;
	m_MaterialDescription.AddTexture( pTexRef );

	VMeshDescription meshDesc = 
		BuildMeshDescription(in_Device,
							 m_HalfSphere.GetVertexBuffer().GetDataAddress(),
							 m_HalfSphere.GetVertexBuffer().GetSize(),
							 m_HalfSphere.GetIndexBuffer().GetDataAddress(),
							 m_HalfSphere.GetIndexBuffer().GetSize() );
	meshDesc.geometryType = VMeshDescription::TriangleStrip;

	m_pMesh = in_Device.CreateMesh( meshDesc, m_MaterialDescription );
}



IVDevice::MeshHandle VSkyDome::GetMesh()
{
	return m_pMesh;
}

} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
