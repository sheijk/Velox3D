/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VINPUTPART_2006_02_12_H
#define V3D_VINPUTPART_2006_02_12_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VUnconnectedPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace input {
	class IVInputManager;
}}

namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VInputPart : public entity::VUnconnectedPart
{
public:
	VInputPart();
	virtual ~VInputPart();

	void SetInputManager(input::IVInputManager* in_pInputManager);
	input::IVInputManager* GetInputManager() const;
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

	virtual void Activate();
	virtual void Deactivate();
private:
	input::IVInputManager* m_pInputManager;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils

V3D_TYPEINFO_WITHPARENT(v3d::utils::VInputPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VINPUTPART_2006_02_12_H

