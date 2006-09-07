/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVDOCUMENTCLASS_2004_06_18_H
#define V3D_IVDOCUMENTCLASS_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>

#include <V3d/Editor/IVDocument.h>

#include <wx/wx.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * A document defines a document type which can be edited in the editor.
 * It's used to create, open and save documents of it's type
 *
 * @author sheijk
 */
class IVDocumentClass
{
public:
	typedef VPointer<IVDocument>::SharedPtr DocumentPtr;

	/**
	 * Creates a new document. May return a null pointer indicating that
	 * the user aborted the operation. May open a dialog asking for some
	 * paramters for the document to be created
	 */
	virtual DocumentPtr Create(wxWindow* in_pParent) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_IVDOCUMENTCLASS_2004_06_18_H

