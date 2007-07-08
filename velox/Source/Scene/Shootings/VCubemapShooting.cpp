/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Scene/Shootings/VCubemapShooting.h>
//-----------------------------------------------------------------------------

#include <V3d/Scene/IVSceneManagerPart.h>

#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Messaging/VMessageInterpreter.h>

#include <V3d/Resource.h>
#include <V3d/Resource/ResourceExceptions.h>

#include <V3d/Math/TransformationOps.h>

#include <V3d/Graphics/GraphicsExceptions.h>
#include <V3d/Graphics/IVGraphicsService.h>
#include <V3d/Graphics/Misc/VCamera.h>
#include "../../Graphics/OpenGL/Textures/VCubeMapTexture.h"
#include "../../Graphics/OpenGL/Context/VFrameBufferObjectContext.h"

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {

class VCubeMapContext : public IVRenderContext
{
public:
	VCubeMapContext(
		VCubeMapTexture* cubemapTexture,
		IVRenderContext* parentContext )
		//const VDisplaySettings& displaySettings, 
		//m_FBO(displaySettings, parentContext)
	{
		V3D_ASSERT( cubemapTexture != NULL );
		m_pCubeMapTexture = cubemapTexture;
		m_pParentContext = parentContext;
		m_ActiveSide = PosX;

		m_nSize = cubemapTexture->GetSize();

		m_DisplaySettings.SetSize( m_nSize, m_nSize );
		m_DisplaySettings.SetDepthBits( 24 );
		m_DisplaySettings.SetBitsPerPixel( 0 );

		cubemapTexture->Bind();

		glGenFramebuffersEXT( 1, &m_FBOId );
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_FBOId );

		glFramebufferTexture2DEXT(
			GL_FRAMEBUFFER_EXT,
			GL_COLOR_ATTACHMENT0_EXT,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			cubemapTexture->GetTextureId(),
			0 );

		glGenRenderbuffersEXT( 1, &m_DepthBufferId );
		glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, m_DepthBufferId );
		glRenderbufferStorageEXT(
			GL_RENDERBUFFER_EXT,
			GL_DEPTH_COMPONENT24,
			m_nSize, m_nSize );
		glFramebufferRenderbufferEXT(
			GL_FRAMEBUFFER_EXT,
			GL_DEPTH_ATTACHMENT_EXT,
			GL_RENDERBUFFER_EXT,
			m_DepthBufferId );

		const GLuint fboStatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		if( fboStatus != GL_FRAMEBUFFER_COMPLETE_EXT )
		{
			V3D_THROWMSG( VGraphicException, "invalid fbo status: " << fboStatus );
		}

		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
	}

	enum Side { PosX, NegX, PosY, NegY, PosZ, NegZ };

	void SetActiveSide(Side side)
	{
		m_ActiveSide = side;
	}

	virtual void MakeCurrent()
	{
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_FBOId );
		glViewport( 0, 0, m_nSize, m_nSize );

		static GLuint targetForSide[6] = {
			GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};

		glFramebufferTexture2DEXT(
			GL_FRAMEBUFFER_EXT,
			GL_COLOR_ATTACHMENT0_EXT,
			targetForSide[int(m_ActiveSide)],
			m_pCubeMapTexture->GetTextureId(),
			0 );
	}

	virtual void SwapBuffers()
	{
		glBindTexture( GL_TEXTURE_CUBE_MAP, m_pCubeMapTexture->GetTextureId() );
		glGenerateMipmapEXT( GL_TEXTURE_CUBE_MAP );
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
		//glViewport( 0, 0, m_pParentContext->)
	}

	virtual VDisplaySettings* GetDisplaySettings()
	{
		return &m_DisplaySettings;
	}

	/** Create a Offscreen Context */
	virtual IVRenderContext* CreateOffscreenContext(const VDisplaySettings* in_pDisplaySettings)
	{
		return m_pParentContext->CreateOffscreenContext(in_pDisplaySettings);
	}

private:
	Side m_ActiveSide;
	vuint m_nSize;
	GLuint m_FBOId;
	GLuint m_DepthBufferId;
	VCubeMapTexture* m_pCubeMapTexture;
	VDisplaySettings m_DisplaySettings;
	IVRenderContext* m_pParentContext;

	//graphics::VFrameBufferObjectContext m_FBO;
};

