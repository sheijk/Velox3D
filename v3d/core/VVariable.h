#ifndef V3D_VVARIABLE_H
#define V3D_VVARIABLE_H

#include <Core/VDebug.h>
#include <Core/VTypes.h>

#include <float.h>

class VVariable
{
public :

	enum VEVariableType
	{
		V3D_VARIABLE_TYPE_NONE,
		V3D_VARIABLE_TYPE_BOOL,
		V3D_VARIABLE_TYPE_FLOAT,
		V3D_VARIABLE_TYPE_INT,
		V3D_VARIABLE_TYPE_PTR
	};

protected :

	class VData
	{
	public :

		union VValue
		{
			vbool			m_bValue;
			vfloat32		m_fValue;
			vint			m_iValue;
			void*			m_pValue;
		};

		VValue m_Value;
		VEVariableType m_eType;

		inline vbool operator == (const VData& in_rData)
		{
			if (m_eType == in_rData.m_eType)
			{
				if (m_eType == V3D_VARIABLE_TYPE_BOOL &&
					m_Value.m_bValue == in_rData.m_Value.m_bValue)
				{
					return true;
				}
				else if (m_eType == V3D_VARIABLE_TYPE_FLOAT &&
					m_Value.m_fValue >= (in_rData.m_Value.m_fValue - FLT_EPSILON) &&
					m_Value.m_fValue <= (in_rData.m_Value.m_fValue + FLT_EPSILON))
				{
					return true;
				}
				else if (m_eType == V3D_VARIABLE_TYPE_INT &&
					m_Value.m_iValue == in_rData.m_Value.m_iValue)
				{
					return true;
				}
				else if (m_eType == V3D_VARIABLE_TYPE_PTR &&
					m_Value.m_pValue == in_rData.m_Value.m_pValue)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		inline vbool operator != (const VData& in_rData)
		{
			return (!(*this == in_rData));
		}
	};

	VData					m_Data;

public :

	VVariable(void);
	VVariable(const VVariable& in_rVariable);
	VVariable(const vbool in_bValue);
	VVariable(const vfloat32 in_fValue);
	VVariable(const vint in_iValue);
	VVariable(void* in_pValue);

	inline VEVariableType	GetType(void);
	inline vbool			GetBool(void);
	inline vfloat32			GetFloat(void);
	inline vint				GetInt(void);
	inline void*			GetPtr(void);

	inline VVariable& operator = (const VVariable& in_rVariable);
	inline VVariable& operator = (const vbool in_bValue);
	inline VVariable& operator = (const vfloat32 in_fValue);
	inline VVariable& operator = (const vint in_iValue);
	inline VVariable& operator = (void* in_pValue);

	inline vbool operator == (const VVariable& in_rVariable);
	inline vbool operator == (const vbool in_bValue);
	inline vbool operator == (const vfloat32 in_fValue);
	inline vbool operator == (const vint in_iValue);
	inline vbool operator == (void* in_pValue);

	inline vbool operator != (const VVariable& in_rVariable);
	inline vbool operator != (const vbool in_bValue);
	inline vbool operator != (const vfloat32 in_fValue);
	inline vbool operator != (const vint in_iValue);
	inline vbool operator != (void* in_pValue);

	inline vfloat32 operator + (const vfloat32 in_fValue);
	inline vfloat32 operator - (const vfloat32 in_fValue);
	inline vfloat32 operator * (const vfloat32 in_fValue);
	inline vfloat32 operator / (const vfloat32 in_fValue);

	inline VVariable& operator += (const vfloat32 in_fValue);
	inline VVariable& operator -= (const vfloat32 in_fValue);
	inline VVariable& operator *= (const vfloat32 in_fValue);
	inline VVariable& operator /= (const vfloat32 in_fValue);

	inline vint operator + (const vint in_iValue);
	inline vint operator - (const vint in_iValue);
	inline vint operator * (const vint in_iValue);
	inline vint operator / (const vint in_iValue);

	//
	// *** operator += ***
	//
	// Synopsis:
	//    - Adds an integer value to the value currently stored in this container.
	//
	// Inputs:
	//    - const vint in_iValue: The value which is being added to the value currently stored in this
	//		container.
	//
	// Returns:
	//    - VVariable&: A reference to the current object, making it possible to concatenate multiple
	//		operations.
	//
	// Notes:
	//    - Be sure that there is the right type stored in this container, otherwise you will get a runtime
	//		assertion failure. This functionality has been inserted for security reasons and to ease
	//		debugging.
	//
	// Example:
	//    - VVariable myVariable(13);
	//		myVariable += 7;
	//
	inline VVariable& operator += (const vint in_iValue);
	inline VVariable& operator -= (const vint in_iValue);
	inline VVariable& operator *= (const vint in_iValue);
	inline VVariable& operator /= (const vint in_iValue);
};

#include <Core/VVariable.inl>

#endif