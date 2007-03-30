/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_INDOORCELL_2004_04_11_H
#define V3D_INDOORCELL_2004_04_11_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <v3dLib/Graphics/Portal/IVCell.h>
#include <V3dLib/Graphics/Generators/VBoxMesh.h>
#include <V3dLib/Graphics/Geometry/VSimpleVertex.h>
#include <V3dLib/Graphics/Geometry/VTexturedVertex.h>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VIndoorCell : public IVCell
{
public:
	VIndoorCell(IVDevice* in_pDevice);
	~VIndoorCell();
	
	virtual void Cull(VCamera* in_pCamera, VMultipassDrawList& in_DrawList) ;
	virtual void Hide(VMultipassDrawList& in_DrawList) ;

	//added later..
	void Show();

	void AddCell(IVCell* in_pCell);
	
private:
    
	typedef VPointer<VMatrix44f>::SharedPtr MatrixPtr;
	
	IVDevice* m_pDevice;
	v3d::graphics::VMultipassDrawList* m_pDrawList;

	VBoxMesh<VTexturedVertex>* m_pBox;
	VBoxMesh<VSimpleVertex>* m_pPortalBox;

	
	
	VModel* m_pModel;
	VModel* m_pModel2;

	//our list we are connecting this cell to another
	std::list<IVCell*> m_CellList;

	//flag indicating model is added to drawlist
	vbool m_bModelAdded;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_INDOORCELL_2004_04_11_H

