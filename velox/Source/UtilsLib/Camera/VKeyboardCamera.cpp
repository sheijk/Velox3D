#include <V3d/Graphics/Misc/VKeyboardCamera.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
#include <V3d/XML.h>

#include <sstream>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d::input;
using namespace v3d::xml;
using std::string;
using utils::VStringValue;

const std::string g_strCameraConfigFile = "/data/camera.cfg";

VKeyboardCamera::VKeyboardCamera(IVInputManager& in_InputDevice)
{
	QueryButtons(in_InputDevice);

	m_bIgnoreMouse = false;

	m_fMovementSpeed = 2.0f;
	m_fRotationSpeedX = 1.0f;
	m_fRotationSpeedY = 1.0f;
	m_fRotationSpeedZ = 10.0f;
	m_fKeyRotationFactor = 50.0f;

    LoadCameraPositions(g_strCameraConfigFile);
}

VKeyboardCamera::~VKeyboardCamera()
{
	SaveCameraPositions(g_strCameraConfigFile);
}

void VKeyboardCamera::QueryButtons(IVInputManager& in_InputManager)
{
	//m_pUpButton			= &in_InputManager.GetStandardKeyboard().GetKey(KeyUp);
	//m_pDownButton		= &in_InputManager.GetStandardKeyboard().GetKey(KeyDown);
	//m_pLeftButton		= &in_InputManager.GetStandardKeyboard().GetKey(KeyLeft);
	//m_pRightButton		= &in_InputManager.GetStandardKeyboard().GetKey(KeyRight);

	m_pForwardButton	= &in_InputManager.GetStandardKeyboard().GetKey(KeyW);
	m_pBackwardButton	= &in_InputManager.GetStandardKeyboard().GetKey(KeyS);
	m_pLeftButton		= &in_InputManager.GetStandardKeyboard().GetKey(KeyA);
	m_pRightButton		= &in_InputManager.GetStandardKeyboard().GetKey(KeyD);
	m_pUpButton			= &in_InputManager.GetStandardKeyboard().GetKey(KeyR);
	m_pDownButton		= &in_InputManager.GetStandardKeyboard().GetKey(KeyF);

	m_pRotateLeftButton		= &in_InputManager.GetStandardKeyboard().GetKey(KeyLeft);
	m_pRotateRightButton	= &in_InputManager.GetStandardKeyboard().GetKey(KeyRight);
	m_pRotateUpButton		= &in_InputManager.GetStandardKeyboard().GetKey(KeyUp);
	m_pRotateDownButton		= &in_InputManager.GetStandardKeyboard().GetKey(KeyDown);

	m_pRollLeftButton2	= &in_InputManager.GetStandardKeyboard().GetKey(KeyQ);
	m_pRollRightButton2	= &in_InputManager.GetStandardKeyboard().GetKey(KeyE);

	m_pRollLeftButton	= &in_InputManager.GetStandardMouse().GetLeftButton();
	m_pRollRightButton	= &in_InputManager.GetStandardMouse().GetRightButton();
	m_pMouseXAxis		= &in_InputManager.GetStandardMouse().GetXAxis();
	m_pMouseYAxis		= &in_InputManager.GetStandardMouse().GetYAxis();

	m_pFastTriggerButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyLeftShift);

	m_pSavePosModifierButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyLeftAlt);

	for(vuint num = 0; num < 10; ++num) 
	{
		m_GotoButtons.push_back(&in_InputManager.GetStandardKeyboard().GetKey(VKeyCode(vint(Key1) + num)));
	}
}

namespace {
	const vchar* cameraConfigNodeName = "camera";
	const vchar* posNodeName = "pos";
	const vchar* idAttribName = "id";
	const vchar* xAttribName = "x";
	const vchar* yAttribName = "y";
	const vchar* zAttribName = "z";
}

V3D_DECLARE_EXCEPTION(VCameraCfgLoadFailure, VException);

VMatrix44f LoadMatrixFromXML(IVXMLElement* in_pElement)
{
	VMatrix44f matrix;

	for(vuint row = 0; row < 4; ++row)
	for(vuint column = 0; column < 4; ++column)
	{
		std::stringstream tmp;
		tmp << "r" << row << "c" << column;
		std::string attribName = tmp.str();

		vfloat32 val = in_pElement->GetAttributeValue<vfloat32>(attribName.c_str());
		matrix.Set(row, column, val);
	}

	return matrix;
};

void WriteMatrixToXML(const VMatrix44f& in_Matrix, IVXMLElement* in_pElement)
{
	for(vuint row = 0; row < 4; ++row)
	for(vuint column = 0; column < 4; ++column)
	{
		std::stringstream tmp;
		tmp << "r" << row << "c" << column;
		std::string attribName = tmp.str();

		vfloat32 val = in_Matrix.Get(row, column);

		in_pElement->AddAttribute(attribName.c_str(), VStringValue(val));
	}
}

