#include "VXMLTests.h"
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>
#include <V3d/XML/IVXMLService.h>
#include <V3d/VFS/IVStreamFactory.h>
#include <V3d/VFS/VStreamOps.h>
#include "VXMLVisitor.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace unittests{
using namespace v3d::xml;
//-----------------------------------------------------------------------------
VXMLTest::VXMLTest()
{
	IVTestManager* pTestManager = 0;

	// register unit test
	pTestManager = QueryObject<IVTestManager>("testmngr");
															
	if( ! pTestManager ) 
	{
		V3D_THROW(VException, "test manager could not be found");
	}

	pTestManager->AddCommonTest(this);
}
void VXMLTest::GetTestInfo(VString& out_TestName, 
						   VString& out_SubjectName)
{
	// set the name
	out_TestName = "XML Test";

	// specifiy the subject of the whole thing
	out_SubjectName = "xml testing";
}

void VXMLTest::ExecuteTest()
{
	IVXMLService* m_XmlService;
	VXMLVisitor m_TestVisitor;
	
	m_XmlService = QueryObject<IVXMLService>("xml.service");
	if( !m_XmlService)
		V3D_THROW(VException, "Service could not be quired!");
		
	IVXMLService::IVXMLWriterPtr m_XmlWriter;
	
	m_XmlWriter = m_XmlService->CreateXMLWriter("test.xml");
	m_XmlWriter->AddComment("This is a comment");
	m_XmlWriter->AddComment("This is a comment 2");
	m_XmlWriter->AddComment("This is a comment 3");
	m_XmlWriter->OpenElement("Service");
	m_XmlWriter->OpenElement("Element");
	m_XmlWriter->AddAttribute("dll","xml.dll");
	m_XmlWriter->AddAttribute("fgg","derst.dll");
	m_XmlWriter->CloseElement();
	m_XmlWriter->AddAttribute("fsdds","ss.dll");
	m_XmlWriter->OpenElement("Devices");
	m_XmlWriter->AddAttribute("Graphics","graphcs.dll");
	m_XmlWriter->CloseElement();
	m_XmlWriter->AddText("<!--This should be a comment too-->\n");
	m_XmlWriter->CloseElement();
	
	
	//Test one finished
	m_XmlWriter->~IVXMLWriter();

	m_XmlService->ParseLocalXMLFile("test.xml", &m_TestVisitor);
	
	IVStreamFactory* m_pStrFac;
	IVXMLService::IVStreamPtr m_pSmartPtr;
	{
		IVStreamFactory::FileStreamPtr ptr;
		m_pStrFac = QueryObject<IVStreamFactory>("vfs.strfact");

		if( ! m_pStrFac)
			V3D_THROW(VException, "Cannot load vfs stream factory!");

		ptr = m_pStrFac->CreateFileStream("test2.xml",
			VCreateAlways, VRWAccess);

		m_pSmartPtr.Assign(ptr.DropOwnership());
	}
		
	m_XmlWriter = m_XmlService->CreateXMLWriter(m_pSmartPtr);

	m_XmlWriter->OpenElement("Device");
	m_XmlWriter->AddComment("Second file test");
	m_XmlWriter->OpenElement("Graphics");
	m_XmlWriter->AddAttribute("Hi","toll");
	m_XmlWriter->AddComment("strange");
	m_XmlWriter->CloseElement();
	m_XmlWriter->CloseElement();
	
	m_pSmartPtr->SetPos(vfs::IVStream::Anchor::Begin, 0);
	m_XmlService->ParseXMLFile((IVStream*)m_pSmartPtr.Get(), &m_TestVisitor);
	
	
	m_XmlWriter.Release();
	
		
}

//-----------------------------------------------------------------------------
} //v3d
} // unittests