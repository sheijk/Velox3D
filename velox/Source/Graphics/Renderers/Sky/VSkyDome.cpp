#include <v3dlib/Graphics/Renderers/Sky/VSkyDome.h>
#include <v3d/Math/VMatrixOps.h>
#include <v3d/Image.h>
#include <v3dLib/Math.h>
#include <v3d/Core/MemManager.h>
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
	  m_nDetail(in_nDetail),
	  m_HalfSphere(in_nDetail, in_nDetail, 1.0f, 0.0f),
	  m_strImage(in_strImage),
	  //m_Colorizer( 1.0f, 2.2, 2.0f)
	  //m_Colorizer( 1.40f, 1.5f, 2.0f)
	  m_Colorizer( .8f, 0.7f, 3.0f)
{
	m_HalfSphere.GenerateCoordinates();

	Texturize();
	Colorize();
	InverseIndexBuffer();

	CreateTextureRef(in_Device);
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

	for (vuint i=0; i<nSize; ++i)
		pTemp[i] = pBuffer[nSize-1-i];

	for (vuint i=0; i<nSize; ++i)
		pBuffer[i] = pTemp[i];

	delete pTemp;
}

vuint VSkyDome::GetVertexNum(vuint sector, vuint ring)
{
	return ring * m_nDetail + sector;
}

struct SphereCoords
{
	vfloat32 fTheta;
	vfloat32 fPhi;
	vfloat32 fRadius;
};

inline SphereCoords CarthesicToSpherical( const VVertex3f& in_vec )
{
	SphereCoords coords;

	coords.fRadius= sqrt( in_vec.x*in_vec.x + in_vec.y*in_vec.y + in_vec.z*in_vec.z );
	coords.fPhi = atan2( in_vec.z , in_vec.x );
	coords.fTheta = acos( in_vec.y / coords.fRadius);

	if ( coords.fPhi < 0.0f )
		coords.fPhi = coords.fPhi +  2*math::Pi();

	if ( (in_vec.x == 0.0f) && (in_vec.z == 0.0f) )
		coords.fPhi = 0.0f;
	
	//vout << "(" << in_vec.x << "|" << in_vec.y << "|" << in_vec.z << ")  (" << coords.fTheta << "|" << coords.fPhi << "|" << coords.fRadius << ")" << vendl;

	return coords;    
}

void VSkyDome::Colorize()
{
	SphereCoords coords;

	for(vuint ring = 0; ring < m_nDetail; ++ring)
		for(vuint sector = 0; sector < m_nDetail; ++sector)
		{
			coords =CarthesicToSpherical(
				m_HalfSphere.GetVertexBuffer()[GetVertexNum(sector,ring)].position );
			
			m_HalfSphere.GetVertexBuffer()[GetVertexNum(sector,ring)].color =
				m_Colorizer.GetColor(coords.fTheta,coords.fPhi);
		}
}

void VSkyDome::Texturize()
{
	const vfloat32 deltaU =  1.0f / m_nDetail;
	const vfloat32 deltaV = 0.5f / m_nDetail;

	// for each ring
	for(vuint ring = 0; ring < m_nDetail; ++ring)
		for(vuint sector = 0; sector < m_nDetail; ++sector)
		{
			SkyVertex& vertex =
				m_HalfSphere.GetVertexBuffer()[GetVertexNum(sector, ring)];

			vertex.texCoords.u = deltaU * sector;
			vertex.texCoords.v = deltaV * ring;
		}
}

void VSkyDome::CreateTextureRef(IVDevice& in_Device)
{
	IVImageFactory* pFactory = QueryObject<IVImageFactory>("image.service");
	IVImageFactory::ImagePtr myImage = pFactory->CreateImage(m_strImage);

	m_pTexRef = new VMaterialDescription::TextureRef();

	IVDevice::BufferHandle hTextureBuffer = in_Device.CreateBuffer(
		IVDevice::Texture,
		myImage->pData,
		IVDevice::Buffer::DropData
		);

	m_pTexRef->nWidth = myImage->iWidth;
	m_pTexRef->nHeight = myImage->iHeight;
	m_pTexRef->hData = hTextureBuffer;
	
	//m_pTexRef->minificationFilter = VMaterialDescription::FilterLinear;
	//m_pTexRef->magnificationFilter = VMaterialDescription::FilterLinear;
	//m_pTexRef->wrapTexCoordU = VMaterialDescription::TextureRepeat;
	//m_pTexRef->wrapTexCoordV = VMaterialDescription::TextureClamp;
}

void VSkyDome::CreateMesh(IVDevice& in_Device)
{
	// Scale halfsphere with m_fRadius
	ForEachVertex( m_HalfSphere.GetVertexBuffer(), ScaleVertex<SkyVertex>(m_fRadius,
															   m_fRadius,
															   m_fRadius) );

	// Swap halfsphere to y z axis
	ForEachVertex( m_HalfSphere.GetVertexBuffer(), SwitchYZ<SkyVertex>);
	
	m_MaterialDescription.frontPolyMode = VMaterialDescription::PolygonMode::Filled;
	m_MaterialDescription.backPolyMode = VMaterialDescription::PolygonMode::Filled;
	
	//m_MaterialDescription.depthTestFunction = VMaterialDescription::DepthTest::DepthNever;
	
	m_MaterialDescription.sourceBlendFactor = VMaterialDescription::BlendFactor::BlendSourceAlpha;
	m_MaterialDescription.destBlendFactor = VMaterialDescription::BlendFactor::BlendOneMinusSourceAlpha;
	m_MaterialDescription.enableBlending = true;
    	
	m_MaterialDescription.AddTexture( m_pTexRef );

	VMeshDescription meshDesc = 
	BuildMeshDescription( in_Device,
		m_HalfSphere.GetVertexBuffer().GetDataAddress(),
		m_HalfSphere.GetVertexBuffer().GetSize(),
		m_HalfSphere.GetIndexBuffer().GetDataAddress(),
		m_HalfSphere.GetIndexBuffer().GetSize() );

	meshDesc.SetGeometryType(VMeshDescription::TriangleStrip);
	//meshDesc.geometryType = VMeshDescription::TriangleStrip;

	m_pMesh = in_Device.CreateMesh( meshDesc, m_MaterialDescription );
}



IVDevice::MeshHandle VSkyDome::GetMesh()
{
	return m_pMesh;
}

} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
