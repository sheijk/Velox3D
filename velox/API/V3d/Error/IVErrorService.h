#ifndef V3D_IVERRORSERVICE_H
#define V3D_IVERRORSERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>
#include <v3d/Error/IVLogDevice.h>
#include <v3d/Error/VLogModeEnum.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

//TODO: Dokumentation (sheijk)

/**
 * the error service
 *
 */
class IVErrorService : public VNamedObject
{
//	IVExampleService();
public:
	IVErrorService(std::string in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent)
	{
	}

	virtual vbool RegisterLogDevice( IVLogDevice* in_pLogDevice ) = 0;
	virtual vbool UnregisterLogDevice( IVLogDevice* in_pLogDevice ) = 0;

	virtual void Message( const VString& in_Message, LogMode in_LogMode = Ok ) = 0;
	
	virtual void BeginProgressbar() = 0;
	virtual void UpdateProgressbar( const vfloat32 in_fIndex ) = 0;
	virtual void EndProgressbar() = 0;

	virtual void CreateState( const VString& in_Name, const VString& in_Text ) = 0;
	virtual void UpdateState( const VString& in_Name, const VString& in_State ) = 0;
	virtual void DeleteState( const VString& in_Name ) = 0;
};

//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVERRORSERVICE_H