//math::VRBTransform LoadRBTransformFromXML(IVXMLElement* in_pElement)
//{
//	math::VRBTransform transform;
//
//	VVector3f pos = VVector3f(
//		in_pElement->GetAttributeValue<vfloat32>("posx"),
//		in_pElement->GetAttributeValue<vfloat32>("posy"),
//		in_pElement->GetAttributeValue<vfloat32>("posz"));
//
//	VVector3f viewDir = VVector3f(
//		in_pElement->GetAttributeValue<vfloat32>("viewx"),
//		in_pElement->GetAttributeValue<vfloat32>("viewy"),
//		in_pElement->GetAttributeValue<vfloat32>("viewz"));
//
//	VVector3f up = VVector3f(
//		in_pElement->GetAttributeValue<vfloat32>("upx"),
//		in_pElement->GetAttributeValue<vfloat32>("upy"),
//		in_pElement->GetAttributeValue<vfloat32>("upz"));
//
//    transform.SetLookAt(pos, viewDir, up);
//	return transform;
//}
//
//void WriteRBTransformToXML(const VRBTransform& transform, IVXMLElement* in_pElement)
//{
//	VVector3f pos = transform.GetPosition();
//	VVector3f viewDir = transform.GetZAxis();
//}

void VKeyboardCamera::LoadCameraPositions(const std::string& in_strFileName)
{
	//try
	//{
	//	m_SavedOrientations.clear();

	//	VSharedPtr<IVXMLElement> pRoot = VXMLServicePtr()->GetRootElement(in_strFileName.c_str());

	//	if( pRoot->GetName() != cameraConfigNodeName )
	//	{
	//		V3D_THROWMSG(VException, "Expected root node name '" 
	//			<< cameraConfigNodeName << "' but found '"
	//			<< pRoot->GetName() << "'");
	//	}

	//	VRangeIterator<IVXMLNode> nodeIter = pRoot->ChildBegin();
	//	while( nodeIter.HasNext() )
	//	{
	//		IVXMLElement* pElement = nodeIter->ToElement();

	//		if( pElement != 0 && pElement->GetName() == posNodeName )
	//		{
	//			vuint id = pElement->GetAttributeValue<vuint>(idAttribName);

	//			VMatrix44f pos = LoadMatrixFromXML(pElement);

	//			m_SavedOrientations[id] = pos;
	//		}
	//	}	
 //       
	//}
	//catch(VException& e)
	//{
	//	vout << "Warning: could not load camera config file \"" 
	//		<< in_strFileName << "\": \""
	//		<< e.GetErrorString() << "\""
	//		<< ". Saved positions will not be "
	//		<< "available" << vendl;
	//}
}

void VKeyboardCamera::SaveCameraPositions(const std::string& in_strFileName)
{
	//try
	//{
	//	VSharedPtr<IVXMLElement> pRoot = 
	//		VXMLServicePtr()->CreateEmptyElement(cameraConfigNodeName);

	//	for(SavedOrientationMap::iterator orient = m_SavedOrientations.begin();
	//		orient != m_SavedOrientations.end(); ++orient)
	//	{
	//		VSharedPtr<IVXMLElement> pOrientNode =
	//			VXMLServicePtr()->CreateEmptyElement(posNodeName);

	//		pOrientNode->AddAttribute(idAttribName, VStringValue(orient->first));

	//		WriteMatrixToXML(orient->second, pOrientNode.Get());
	//	}

	//	SaveXMLElementToFile(pRoot.Get(), in_strFileName.c_str());
	//}
	//catch(VException& e)
	//{
	//	vout << "Could not save camera config file to '"
	//		<< in_strFileName << "': "
	//		<< e.GetErrorString();
	//}
}

graphics::VCamera& VKeyboardCamera::GetCamera()
{
	return m_Camera;
}

const graphics::VCamera& VKeyboardCamera::GetCamera() const
{
	return m_Camera;
}

