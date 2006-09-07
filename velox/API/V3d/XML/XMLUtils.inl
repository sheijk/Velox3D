/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

template<typename T>
vbool HasAttributeWithValue(
							IVXMLElement* in_pElement, 
							VStringParam in_strAttribName,
							const T& in_ExpectedValue)
{
	vbool result = false;

	try
	{
		IVXMLAttribute* pAttrib = in_pElement->GetAttribute(in_strAttribName);

		if( pAttrib != 0 )
		{
			result = pAttrib->GetValue().Get<T>() == in_ExpectedValue;
		}
	}
	catch(VException&)
	{}

	return result;
}