VCubeMapContext::Side operator++(VCubeMapContext::Side& s) 
{
	s = VCubeMapContext::Side( int(s) + 1 );
	return s;
}

}} // namespace v3d::graphics
V3D_TYPEINFO_WITHPARENT(v3d::graphics::VCubeMapContext, v3d::graphics::IVRenderContext);

namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; //  auto indent
using namespace resource;
using graphics::VCubeMapTexture;

/**
 * standard c'tor
 */
VCubemapShooting::VCubemapShooting() :
	m_pScene( RegisterTo() ),
	m_pParentShooting( RegisterTo() )
{
}

/**
 * d'tor
 */
VCubemapShooting::~VCubemapShooting()
{
}

void VCubemapShooting::UpdateAndCull()
{
}

void VCubemapShooting::OnActivate()
{
	m_pParentShooting->AddPreShooting( this );
}

void VCubemapShooting::OnDeactivate()
{
	m_pParentShooting->RemovePreShooting( this );
}

namespace {
	using namespace v3d::math;
	// to be migrated to mathlib

	VMatrix44f ProjectionMatrix(float fovy, float aspect, float znear, float zfar)
	{
		VMatrix44f mat;
		MakeProjectionMatrix( &mat, fovy, aspect, znear, zfar );
		return mat;
	}

	VMatrix44f LookAtMatrix(
		float posx, float posy, float posz,
		float lookatx, float lookaty, float lookatz,
		float upx, float upy, float upz)
	{
		VRBTransform transform;
		transform.SetLookAt( posx, posy, posz, lookatx, lookaty, lookatz, upx, upy, upz );
		return transform.AsMatrix();
	}

	VMatrix44f LookAtDirMatrix(
		float lookatx, float lookaty, float lookatz, 
		float upx, float upy, float upz)
	{
		return LookAtMatrix( 0.f, 0.f, 0.f, lookatx, lookaty, lookatz, upx, upy, upz );
	}
}

