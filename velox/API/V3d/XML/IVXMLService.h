#ifndef V3D_IVXMLSERVICE_H
#define V3D_IVXMLSERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>
#include <v3d/Vfs/IVStream.h>
#include <v3d/XML/IVXMLWriter.h>
#include <V3d/XML/IVXMLVisitor.h>
#include <V3d/Core/SmartPtr/VGuards.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------
using namespace v3d::vfs;
//-----------------------------------------------------------------------------

/**
 * The interface for the XML service
 * @author insane
 * @version 1.0
 */

class IVXMLService : public VNamedObject
{
public:
typedef VPointer<IVXMLWriter>::SharedPtr IVXMLWriterPtr;
        
	virtual void ParseXMLFile(IVStream* in_pStream, IVXMLVisitor* in_pVisitor) = 0;
	virtual void ParseXMLFile(VStringParam in_pcName, IVXMLVisitor* in_pVisitor) = 0;
	virtual IVXMLWriterPtr CreateXMLWriter(VStringParam FileName) = 0;
	virtual IVXMLWriterPtr CreateXMLWriter(IVStream* pStream) = 0;
	virtual ~IVXMLService() {};
	
protected:
	/**
	* a protected constructor is needed to pass the parameters to the 
	* VNamedObject constructor
	*/
	IVXMLService(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent)
		{
		}
};

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLSERVICE_H
