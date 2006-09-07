/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VGRAPHICSPRITE_04_06_19_H
#define V3D_VGRAPHICSPRITE_04_06_19_H
//-----------------------------------------------------------------------------
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
//-----------------------------------------------------------------------------

/**
 * @author ins
 * @version 1.0
 */

class VGraphicSprite
{

public:

	struct VGraphicRect
	{
		vfloat32 x1,y1;
		vfloat32 x2,y2;	
	};

	struct VGraphicTexCoordRect
	{
		vfloat32 uv[8]; 

	};

	struct VGraphicFrame
	{
		vuint iID;
		VGraphicRect rect;
		VGraphicTexCoordRect texRect;
	};

	VGraphicSprite(VStringParam in_sTextureFile, IVDevice& in_Device);
	~VGraphicSprite();

	virtual void Render(vuint in_iFrameNum, vfloat32 x, vfloat32 y);
	virtual void Render(vuint in_iFrameNum, vfloat32 x, vfloat32 y, vfloat32 z);
	virtual void SetFrame(vuint in_iID, VGraphicFrame in_Frame);
    
	//creates a new frame
	virtual void AddFrame(VGraphicFrame in_Frame);

protected:

	virtual void CreateTexture(VStringParam in_sTextureFile);

	void CreateMesh(vuint in_iFrameID, vfloat32 x, vfloat32 y, vfloat32 z);
	void CreateDefaultMesh();

	VMaterialDescription m_TextureDescription;
	VMeshDescription m_MeshDescription;
	IVDevice& m_Device;

	IVDevice::Buffer* m_pVertexDeviceBuffer;
	IVDevice::Buffer* m_pTexCoordDeviceBuffer;

	IVDevice::BufferHandle m_VertexHandle;
	IVDevice::BufferHandle m_TexHandle;
	IVDevice::MeshHandle m_MeshHandle;


	std::vector<VGraphicFrame> m_FrameList;


};

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------

#endif // V3D_VGRAPHICSPRITE_04_06_19_H