void VKeyboardCamera::Move(vfloat32 in_fSeconds)
{
	if( m_pFastTriggerButton->IsDown() == true )
		in_fSeconds *= 4;

	// strafing
	if(m_pForwardButton->IsDown() == true)
		m_Camera.MoveForward(m_fMovementSpeed * in_fSeconds);

	if(m_pBackwardButton->IsDown() == true)
		m_Camera.MoveForward(-m_fMovementSpeed* in_fSeconds);

	if(m_pLeftButton->IsDown() == true)
		m_Camera.Strafe(-m_fMovementSpeed * in_fSeconds);

	if(m_pRightButton->IsDown() == true)
		m_Camera.Strafe(m_fMovementSpeed * in_fSeconds);

	if(m_pUpButton->IsDown() == true)
		m_Camera.MoveUp(m_fMovementSpeed * in_fSeconds);

	if(m_pDownButton->IsDown() == true)
		m_Camera.MoveUp(-m_fMovementSpeed * in_fSeconds);

	// keyboard rotation
	if( m_pRotateLeftButton->IsDown() == true )
		m_Camera.RotateY(-m_fRotationSpeedY * m_fKeyRotationFactor  * in_fSeconds);

	if( m_pRotateRightButton->IsDown() == true )
		m_Camera.RotateY(m_fRotationSpeedY * m_fKeyRotationFactor * in_fSeconds);

	if( m_pRotateUpButton->IsDown() == true )
		m_Camera.RotateX(-m_fRotationSpeedX * m_fKeyRotationFactor  * in_fSeconds);

	if( m_pRotateDownButton->IsDown() == true )
		m_Camera.RotateX(m_fRotationSpeedX * m_fKeyRotationFactor  * in_fSeconds);

	vbool rollRight = false;
	vbool rollLeft = false;

	if( ! m_bIgnoreMouse )
	{
		if( m_pRollRightButton->IsDown() )
			rollRight = true;
		if( m_pRollLeftButton->IsDown() )
			rollLeft = true;

		//if(m_pRollRightButton->IsDown() == true || m_pRollRightButton2->IsDown() == true)
		//	m_Camera.RotateZ(-m_fRotationSpeedZ * in_fSeconds);

		//if(m_pRollLeftButton->IsDown() == true || m_pRollLeftButton2->IsDown() == true)
		//	m_Camera.RotateZ(m_fRotationSpeedZ * in_fSeconds);

		m_Camera.RotateX(- m_pMouseYAxis->GetLastMovement() * m_fRotationSpeedX * in_fSeconds);
		m_Camera.RotateY(m_pMouseXAxis->GetLastMovement() * m_fRotationSpeedY * in_fSeconds);
	}

	if( m_pRollRightButton2->IsDown() )
		rollRight = true;
	if( m_pRollLeftButton2->IsDown() )
		rollLeft = true;

	if( rollRight )
		m_Camera.RotateZ(-m_fRotationSpeedZ * in_fSeconds);

	if( rollLeft )
		m_Camera.RotateZ(m_fRotationSpeedZ * in_fSeconds);

	for(vuint savedOrientNum = 0; savedOrientNum < m_GotoButtons.size(); ++savedOrientNum)
	{
		if( m_GotoButtons[savedOrientNum]->IsDown() )
		{
			if( m_pSavePosModifierButton->IsDown() )
			{
				m_SavedOrientations[savedOrientNum] = m_Camera.GetTransform();

//				vout << "Saved orientation " << savedOrientNum << vendl;
			}
			else
			{
				if( m_SavedOrientations.find(savedOrientNum) != m_SavedOrientations.end() )
				{
					m_Camera.SetTransform(m_SavedOrientations[savedOrientNum]);

//					vout << "Restored orientation " << savedOrientNum << vendl;
				}
			}
		}
	}
}

const VMatrix44f& VKeyboardCamera::GetTransform() const
{
	return ViewMatrix();
}

const VMatrix44f& VKeyboardCamera::ViewMatrix() const
{
	return m_Camera.ViewMatrix();
}

const math::VRBTransform& VKeyboardCamera::Transform() const
{
	return m_Camera.Transform();
}

void VKeyboardCamera::ApplyTo(IVDevice& in_Device) const
{
	m_Camera.ApplyTo(in_Device);
}

VVector3f VKeyboardCamera::GetPosition() const
{
	return m_Camera.GetPosition();
}

VVector3f VKeyboardCamera::GetViewDirection() const
{
	return m_Camera.GetViewDirection();
}

VVector3f VKeyboardCamera::GetUpVector() const
{
	return m_Camera.GetUpVector();
}

void VKeyboardCamera::SetMovementSpeed(vfloat32 in_fMovementSpeed)
{
	m_fMovementSpeed = in_fMovementSpeed;
}

vfloat32 VKeyboardCamera::GetMovementSpeed() const
{
	return m_fMovementSpeed;
}

void VKeyboardCamera::SetRotationSpeedX(vfloat32 in_fNewSpeedX)
{
	m_fRotationSpeedX = in_fNewSpeedX;
}

vfloat32 VKeyboardCamera::GetRotationSpeedX() const
{
	return m_fRotationSpeedX;
}

void VKeyboardCamera::SetRotationSpeedY(vfloat32 in_fNewSpeedY)
{
	m_fRotationSpeedY = in_fNewSpeedY;
}

vfloat32 VKeyboardCamera::GetRotationSpeedY() const
{
	return m_fRotationSpeedY;
}

void VKeyboardCamera::SetRotationSpeedZ(vfloat32 in_fNewSpeedZ)
{
	m_fRotationSpeedZ = in_fNewSpeedZ;
}

vfloat32 VKeyboardCamera::GetRotationSpeedZ() const
{
	return m_fRotationSpeedZ;
}

void VKeyboardCamera::SetIgnoreMouse(vbool in_bMouseIgnored)
{
	m_bIgnoreMouse = in_bMouseIgnored;
}

vbool VKeyboardCamera::IsMouseIgnored() const
{
	return m_bIgnoreMouse;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
