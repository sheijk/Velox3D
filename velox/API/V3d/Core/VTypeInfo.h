/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VTYPEINFO_2005_07_20_H
#define V3D_VTYPEINFO_2005_07_20_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <set>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * Provides a simple type info to decide whether a dynamic cast is possible
 * (Scroll down for usage info)
 *
 * @see v3d::InitTypeInfo<T>
 * @author sheijk
 */
class VTypeInfo
{
public:
	VTypeInfo();
	virtual ~VTypeInfo();

	std::string GetName() const;

	/** 
	 * Returns wheter an instance of the type the info represents can be
	 * safely casted to an instance of the type in_DestType represents
	 */
	vbool CanBeCastedTo(const VTypeInfo& in_DestType) const;
	vbool CanBeCastedTo(const std::string& in_TypeName) const;

	/**
	 * Returns whether the instance has been initialized using InitTypeInfo
	 */
	vbool IsInitialized() const;

	// functions to be called from InitTypeInfo:

	/** Adds T and T's super types to the list of super types */
	template<typename T> void AddSuperType();
	
	void SetName(const std::string& in_strName);


	vbool operator<(const VTypeInfo& other) const;
	vbool operator==(const VTypeInfo& other) const;
	vbool operator!=(const VTypeInfo& other) const;
private:
	void AddSuperType(const VTypeInfo& in_TypeInfo);

	std::set<std::string> m_SuperTypes;
	std::string m_strName;
};

/**
 * Returns the type info for type T. It will be constructed using the
 * function InitTypeInfo<T> which must be specialized for your own types
 */
template<typename T>
const VTypeInfo& GetTypeInfo();

/**
 * Returns the type info for type T. The type of T and thus the returned
 * type info will be determined at compile time. Thus you _cannot_ use this
 * function to get the type of an object at runtime. (Runtime type information
 * is not supported by VTypeInfo)
 */
template<typename T>
const VTypeInfo& GetCompileTimeTypeInfo(T* ptr);

/**
 * Initializes the type info for T. Must be specialized for every type to be
 * used with velox's type info system
 *
 * @Example
 <code>
 namespace v3d {
	class Parent {};
	class Child : public Parent {};
	class GrandChild : public Child {};
 } // namespace v3d

 // simples way (must be in global namespace!)
 V3D_TYPEINFO(v3d::Parent);
 V3D_TYPEINFO_WITHPARENT(v3d::Child, v3d::Parent);
 V3D_TYPEINFO_WITHPARENT(v3d::GrandChild, v3d::Child);

 // 'manual' way, use this if you need to provide more information than a name
 // and one parent type (for instance for types which inherit from multiple
 // other classes):

 template<>
 void InitTypeInfo<v3d::Parent>(VTypeInfo* out_pTypeInfo)
 {
 out_pTypeInfo->SetName("v3d::Parent");
 }

 template<>
 void InitTypeInfo<v3d::Child>(VTypeInfo* out_pTypeInfo)
 {
 out_pTypeInfo->SetName("v3d::Child");
 out_pTypeInfo->AddSuperType<Parent>();
 }

 template<>
 void InitTypeInfo<v3d::GrandChild>(VTypeInfo* out_pTypeInfo)
 {
 out_pTypeInfo->SetName("v3d::GrandChild");
 out_pTypeInfo->AddSuperType<Child>();
 }
 </code>
	
 See VFileName for a simple real world example
 */
template<typename T>
class InitTypeInfo
{
public:
	void operator()(VTypeInfo* out_pTypeInfo);
};

template<typename T>
class InitTypeInfo<const T>
{
public:
	void operator()(VTypeInfo* out_pTypeInfo)
	{
		InitTypeInfo<T>()(out_pTypeInfo);
	}
};

/** Use this for types which don't have a parent */
#define V3D_TYPEINFO(TheType) \
  namespace v3d { \
	template<> class InitTypeInfo<TheType>\
	{\
	public:\
		void operator()(VTypeInfo* out_pTypeInfo)\
		{\
			out_pTypeInfo->SetName(#TheType);\
		}\
	};\
  }

/**
 * Use this if your type has only one parent. TheParent must be the super
 * class of TheType
 */
#define V3D_TYPEINFO_WITHPARENT(TheType, TheParent) \
  namespace v3d { \
	template<> class InitTypeInfo<TheType>\
	{\
	public:\
		void operator()(VTypeInfo* out_pTypeInfo)\
			{\
				/* Check if TheType derives from TheParent*/\
				TheParent* p = static_cast<TheType*>(0);\
				/* use p to zero out warning */\
				p = 0;\
				\
				out_pTypeInfo->SetName(#TheType);\
				out_pTypeInfo->AddSuperType<TheParent>();\
			}\
	};\
  }

//-----------------------------------------------------------------------------

template<typename T>
const VTypeInfo& GetTypeInfo()
{
	static VTypeInfo typeInfo;

	if( ! typeInfo.IsInitialized() )
	{
		InitTypeInfo<T> x;
		x(&typeInfo);
	}

	return typeInfo;
}

template<typename T>
const VTypeInfo& GetCompileTimeTypeInfo(T* ptr)
{
	return GetTypeInfo<T>();
}

template<typename T>
void InitTypeInfo<T>::operator()(VTypeInfo* out_pTypeInfo)
{
	// in order for a type T to be used with velox's simple type info there
	// must be a specialization of InitTypeInfo<T> which constructs the 
	// VTypeInfo object. See example in declaration above (~ line 62ff)
	// This error will also occur if you try to get type info for a type
	// which has been forward declared only
	typeLacksGetTypeInfoSpecialization(new T);
}

template<typename T>
void VTypeInfo::AddSuperType()
{
	const VTypeInfo& superInfo = GetTypeInfo<T>();
	AddSuperType(superInfo);
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTYPEINFO_2005_07_20_H
