#include <V3dLib/Graphics/Geometry/VGeometryUtil.h>
#include <v3dlib/Graphics/Misc/MiscUtils.h>
#include <v3dLib/Graphics/Image/VGraphicSprite.h>
#include <V3d/Graphics/IVMesh.h>

#include <stdlib.h>

//-----------------------------------------------------------------------------
namespace v3d{
namespace graphics{
//-----------------------------------------------------------------------------

VGraphicSprite::VGraphicSprite(VStringParam in_sTextureFile,
							   IVDevice& in_Device)
							   : m_Device(in_Device)
{
	CreateTexture(in_sTextureFile);
	CreateDefaultMesh();
}
VGraphicSprite::~VGraphicSprite()
{
}



void VGraphicSprite::CreateTexture(VStringParam in_sTextureFile)
{
	m_TextureDescription = BuildTextureMaterial(&m_Device, in_sTextureFile);
}

void VGraphicSprite::Render(vuint in_iFrameNum, vfloat32 x, vfloat32 y, vfloat32 z)
{
	if(m_FrameList.size() <= in_iFrameNum)
		return;

	CreateMesh(in_iFrameNum, x,y,z);

	ApplyMaterial(m_Device, &m_MeshHandle->GetMaterial(0));
	m_Device.RenderMesh(m_MeshHandle);
}

void VGraphicSprite::Render(vuint in_iFrameNum, vfloat32 x, vfloat32 y)
{
	Render(in_iFrameNum, x, y, 0.0f);
}

void VGraphicSprite::SetFrame(vuint in_iID, VGraphicFrame in_Frame)
{
	if(m_FrameList.size() >= in_iID)
		return;

	m_FrameList[in_iID] = in_Frame;
}

void VGraphicSprite::AddFrame(VGraphicFrame in_Frame)
{
	in_Frame.iID = (vuint)m_FrameList.size() +1;

	m_FrameList.push_back(in_Frame);
}

void VGraphicSprite::CreateMesh(vuint in_iFrameID, vfloat32 x, vfloat32 y, vfloat32 z)
{
	// get the frame

	VGraphicFrame* theFrame = &m_FrameList[in_iFrameID];

	vfloat32* tex = new vfloat32[8];

	for(int i = 0; i < 8; i++)
	{
		tex[i] =  theFrame->texRect.uv[i];
	}


	IVDevice::Buffer* buf = new IVDevice::Buffer
		(reinterpret_cast<vbyte*>(tex),
		sizeof(vfloat32)*8);


	
	m_Device.OverwriteBuffer(m_TexHandle, 0, 8*sizeof(vfloat32), buf->GetDataAddress());

	// create vertices
	vfloat32* vertices = new vfloat32[12];

	//swap order to x1,y2 to lower left

	vfloat32 lx = std::min(theFrame->rect.x1,theFrame->rect.x2);
	vfloat32 ly = std::min(theFrame->rect.y1,theFrame->rect.y2);

	vfloat32 rx = std::max(theFrame->rect.x1,theFrame->rect.x2);
	vfloat32 ry = std::max(theFrame->rect.y1,theFrame->rect.y2);

	vertices[0] = x;
	vertices[1] = y;
	vertices[2] = z;

	/*vertices[3] = theFrame->rect.x2-theFrame->rect.x1 + x;
	vertices[4] = y;
	vertices[5] = z;*/

	vertices[3] = rx-lx + x;
	vertices[4] = y;
	vertices[5] = z;


	vertices[9] = x;
	//vertices[10] = theFrame->rect.y2 - theFrame->rect.y1 + y;
	vertices[10] = ry - ly + y;
	vertices[11] = z;

	/*vertices[6] = theFrame->rect.x2 - theFrame->rect.x1 + x;
	vertices[7] = theFrame->rect.y2 - theFrame->rect.y1 + y;*/
	vertices[6] = rx - lx + x;
	vertices[7] = ry - ly + y;
	vertices[8] = z;

	IVDevice::Buffer* vertBuf = new IVDevice::Buffer
		(reinterpret_cast<vbyte*>(vertices),
		sizeof(vfloat32)*12);
	
	m_Device.OverwriteBuffer(m_VertexHandle, 0, 12*sizeof(vfloat32), vertBuf->GetDataAddress());

	delete vertBuf;
	delete buf;
}

void VGraphicSprite::CreateDefaultMesh()
{

	vfloat32* vertices = new vfloat32[12];
    vfloat32* texCoords = new vfloat32[4*2];

	for(int i=0; i<4; i++)
	{
		vertices[i*3] = 0.0f;
		vertices[i*3+1] = 0.0f;
		vertices[i*3+2] = 0.0f;

		texCoords[i*2] = 0.0f;
		texCoords[i*2+1] = 0.0f;
	}

	m_pVertexDeviceBuffer = new IVDevice::Buffer
		(reinterpret_cast<vbyte*>(vertices),
		4 * sizeof(vfloat32));

	m_pTexCoordDeviceBuffer = new IVDevice::Buffer
		(reinterpret_cast<vbyte*>(texCoords),
		8 * sizeof(vfloat32));

	m_VertexHandle =  m_Device.CreateBuffer(
		IVDevice::VertexBuffer,
		m_pVertexDeviceBuffer,
		IVDevice::Buffer::CopyData);

	m_TexHandle =  m_Device.CreateBuffer(
		IVDevice::VertexBuffer,
		m_pTexCoordDeviceBuffer,
		IVDevice::Buffer::CopyData);

	m_MeshDescription.SetCoordinateData(m_VertexHandle, VDataFormat(0, 12, 3));
	//m_MeshDescription.triangleVertices = VMeshDescription::ByteDataRef(
 //       m_VertexHandle, 0, 12, 3);

	m_MeshDescription.SetTexCoordData(0, m_TexHandle, VDataFormat(0, 4, 2));
	//m_MeshDescription.triangleTexCoords = VMeshDescription::ByteDataRef(
	//	m_TexHandle, 0, 4, 2);

	m_MeshDescription.SetGeometryType(VMeshDescription::Quads);
	//m_MeshDescription.geometryType = VMeshDescription::Quads;

	m_MeshHandle = m_Device.CreateMesh(m_MeshDescription, m_TextureDescription);
}

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------
