class VCameraToolWindow : public wxMiniFrame
{
	enum MenuCommands
	{
		FirstCommand = 0,
		MoveXYCommand,
		MoveXZCommand,
		RotateCommand,
		LastCommand
	};

	typedef math::VVector<vfloat32, 4> VVector4f;

public:
	typedef v3d::graphics::VCamera Camera;

	VCameraToolWindow(
		wxWindow* in_pParent, 
		Camera& in_Camera
		) :
		wxMiniFrame(
			in_pParent,
			-1,
			"camera",
			wxPoint(0, 0),
			wxSize(100, 100),
			wxTINY_CAPTION_HORIZ | wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR
			),
		m_Camera(in_Camera)
	{
		wxPoint parentPos = in_pParent->ClientToScreen(wxPoint(0,15));
			//in_pParent->GetPosition();
		SetSize(parentPos.x, parentPos.y, -1, -1);

		// build popup menu
		m_PopupMenu.Append(-1, "lalala", "a dummmy function");
		wxMenu* pDragFuncMenu = &m_PopupMenu;
		pDragFuncMenu->Append(MoveXYCommand, "move x/y");
		pDragFuncMenu->Append(MoveXZCommand, "move x/z");
		pDragFuncMenu->Append(RotateCommand, "rotate");
		pDragFuncMenu->Append(FirstCommand, "fixed view");
		//m_PopupMenu.Append(pDragFuncMenu);

		VVector4f right; right.Set(0, 1.0f);
		VVector4f up; up.Set(1, 1.0f);
		m_pMouseHandler.Assign(new Mover(right, up, "move x/y"));
	}

private:
	struct MovementInfo
	{
		MovementInfo(Camera& c, wxMouseEvent& e, wxPoint p, vfloat32 s) :
			cam(c), event(e), movement(p), scale(s)
		{}

		Camera& cam;
		wxMouseEvent& event;
		wxPoint movement;
		vfloat32 scale;
	};

	struct MouseHandler
	{
		virtual void HandleEvent(MovementInfo& info) = 0;
		virtual VStringRetVal GetName() const = 0;
	};

	typedef VPointer<MouseHandler>::SharedPtr MouseHandlerPtr;

	class Mover : public MouseHandler
	{
		VVector4f right;
		VVector4f up;
		std::string name;
	public:
		Mover(VVector4f r, VVector4f u, std::string n) : 
			right(r), up(u), name(n)
		{}

		virtual VStringRetVal GetName() const
		{
			return name.c_str();
		}

		virtual void HandleEvent(MovementInfo& info)
		{
			// calculate movment:
			VVector4f mov = right * info.scale * -info.movement.x +
							up * info.scale * info.movement.y;

			info.cam.MoveForward(mov.Get(2));
			info.cam.MoveUp(mov.Get(1));
			info.cam.Strafe(mov.Get(0));
		}
	};

	class Rotator : public MouseHandler
	{
	public:
		virtual VStringRetVal GetName() const
		{
			return "rotate";
		}

		virtual void HandleEvent(MovementInfo& info)
		{
			info.cam.RotateY(-info.movement.x * info.scale);
			info.cam.RotateX(info.movement.y * info.scale);
		}
	};

	class FixedPos : public MouseHandler
	{
	public:
		virtual VStringRetVal GetName() const
		{
			return "fixed view";
		}

		virtual void HandleEvent(MovementInfo& info) 
		{}
	};

	void OnLeftMouseDown(wxMouseEvent& in_Event)
	{
		vout << "left btn pressed.." << vendl;

		m_LastMousePos = in_Event.GetPosition();

		CaptureMouse();
	}

	void OnLeftMouseUp(wxMouseEvent& in_Event)
	{
		vout << "left btn release.." << vendl;

		ReleaseMouse();
	}

	void OnRightDown(wxMouseEvent& in_Event)
	{
		//CaptureMouse();
		PopupMenu(&m_PopupMenu, in_Event.GetPosition());
	}

	void OnRightUp(wxMouseEvent& in_Event)
	{
		//ReleaseMouse();
	}

	void OnMouseMoved(wxMouseEvent& in_Event)
	{
		wxPoint mousePos = in_Event.GetPosition();
		wxPoint movement = m_LastMousePos - mousePos;

		if( in_Event.LeftIsDown() )
		{
			MovementInfo info(m_Camera, in_Event, movement, 2.0f);
			m_pMouseHandler->HandleEvent(info);
		}

		m_LastMousePos = mousePos;
	}

	void OnMenuItem(wxCommandEvent& in_Event)
	{
		vout << "invoked cmd " << in_Event.GetId() << vendl;
		switch(in_Event.GetId())
		{
		case MoveXYCommand:
			{
				VVector4f right; right.Set(0, 1.0f);
				VVector4f up; up.Set(1, 1.0f);
				m_pMouseHandler.Assign(new Mover(right, up, "move x/y"));
			} break;

		case MoveXZCommand:
			{
				VVector4f right; right.Set(0, 1.0f);
				VVector4f up; up.Set(2, 1.0f);
				m_pMouseHandler.Assign(new Mover(right, up, "move x/z"));
			} break;

		case RotateCommand:
			{
				m_pMouseHandler.Assign(new Rotator());
			} break;

		default:
			{
				m_pMouseHandler.Assign(new FixedPos());
			} break;
		};

		SetTitle(wxString(m_pMouseHandler->GetName()));
	}

	wxPoint m_LastMousePos;
	wxMenu m_PopupMenu;
	Camera& m_Camera;
	MouseHandlerPtr m_pMouseHandler;

	DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(VCameraToolWindow, wxMiniFrame)
EVT_LEFT_DOWN(VCameraToolWindow::OnLeftMouseDown)
EVT_LEFT_UP(VCameraToolWindow::OnLeftMouseUp)
EVT_RIGHT_DOWN(VCameraToolWindow::OnRightDown)
EVT_RIGHT_UP(VCameraToolWindow::OnRightUp)
EVT_MOTION(VCameraToolWindow::OnMouseMoved)
EVT_MENU_RANGE(FirstCommand, LastCommand, VCameraToolWindow::OnMenuItem)
END_EVENT_TABLE()

class VCameraTool : public IVTool
{
	typedef VPointer<IVAction>::SharedPtr ActionPtr;
	typedef std::vector<ActionPtr> ActionList;
	typedef VSTLDerefIteratorPol<ActionList::iterator, IVAction> ActionIterPol;

public:
	VCameraTool(VCameraToolWindow::Camera& in_Camara) :
		m_pWindow(0),
		m_Camera(in_Camara)
	{
	}

	ActionIterator ActionsBegin() 
	{
		return ActionIterator(new ActionIterPol(m_Actions.begin()));
	}

	ActionIterator ActionsEnd() 
	{
		return ActionIterator(new ActionIterPol(m_Actions.end()));
	}

	virtual VStringRetVal GetName() const
	{
		return "CameraTool";
	}

	virtual void Enable(wxWindow* in_pParent)
	{
		if(! m_pWindow)
		{
			m_pWindow = new VCameraToolWindow(in_pParent, m_Camera);
			m_pWindow->Show(true);
		}
	}

	virtual VMessageTreatment DeliverMessage(IVMessage& in_Message)
	{
		vout << "camera tool received msg" << vendl;

		return MessageIgnored;
	}

private:
	VCameraToolWindow* m_pWindow;
	VCameraToolWindow::Camera& m_Camera;
	ActionList m_Actions;
};
