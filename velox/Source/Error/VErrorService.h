#ifndef V3D_VERRORSERVICE_H
#define V3D_VERRORSERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>
#include <v3d/Error/IVErrorService.h>
#include "VLogModeEnum.h"
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

	vbool RegisterLogDevice( IVLogDevice* in_pLogDevice );
			
	virtual void Message( const std::string& in_Message, LogMode in_LogMode = OK );
	
	virtual void BeginProgressbar();
	virtual void UpdateProgressbar( const vfloat32 in_fIndex );
	virtual void EndProgressbar();

	virtual void CreateState( const std::string& in_Name, const std::string& in_Text );
	virtual void UpdateState( const std::string& in_Name, const std::string& in_Text );
	virtual void DeleteState( const std::string& in_Name );
};

//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------
#endif // V3D_VERRORSERVICE_H
