#ifndef V3D_IVERRORSERVICE_H
#define V3D_IVERRORSERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

/**
 * the error service
 */
class IVErrorService : public VNamedObject
{
//	IVExampleService();
public:
	IVErrorService(std::string in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent)
	{
	}

	enum LogMode
	{
		OK,
		Warning,
		Error
	};

	virtual void Message( const std::string& in_Message, LogMode in_LogMode = OK ) = 0;
	
	virtual void BeginProgressbar() = 0;
	virtual void UpdateProgressbar( const vfloat32 in_fIndex ) = 0;
	virtual void EndProgressbar() = 0;

	virtual void CreateState( const std::string& in_Name, const std::string& in_Text ) = 0;
	virtual void UpdateState( const std::string& in_Name, const std::string& in_State ) = 0;
	virtual void DeleteState( const std::string& in_Name ) = 0;
};

//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVERRORSERVICE_H