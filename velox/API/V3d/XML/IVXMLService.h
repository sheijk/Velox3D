/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVXMLSERVICE_H
#define V3D_IVXMLSERVICE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VNamedObject.h>
#include <V3d/Vfs/IVStream.h>
#include <V3d/XML/IVXMLWriter.h>
#include <V3d/XML/IVXMLVisitor.h>
#include <V3d/Core/SmartPtr/VGuards.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>
#include <V3d/Core/SmartPtr/VSharedPtr.h>
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
	typedef VSharedPtr<v3d::xml::IVXMLWriter> IVXMLWriterPtr;
	typedef VSharedPtr<v3d::vfs::IVStream> IVStreamPtr;
	typedef VSharedPtr<v3d::xml::IVXMLElement> IVXMLElementPtr;

	/**
	 * Parses an xml file through an IVStream. Returns the root node of
	 * the xml tree.
	 *
	 * @param in_pStream A vfs data stream that represents a xml file
	 * @author acrylsword
	 */
	virtual VSharedPtr<IVXMLElement> GetRootElement(vfs::IVStream* in_pStream) = 0; 

	/**
	* Parses an xml file through the local file system. Returns the root
	* node of the xml tree.
	*
	* @param in_strName The file to open
	* @author acrylsword
	*/
	virtual VSharedPtr<IVXMLElement> GetRootElement(VStringParam in_strName) = 0; 

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

	virtual VSharedPtr<IVXMLElement> CreateEmptyElement(VStringParam in_strName = 0) = 0;
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

typedef VServicePtr<IVXMLService> VXMLServicePtr;
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
template<>
inline v3d::xml::IVXMLService* v3d::QueryService<v3d::xml::IVXMLService>()
{
	return QueryObject<v3d::xml::IVXMLService>("xml.service");
}
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLSERVICE_H
