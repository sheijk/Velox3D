#ifndef V3D_IVDOCUMENT_2004_06_18_H
#define V3D_IVDOCUMENT_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Editor/IVMessage.h>
#include <V3dLib/BoostSignals.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * A document holds some data which may be loaded from and saved to files
 *
 * @author sheijk
 */
class IVDocument
{
public:
	enum WindowMode
	{
		Hide,
		Show
		// Maximized, Minimized,...
	};

	enum FocusEventType
	{
		GotFocus,
		LostFocus
	};

	typedef boost::signal<void (IVDocument&, FocusEventType)> FocusSignal;
	typedef FocusSignal::slot_type FocusSlot;
	typedef boost::signals::connection Connection;

	/** 
	 * Registers a slot which will be called when the documents gets the 
	 * focus
	 */
	virtual Connection RegisterFocusListener(const FocusSlot& in_Slot) = 0;

	virtual void SetWindowMode(WindowMode in_Mode) = 0;

	virtual VMessageTreatment DeliverMessage(IVMessage& in_Message) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_IVDOCUMENT_2004_06_18_H
