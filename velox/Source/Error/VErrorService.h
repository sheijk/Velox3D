#ifndef V3D_VERRORSERVICE_H
#define V3D_VERRORSERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>
#include <v3d/Error/IVErrorService.h>
#include <list>

//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

class IVLogDevice;

/**
 * A service which implements the error interface
 */
class VErrorService : public IVErrorService
{
private:
	
	std::list<IVLogDevice*>		m_LogDevices;
	std::list<IVLogDevice*>::iterator m_Iter;

public:
	VErrorService();
	virtual ~VErrorService();

	virtual vbool RegisterLogDevice( IVLogDevice* in_pLogDevice );
	virtual void UnregisterLogDevice( IVLogDevice* in_pLogDevice );
			
	virtual void Message( const VString& in_Message, LogMode in_LogMode = Ok );
	
	virtual void BeginProgressbar();
	virtual void UpdateProgressbar( const vfloat32 in_fIndex );
	virtual void EndProgressbar();

	virtual void CreateState( const VString& in_Name, const VString& in_Text );
	virtual void UpdateState( const VString& in_Name, const VString& in_Text );
	virtual void DeleteState( const VString& in_Name );
};

//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------
#endif // V3D_VERRORSERVICE_H
