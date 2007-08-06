#ifndef SKYPLANE_H
#define SKYPLANE_H
#include <V3d/Core.h>
#include <V3d/Graphics.h>
#include <gmtl/gmtl.h>
#include <V3d/Scene/VMeshPartBase.h>
#include <V3d/Entity/IVPartParser.h>
#include <V3d/Core/VTypeInfo.h>
#include <V3d/Messaging/VMessageInterpreter.h>

namespace v3d { namespace scene {

class VSkyDomeGenerator
{
public:
	typedef gmtl::Vec3f V3f;
	typedef gmtl::Vec4f Col4f;
    typedef unsigned int uint;

	VSkyDomeGenerator();
	~VSkyDomeGenerator();

	float* GetVertexBuffer();
	uint* GetIndexBuffer();
	float* GetTextureBuffer();
	uint GetIndexCount();
	uint GetVertexCount();

	void SetRadius(float in_fRadius);
	void SetSlices(uint in_Slices);
	void SetSides(uint in_Sides);

	vfloat32 GetRadius() const;
	vuint GetSlices() const;
	vuint GetSides() const;

private:
	void Generate();
	void GenerateVertices();

	uint* m_pIndexBuffer;
	float* m_pVertexBuffer;
	float* m_pTexCoords;
	Col4f* m_pColorBuffer;

	float m_fRadius;
	vuint m_nSides;
	vuint m_nSlices;
	uint m_nIndexCount;
	uint m_nVertexCount;

};

class VSkyPart : public v3d::scene::VMeshPartBase
{
public:
    VSkyPart();
	VSkyPart(const v3d::graphics::VColor4f& in_Color);
	virtual ~VSkyPart();

	void SetColor(const v3d::graphics::VColor4f& in_Color);
	void SendGeometry(v3d::graphics::IVDevice& in_Device) const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:

    void BuildResources();
	VSkyDomeGenerator* m_pSkyDome;
	resource::VResourceDataPtr<const graphics::IVMesh> m_hMesh;

protected:
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);
};

}
}
V3D_TYPEINFO_WITHPARENT(v3d::scene::VSkyPart, v3d::scene::IVShapePart);

#endif