void VCubemapShooting::Render()
{
	V3D_ASSERT( m_pScene.Get() != NULL );

	const vuint sideCount = 6;
	const vuint colorComponentCount = 4;

	static float sideColors[sideCount * colorComponentCount] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f
	};

	static math::VRBTransform cameraTransforms[6] = {
		math::VRBTransform( 0.f, 0.f, 0.f,  1.f, 0.f, 0.f,  0.f, 1.f, 0.f ),
		math::VRBTransform( 0.f, 0.f, 0.f,  1.f, 0.f, 0.f,  0.f, 1.f, 0.f ),
		math::VRBTransform( 0.f, 0.f, 0.f,  1.f, 0.f, 0.f,  0.f, 1.f, 0.f ),
		math::VRBTransform( 0.f, 0.f, 0.f,  1.f, 0.f, 0.f,  0.f, 1.f, 0.f ),
		math::VRBTransform( 0.f, 0.f, 0.f,  1.f, 0.f, 0.f,  0.f, 1.f, 0.f ),
		math::VRBTransform( 0.f, 0.f, 0.f,  1.f, 0.f, 0.f,  0.f, 1.f, 0.f )

		//math::VRBTransform( 0.f, 0.f, 0.f,  1.f, 0.f, 0.f,  0.f, 1.f, 0.f ),
		//math::VRBTransform( 0.f, 0.f, 0.f,  -1.f, 0.f, 0.f,  0.f, 1.f, 0.f ),
		//math::VRBTransform( 0.f, 0.f, 0.f,  0.f, 1.f, 0.f,  0.f, 0.f, 1.f ),
		//math::VRBTransform( 0.f, 0.f, 0.f,  0.f, -1.f, 0.f,  0.f, 0.f, -1.f ),
		//math::VRBTransform( 0.f, 0.f, 0.f,  0.f, 0.f, 1.f, 0.f, 1.f, 0.f ),
		//math::VRBTransform( 0.f, 0.f, 0.f,  0.f, 0.f, -1.f, 0.f, 1.f, 0.f )
	};

	//static math::VMatrix44f cameraMatrices[6] = {
	//	cameraTransforms[0].AsMatrix(),
	//	cameraTransforms[1].AsMatrix(),
	//	cameraTransforms[2].AsMatrix(),
	//	cameraTransforms[3].AsMatrix(),
	//	cameraTransforms[4].AsMatrix(),
	//	cameraTransforms[5].AsMatrix()
	//	//LookAtDirMatrix( 1.f, 0.f, 0.f,  0.f, 1.f, 0.f ),
	//	//LookAtDirMatrix( -1.f, 0.f, 0.f,  0.f, 1.f, 0.f ),
	//	//LookAtDirMatrix( 0.f, 1.f, 0.f,  0.f, 0.f, 1.f ),
	//	//LookAtDirMatrix( 0.f, -1.f, 0.f,  0.f, 0.f, -1.f ),
	//	//LookAtDirMatrix( 0.f, 0.f, 1.f, 0.f, 1.f, 0.f ),
	//	//LookAtDirMatrix( 0.f, 0.f, -1.f, 0.f, 1.f, 0.f )
	//};

	float* c = &sideColors[0];

	if( m_pContext != NULL )
	{
		using graphics::VCubeMapContext;
		using graphics::IVDevice;

		//glClearColor( 1.0f, 1.0f, 0.0f, 1.0f );

		for( VCubeMapContext::Side side = VCubeMapContext::PosX;
			side <= VCubeMapContext::NegZ;
			++side )
		{
			graphics::VCamera camera;
			camera.SetTransform( cameraTransforms[int(side)] );
			m_pScene->UpdateAndCull( camera );

			static math::VMatrix44f projectionMatrix = 
				ProjectionMatrix( 90.0f, 1.0f, 1.0f, 1000.0f );
			m_pDevice->SetMatrix( IVDevice::ProjectionMatrix, projectionMatrix );
			m_pDevice->SetViewTransform( cameraTransforms[int(side)] );
			//m_pDevice->SetMatrix( IVDevice::ViewMatrix, cameraMatrices[int(side)] );

			m_pContext->SetActiveSide(side);
			//m_pContext->MakeCurrent();
			m_pDevice->BeginScene();

			//glClearColor( .2f, .2f, .2f, 1.f );
			glClearColor( c[0], c[1], c[2], c[3] );
			c += 4;
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			VRangeIterator<const IVShapePart> visibleObject = m_pScene->GetVisibleMeshes();
			while( visibleObject.HasNext() )
			{
				for(vint passNum = visibleObject->GetPassCount() - 1;
					passNum >= 0;
					--passNum)
				{
					visibleObject->ApplyPassStates( passNum, *m_pDevice );
					visibleObject->SendGeometry( *m_pDevice );
					visibleObject->UnapplyPassStates( passNum, *m_pDevice );
				}

				++visibleObject;
			}
		}

		m_pDevice->EndScene();
		//m_pContext->SwapBuffers();
	}
}

vbool VCubemapShooting::IsActive() const
{
	V3D_THROW(VException, "ooops, this is called?");
}

void VCubemapShooting::SetCubeMapResource(const std::string& resourceName)
{
	try
	{
		using namespace graphics;

		VResourceId res( resourceName.c_str() );

		m_pCubeMapTexture = res->GetMutableData<VCubeMapTexture>();

		if( ! res->ContainsData<VCubeMapContext>() )
		{
			IVRenderContext* mainContext =
				VGraphicsServicePtr()->GetMainDevice()->GetRenderContext();

			VCubeMapContext* newContext = new VCubeMapContext(
				&*m_pCubeMapTexture,
				mainContext );
			res->AddData( newContext );
		}

		m_pContext = res->GetMutableData<VCubeMapContext>();
		m_pDevice = res->GetMutableData<IVDevice>();
	}
	catch(VResourceException&)
	{}
}

std::string VCubemapShooting::GetCubeMapResource() const
{
	return m_pCubeMapTexture.GetResourceName();
}

void VCubemapShooting::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	interpreter.AddAccessorOption<VCubemapShooting, std::string>(
		"cubemap_resource",
		&VCubemapShooting::GetCubeMapResource,
		&VCubemapShooting::SetCubeMapResource );
}

messaging::VMessageInterpreter* VCubemapShooting::GetMessageInterpreterForClass()
{
	static messaging::VMessageInterpreter interpreter;
	return &interpreter;
}

V3D_REGISTER_PART_PARSER(VCubemapShooting);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

