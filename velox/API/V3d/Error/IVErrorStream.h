#ifndef V3D_IVERRORSTREAM_H
#define V3D_IVERRORSTREAM_H

#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Error/VMessageTypeEnum.h>
#include <v3d/Utils/IVStringStream.h>

namespace v3d {
namespace error {

/**
 * Interface for error streams
 * @author AcrylSword
 * @version 1.0
 */
class VEndDbgMsg
{
public:
	VEndDbgMsg( VStringParam in_strFile, vuint in_nLine ) : m_strFile(in_strFile), m_nLine(in_nLine) {};
	VStringParam m_strFile;
	vuint m_nLine;
};

class IVErrorStream : public utils::IVStringStream
{
public:
	IVErrorStream() {};
	virtual ~IVErrorStream() {};

	virtual void BeginProgressbar() = 0;
	virtual void UpdateProgressbar(vfloat32 in_fIndex) = 0;
	virtual void EndProgressbar() = 0;
	virtual void UpdateState(VStringParam in_strText ) = 0;
	virtual VStringRetVal GetName() = 0;
	virtual void SetLine( vuint in_nLine ) = 0;
	virtual void SetFile( VStringParam in_strLine ) = 0;
	virtual void SetMessageType( VMessageType in_MessageType ) = 0;
	virtual void Write( VStringParam in_strString ) = 0;
	virtual void Flush() = 0;
};
//-----------------------------------------------------------------------------
template <typename T> IVErrorStream& operator<<(IVErrorStream& in_Stream, T in_Val)
{
	std::ostringstream oStream;
	oStream << std::flush << in_Val;
	in_Stream.Write( oStream.str().c_str() );
	oStream.str("");
	return in_Stream;
}


inline IVErrorStream& operator<<( IVErrorStream& in_Stream, VMessageType in_MessageType )
{
	in_Stream.SetMessageType( in_MessageType );

	return in_Stream;
}

inline IVErrorStream& operator<< ( IVErrorStream& in_Stream, VEndDbgMsg in_EndDbgMsg  )
{
	
	in_Stream.SetFile( in_EndDbgMsg.m_strFile );
	in_Stream.SetLine( in_EndDbgMsg.m_nLine );
	in_Stream.Flush();

	return in_Stream;
}


#define V3D_DBGMSGEND v3d::error::VEndDbgMsg( __FILE__, __LINE__ )
//-----------------------------------------------------------------------------





}; //error
}; //v3d

#endif