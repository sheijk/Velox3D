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

/**
 * The interface for the XML service
 * @author insane/acrylsword/sheijk
 * @version 2.0
 */
class IVXMLService : public VNamedObject
{
public:
	typedef VPointer<IVXMLWriter>::SharedPtr IVXMLWriterPtr;
	typedef VPointer<vfs::IVStream>::SharedPtr IVStreamPtr;
	typedef VPointer<IVXMLElement>::SharedPtr IVXMLElementPtr;

	/**
	 * Parses an xml file through an IVStream. Returns the root node of
	 * the xml tree.
	 *
	 * @param in_pStream A vfs data stream that represents a xml file
	 * @author acrylsword
	 */
	virtual IVXMLElementPtr GetRootElement(vfs::IVStream* in_pStream) = 0; 

	/**
	* Parses an xml file through the local file system. Returns the root
	* node of the xml tree.
	*
	* @param in_strName The file to open
	* @author acrylsword
	*/
	virtual IVXMLElementPtr GetRootElement(VStringParam in_strName) = 0; 

	/**
	 * Loads a xml file from the virtual file system an uses the visitor
	 * to travesal the xml tree.
	 * 
	 * @param in_Visitor The visitor that visits this xml tree
	 * @param in_Stream The data stream to the xml file
	 *
	 * @author acrylsword
	 * @version 1.0
	 */
	virtual bool Visit(IVXMLVisitor& in_Visitor, vfs::IVStream& in_Stream) = 0;

	/**
	* Loads a xml file from the local file system an uses the visitor
	* to travesal the xml tree.
	* 
	* @param in_Visitor The visitor that visits this xml tree
	* @param in_strFile The xml file 
	*
	* @author acrylsword
	* @version 1.0
	*/
	virtual bool Visit(IVXMLVisitor& in_Visitor, VStringParam in_strFile) = 0;

	/**
	 * Creates an xml writer to write to an xml file in the vfs
	 */
	virtual IVXMLWriterPtr CreateXMLWriter(VStringParam FileName) = 0;

	/**
	 * Creates an xml writer to write to a stream
	 //TODO: klaeren, wann der stream geschlossen wird
	 */
	virtual IVXMLWriterPtr CreateXMLWriter(IVStreamPtr pStream) = 0;

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