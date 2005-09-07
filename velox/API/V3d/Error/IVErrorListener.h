#ifndef V3D_IVERRORLISTENER_H
#define V3D_IVERRORLISTENER_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/Wrappers/VString.h>
#include <V3d/Error/VMessageTypeEnum.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------
/**
 * Interface for log device. 
 * @author AcrylSword
 * @version 1.0
 */
class IVErrorListener
{
public:
	//TODO: ieeh ;), wozu wird das gebraucht? (sheijk)
	friend class	IVErrorService;

			IVErrorListener() {};
	virtual	~IVErrorListener() {};

//protected:
	/**
	 * Called by the \a Error Service when it gets a message
	 * @param in_Message The Message
	 * @param in_LogMode A member of the MessageTyp enumeration
	 */
	virtual void OnMessage( VStringParam in_strMessage,
							VMessageType in_MessageType,
							VStringParam in_strFile,
							vuint in_nLine )=0;
	/**
	 * Called by the Error Service to begin a progressbar
     */	
	virtual void	OnProgressbarBegin()=0;

	/** Called by the error service to update the progressbar
	 * @param in_fIndex Index value between 0.0f and 1.0f
	 * fIndex should be between 0.0f and 1.0f. Other values are clamped.
	 */
    virtual void	OnProgressbarUpdate( const vfloat32 in_fIndex)=0;

	/** 
	 * Called by VDebugLogger to end the progressbar
     */
	virtual void	OnProgressbarEnd()=0;

	/** 
	 * Called by the error service to update a state
	 * @param in_StateName The name of the state
	 * @param in_Text The text of the state
	 * \a StateName is used as an identifier in all three state functions
	 */
    virtual void	OnStateUpdate( VStringParam in_Text ) = 0;
};

} // namespace error
} // namespace v3d
#endif

