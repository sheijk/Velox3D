#include <Core/VVariable.h>

VVariable::VVariable(void)
{
	m_Data.m_eType = V3D_VARIABLE_TYPE_NONE;
}

VVariable::VVariable(const VVariable& in_rVariable)
{
	m_Data.m_eType = in_rVariable.m_Data.m_eType;
	m_Data.m_Value = in_rVariable.m_Data.m_Value;
}

VVariable::VVariable(const vbool in_bValue)
{
	m_Data.m_eType = V3D_VARIABLE_TYPE_BOOL;
	m_Data.m_Value.m_bValue = in_bValue;
}

VVariable::VVariable(const vfloat32 in_fValue)
{
	m_Data.m_eType = V3D_VARIABLE_TYPE_FLOAT;
	m_Data.m_Value.m_fValue = in_fValue;
}

VVariable::VVariable(const vint in_iValue)
{
	m_Data.m_eType = V3D_VARIABLE_TYPE_INT;
	m_Data.m_Value.m_iValue = in_iValue;
}

VVariable::VVariable(void* in_pValue)
{
	m_Data.m_eType = V3D_VARIABLE_TYPE_PTR;
	m_Data.m_Value.m_pValue = in_pValue;
}