/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VXmlIniReader_H
#define V3D_VXmlIniReader_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/XML/IVXMLVisitor.h>

#include <stack>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------
class VDirectory;
class IVDirectory;

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

	// 0 or m_DirStack.top (depending on m_DirStack.empty())
	IVDirectory* GetDirStackTop();

	std::stack<VDirectory*> m_DirStack;
public:
	VXmlIniReader(VDirectory* in_pDestDir);
	virtual ~VXmlIniReader();

	virtual void OnElementClose(xml::IVXMLElement* Element);
	virtual void OnElementOpen(xml::IVXMLElement* Element);
	virtual void OnFileEnd();
	virtual void OnComment(VStringParam pText);
	virtual void OnText(VStringParam pText);
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VXmlIniReader_H

