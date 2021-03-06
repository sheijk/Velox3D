/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VXMLAttribute.h"
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * The private default constructor does nothing
 *
 *@author insane/acrylsword
 */
//VXMLAttribute::VXMLAttribute(void)
//{
//
//}

/**
 * This is the main constructor. It creates a XMLAttribute from an 
 * name and a string containing the value of this attribute. The 
 * conversion frome the value string to other data types is done by
 * <code>VStringValue</code>.
 *
 * @author ins/acrylsword
 * @version 2.0
 */
VXMLAttribute::VXMLAttribute(VStringParam in_strName, VStringParam in_strValue)
{
	m_strName = in_strName;
	m_Value = v3d::utils::VStringValue(in_strValue);
}

/**
 * Returns the name of this XMLAttribute.
 *
 * @return The name of the attribute.
 * @author ins/acrylsword
 */
VStringRetVal VXMLAttribute::GetName() const
{
	return m_strName;
}

/**
 * Returns the <code>VStringValue</code> of this XMLAttribute.
 *
 * @return VStringValue that can be used to convert the string 
 *		   attribute to any data format.
 * @see VStringValue#Get()
 * @see VStringValue#GetSafe()
 * @author acrylsword
 */
v3d::utils::VStringValue VXMLAttribute::GetValue() const
{
	return m_Value;
}

void VXMLAttribute::SetValue(const v3d::utils::VStringValue& in_NewValue)
{
	m_Value = in_NewValue;
}

/**
 * Sets the name of this XMLAttribute.
 *
 * @param in_strName The new name of this XMlAttribute
 * @author ins/acrylsword
 */
void VXMLAttribute::SetName(VStringParam in_strName)
{
	m_strName = in_strName;
}

/**
 * Sets a new string attribute of the VStringValue attribute.
 *
 * @param in_strValue The new string value
 * @author acrylsword
 */
void VXMLAttribute::SetValue(VStringParam in_strValue)
{
	m_Value = v3d::utils::VStringValue(in_strValue);
}

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
