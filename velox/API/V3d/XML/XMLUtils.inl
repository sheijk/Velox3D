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
