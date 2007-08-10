#ifndef V3D_VSKYPLANE_2007_08_10_H
#define V3D_VSKYPLANE_2007_08_10_H

#include <V3d/Core.h>
#include <V3d/Graphics.h>
#include <gmtl/gmtl.h>
#include <V3d/Scene/VMeshPartBase.h>
#include <V3d/Entity/IVPartParser.h>
#include <V3d/Core/VTypeInfo.h>
#include <V3d/Messaging/VMessageInterpreter.h>
#include <V3d/Scene/Shapes/VSkyDomeGenerator.h>

namespace v3d { namespace scene {

/**
 * A procedural sky part for rendering. Needs shader support
 * @author ins
 */

class VSkyPart : public v3d::scene::VMeshPartBase
{
public:
	VSkyPart(
		std::string in_Mode = "Plane",
		vuint in_Sides = 40,
		vuint in_Slices = 40,
		vuint in_DivSteps = 100,
		vfloat32 in_fRadius = 20,
		vfloat32 in_fWidth = 8000,
		vfloat32 in_fHeight = 100,
		vbool in_ShowAsLine = false);

	virtual ~VSkyPart();

	void SetColor(const v3d::graphics::VColor4f& in_Color);
	void SendGeometry(v3d::graphics::IVDevice& in_Device) const;

	//dome getters / setters
	void SetRadius(const float& in_fRadius);
	void SetSlices(const vuint& in_Slices);
	void SetSides(const vuint& in_Sides);

	vfloat32 GetRadius() const;
	vuint GetSlices() const;
	vuint GetSides() const;

	//plane getters / setters
	
	void SetDivSteps(const vuint& in_DivSteps);
	void SetWidth(const vfloat32& in_fWidth);
	void SetHeight(const vfloat32& in_fHeight);
	
	vuint GetDivSteps() const;
	vfloat32 GetWidth() const;
	vfloat32 GetHeight() const;
	
	vbool SetShowAsLine(const vbool& in_ShowAsLine);
	vbool GetShowAsLine() const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:

    void BuildResources();
	VSkyDomeGenerator* m_pSkyDome;
	resource::VResourceDataPtr<const graphics::IVMesh> m_hMesh;
	VSkyDomeGenerator::Mode m_Mode;

	vuint m_Sides;
	vuint m_Slices;
	vuint m_DivSteps;

	vfloat32 m_fRadius;
	vfloat32 m_fWidth;
	vfloat32 m_fHeight;
	vbool m_ShowAsLine;

	std::string m_ModeString;

	std::string GetMode() const;
	void SetMode(const std::string& in_Mode);

protected:
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);
};

}
}
V3D_TYPEINFO_WITHPARENT(v3d::scene::VSkyPart, v3d::scene::IVShapePart);

#endif //V3D_VSKYPLANE_2007_08_10_H
