#ifndef V3D_VPRINTACTION_2004_06_11_H
#define V3D_VPRINTACTION_2004_06_11_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Editor.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

class VPrintAction : public IVAction
{
public:
	VPrintAction(VStringParam in_strMessage);
	VPrintAction(VStringParam in_strMessage, VStringParam in_strCaption);

	virtual VStringRetVal GetName();	
	virtual void Execute();

	void SetMessage(VStringParam in_strMessage);

private:
	VString m_strMessage;
	VString m_strCaption;
};


//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VPRINTACTION_2004_06_11_H
