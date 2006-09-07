/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

template<typename T>
VStateParameter::VStateParameter(VStringParam in_strName, const T& in_Val)
{
	m_strName = in_strName;
	SetValue<T>(in_Val);
}

//-----------------------------------------------------------------------------

template<typename T>
vbool VState::GetParameter(VStringParam in_strName, T& out_Value) const
{
	if( ContainsParameter(in_strName) )
	{
		out_Value = GetParameterByName(in_strName).GetValue<T>();
		return true;
	}
	else
		return false;
}

template<typename T>
void VState::SetParameter(VStringParam in_strName, T in_Value)
{
	VStateParameter param(in_strName);
	param.SetValue<T>(in_Value);
	SetParameter(param);
}

