#ifndef IVXMLSERVICE_H
#define IVXMLSERVICE_H

#include <v3d/Core/VNamedObject.h>
#include <v3d/Vfs/IVStream.h>
#include <v3d/XML/IVXMLWriter.h>
#include <V3d/XML/IVXMLVisitor.h>

namespace v3d{
namespace xml{

using namespace v3d::vfs;


class IVXMLService : public VNamedObject
{
protected:
	/**
	* a protected constructor is needed to pass the parameters to the 
	* VNamedObject constructor
	*/
	IVXMLService(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent)
	{
	}

public:
        
//	virtual void ParseXMLFile(IVStream* in_pStream, IVXMLVisitor* in_pVisitor) = 0;
	
	//TODO: sollte das vfs verwenden, bzw. ganz wegbleiben (sheijk)
	virtual void ParseXMLFile(VStringParam in_pcName, IVXMLVisitor* in_pVisitor) = 0;
	
	//TODO: die ivstream fkt brauchen wir (sheijk)
	//virtual IVXMLWriter* CreateXMLWriter(IVStream* in_pStream) = 0;

	//TODO: auf keine Fall einfach eine Ptr zurueckgeben, 
	// sondern einen SmartPointer verwenden, sonst gibts Speicherlecks (sheijk)
	virtual IVXMLWriter* CreateXMLWriter() = 0;
};

//TODO: } // namespace ..., ist besser lesbar (sheijk)
}
}

#endif
