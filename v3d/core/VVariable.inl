inline VVariable::VEVariableType VVariable::GetType(void)
{
	return m_Data.m_eType;
}

inline vbool VVariable::GetBool(void)
{
	return m_Data.m_Value.m_bValue;
}

inline vfloat32 VVariable::GetFloat(void)
{
	return m_Data.m_Value.m_fValue;
}

inline vint VVariable::GetInt(void)
{
	return m_Data.m_Value.m_iValue;
}

inline void* VVariable::GetPtr(void)
{
	return m_Data.m_Value.m_pValue;
}

inline VVariable& VVariable::operator = (const VVariable& in_rVariable)
{
	m_Data.m_eType = in_rVariable.m_Data.m_eType;
	m_Data.m_Value = in_rVariable.m_Data.m_Value;
	return (*this);
}

inline VVariable& VVariable::operator = (const vbool in_bValue)
{
	m_Data.m_eType = V3D_VARIABLE_TYPE_BOOL;
	m_Data.m_Value.m_bValue = in_bValue;
	return (*this);
}

inline VVariable& VVariable::operator = (const vfloat32 in_fValue)
{
	m_Data.m_eType = V3D_VARIABLE_TYPE_FLOAT;
	m_Data.m_Value.m_fValue = in_fValue;
	return (*this);
}

inline VVariable& VVariable::operator = (const vint in_iValue)
{
	m_Data.m_eType = V3D_VARIABLE_TYPE_INT;
	m_Data.m_Value.m_iValue = in_iValue;
	return (*this);
}

inline VVariable& VVariable::operator = (void* in_pValue)
{
	m_Data.m_eType = V3D_VARIABLE_TYPE_PTR;
	m_Data.m_Value.m_pValue = in_pValue;
	return (*this);
}

inline vbool VVariable::operator == (const VVariable& in_rVariable)
{
	return (m_Data == in_rVariable.m_Data);
}

inline vbool VVariable::operator == (const vbool in_bValue)
{
	if (m_Data.m_eType == V3D_VARIABLE_TYPE_BOOL &&
		m_Data.m_Value.m_bValue == in_bValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline vbool VVariable::operator == (const vfloat32 in_fValue)
{
	if (m_Data.m_eType == V3D_VARIABLE_TYPE_FLOAT &&
		m_Data.m_Value.m_fValue >= (in_fValue - FLT_EPSILON) &&
		m_Data.m_Value.m_fValue <= (in_fValue + FLT_EPSILON))
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline vbool VVariable::operator == (const vint in_iValue)
{
	if (m_Data.m_eType == V3D_VARIABLE_TYPE_INT &&
		m_Data.m_Value.m_iValue == in_iValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline vbool VVariable::operator == (void* in_pValue)
{
	if (m_Data.m_eType == V3D_VARIABLE_TYPE_PTR &&
		m_Data.m_Value.m_pValue == in_pValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline vbool VVariable::operator != (const VVariable& in_rVariable)
{
	return (m_Data != in_rVariable.m_Data);
}

inline vbool VVariable::operator != (const vbool in_bValue)
{
	if (m_Data.m_eType != V3D_VARIABLE_TYPE_BOOL)
	{
		return true;
	}

	if (m_Data.m_Value.m_bValue != in_bValue)
	{
		return true;
	}
	
	return false;
}

inline vbool VVariable::operator != (const vfloat32 in_fValue)
{
	if (m_Data.m_eType != V3D_VARIABLE_TYPE_FLOAT)
	{
		return true;
	}

	if (m_Data.m_Value.m_fValue < (in_fValue - FLT_EPSILON) ||
		m_Data.m_Value.m_fValue > (in_fValue + FLT_EPSILON))
	{
		return true;
	}
	
	return false;
}

inline vbool VVariable::operator != (const vint in_iValue)
{
	if (m_Data.m_eType != V3D_VARIABLE_TYPE_INT)
	{
		return true;
	}

	if (m_Data.m_Value.m_iValue != in_iValue)
	{
		return true;
	}
	
	return false;
}

inline vbool VVariable::operator != (void* in_pValue)
{
	if (m_Data.m_eType != V3D_VARIABLE_TYPE_PTR)
	{
		return true;
	}

	if (m_Data.m_Value.m_pValue != in_pValue)
	{
		return true;
	}
	
	return false;
}

inline vfloat32 VVariable::operator + (const vfloat32 in_fValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_FLOAT);
	return (m_Data.m_Value.m_fValue + in_fValue);
}

inline vfloat32 VVariable::operator - (const vfloat32 in_fValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_FLOAT);
	return (m_Data.m_Value.m_fValue - in_fValue);
}

inline vfloat32 VVariable::operator * (const vfloat32 in_fValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_FLOAT);
	return (m_Data.m_Value.m_fValue * in_fValue);
}

inline vfloat32 VVariable::operator / (const vfloat32 in_fValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_FLOAT);
	return (m_Data.m_Value.m_fValue / in_fValue);
}

inline vint VVariable::operator + (const vint in_iValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_INT);
	return (m_Data.m_Value.m_iValue + in_iValue);
}

inline vint VVariable::operator - (const vint in_iValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_INT);
	return (m_Data.m_Value.m_iValue - in_iValue);
}

inline vint VVariable::operator * (const vint in_iValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_INT);
	return (m_Data.m_Value.m_iValue * in_iValue);
}

inline vint VVariable::operator / (const vint in_iValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_INT);
	return (m_Data.m_Value.m_iValue / in_iValue);
}

inline VVariable& VVariable::operator += (const vfloat32 in_fValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_FLOAT);
	m_Data.m_Value.m_fValue += in_fValue;
	return (*this);
}

inline VVariable& VVariable::operator -= (const vfloat32 in_fValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_FLOAT);
	m_Data.m_Value.m_fValue -= in_fValue;
	return (*this);
}

inline VVariable& VVariable::operator *= (const vfloat32 in_fValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_FLOAT);
	m_Data.m_Value.m_fValue *= in_fValue;
	return (*this);
}

inline VVariable& VVariable::operator /= (const vfloat32 in_fValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_FLOAT);
	m_Data.m_Value.m_fValue /= in_fValue;
	return (*this);
}

inline VVariable& VVariable::operator += (const vint in_iValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_INT);
	m_Data.m_Value.m_iValue += in_iValue;
	return (*this);
}

inline VVariable& VVariable::operator -= (const vint in_iValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_INT);
	m_Data.m_Value.m_iValue -= in_iValue;
	return (*this);
}

inline VVariable& VVariable::operator *= (const vint in_iValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_INT);
	m_Data.m_Value.m_iValue *= in_iValue;
	return (*this);
}

inline VVariable& VVariable::operator /= (const vint in_iValue)
{
	V3DVERIFY(m_Data.m_eType == V3D_VARIABLE_TYPE_INT);
	m_Data.m_Value.m_iValue /= in_iValue;
	return (*this);
}