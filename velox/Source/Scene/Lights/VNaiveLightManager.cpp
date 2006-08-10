#include <V3d/Scene/Lights/VNaiveLightManager.h>
//-----------------------------------------------------------------------------

#include <V3d/Graphics/IVDevice.h>
#include <V3d/Math/TransformationOps.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <V3d/Graphics/Geometry/Conversions.h>
#include <V3d/Graphics/VLight.h>
#include <V3d/Scene/Lights/VLightPart.h>
#include <V3d/OpenGL.h>
#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d::graphics;
using namespace v3d::entity;

namespace {
	void ApplyGLLightStates(IVDevice& in_Device)
	{
		in_Device.SetMatrix(IVDevice::ModelMatrix, math::IdentityMatrix());

		for(vuint lightNum = 0; lightNum < in_Device.MaxActiveLight(); ++lightNum)
		{
			const VLight* pLight = in_Device.GetLight(lightNum);
			const GLenum lightGL = GL_LIGHT0 + lightNum;

			if( pLight != NULL )
			{
				glEnable(lightGL);

				const VColor4f ambient = pLight->GetAmbientColor();
				const VColor4f diffuse = pLight->GetDiffuseColor();
				const VColor4f specular = pLight->GetSpecularColor();
				//static vfloat32 pos[4] = {0, 10, 0, 1 };
				const VVector4f position = ToVector4f(
					pLight->GetPosition(), pLight->GetW());

				glLightfv(lightGL, GL_POSITION, (float*)&position);
				//glLightfv(lightGL, GL_POSITION, pos);
				glLightfv(lightGL, GL_AMBIENT, (float*)&ambient);
				glLightfv(lightGL, GL_DIFFUSE, (float*)&diffuse);
				glLightfv(lightGL, GL_SPECULAR, (float*)&specular);

				glLightf(lightGL, GL_CONSTANT_ATTENUATION, 1.0f);
				glLightf(lightGL, GL_LINEAR_ATTENUATION, .1f);
				glLightf(lightGL, GL_QUADRATIC_ATTENUATION, .0f);
			}
			else
			{
				glDisable(lightGL);
			}
		}
	}
}

void VNaiveLightManager::Add(VLightPart* in_pLight)
{
	m_Lights.insert(in_pLight);
}

void VNaiveLightManager::Remove(VLightPart* in_pLight)
{
	m_Lights.erase(in_pLight);
}

void VNaiveLightManager::ApplyLights(IVDevice* in_pDevice, IVShapePart* in_pShape)
{
	V3D_ASSERT(in_pDevice);

	if( in_pDevice != NULL )
	{
		// clear previous lights
		for(vuint lightNum = 0; lightNum < in_pDevice->MaxActiveLight(); ++lightNum)
			in_pDevice->ApplyLight(lightNum, NULL);

		// set new lights
		vuint lightNum = 0;
		for(LightSet::iterator light = m_Lights.begin();
			light != m_Lights.end();
			++light, ++lightNum)
		{
			in_pDevice->ApplyLight(lightNum, &(*light)->Light());
		}

		// apply states for fixed function pipeline (no shader support, yet)
		ApplyGLLightStates(*in_pDevice);
	}
}

void VNaiveLightManager::Activate()
{
}

void VNaiveLightManager::Deactivate()
{
}


V3D_REGISTER_PART_PARSER(VNaiveLightManager);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
