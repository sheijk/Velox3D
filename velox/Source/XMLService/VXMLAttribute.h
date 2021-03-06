/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VXMLATTRIBUTE_09_15_2004_H
#define V3D_VXMLATTRIBUTE_09_15_2004_H
//-----------------------------------------------------------------------------
#include <V3d/XML/IVXMLAttribute.h>
#include <V3d/Core/Wrappers/VString.h>
#include <V3d/Utils/VStringValue.h>
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * The XML attribute implementation
 * @author insane/acrylsword
 * @version 2.0
 */

class VXMLAttribute : public IVXMLAttribute
{
public:
	VXMLAttribute(VStringParam Name, VStringParam Value);

	virtual VStringRetVal GetName() const;
	virtual v3d::utils::VStringValue GetValue() const;
	virtual void SetValue(const v3d::utils::VStringValue& in_NewValue);
	
	void SetName(VStringParam Name);
	void SetValue(VStringParam Value);

private:
	VXMLAttribute();

	VString m_strName;
	v3d::utils::VStringValue m_Value;
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLATTRIBUTE_09_015_2004_H

