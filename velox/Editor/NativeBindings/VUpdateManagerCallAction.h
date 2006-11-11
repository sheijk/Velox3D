/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VUPDATEMANAGERCALLACTION_2006_11_11_H
#define V3D_VUPDATEMANAGERCALLACTION_2006_11_11_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Entity/VEntity.h>
#include <V3d/Entity/VUpdateablePart.h>

#include "IVFrameAction.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VUpdateManagerCallAction : public IVFrameAction
{
public:
	VUpdateManagerCallAction();

	virtual void Init();
	virtual void UpdateFrame(vfloat32 in_fFrameDuration);
	virtual void Shutdown();

	void SetEntity(v3d::entity::VEntity* in_pEntity);

	vfloat32 GetUpdateSpeedFactor() const { return m_fUpdateSpeedFactor; }
	void SetUpdateSpeedFactor(const vfloat32& in_Value) { m_fUpdateSpeedFactor = in_Value; }
private:
	v3d::entity::VUpdateManagerPart* m_pUpdateManager;
	vfloat32 m_fUpdateSpeedFactor;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VUPDATEMANAGERCALLACTION_2006_11_11_H

