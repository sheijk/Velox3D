#ifndef V3D_VXmlIniReader_H
#define V3D_VXmlIniReader_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/XML/IVXMLVisitor.h>

#include <stack>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------
class VDirectory;

/**
 * parses the vfs's xml ini file and adds content to the given dir
 */
class VXmlIniReader : public xml::IVXMLVisitor
{
	VDirectory* m_pDestDir;

	enum State
	{
		Initial,
		Options,
		ParseFileSystem
	};

	State m_State;
	
	std::stack<VDirectory*> m_DirStack;
public:
	VXmlIniReader(VDirectory* in_pDestDir);
	virtual ~VXmlIniReader();

	virtual void OnElementClose(xml::IVXMLElement* Element);
	virtual void OnElementOpen(xml::IVXMLElement* Element);
	virtual void OnFileEnd();
	virtual void OnComment(VStringParam pText);
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VXmlIniReader_H
