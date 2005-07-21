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
 *
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
	vbool CanBeCastedTo(const VTypeInfo& in_DestType);

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
//template<typename T>
//inline void InitTypeInfo(VTypeInfo* out_pTypeInfo);

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
	template<> class v3d::InitTypeInfo<TheType>\
	{\
	public:\
		void operator()(VTypeInfo* out_pTypeInfo)\
		{\
			out_pTypeInfo->SetName(#TheType);\
		}\
	};

/**
 * Use this if your type has only one parent. TheParent must be the super
 * class of TheType
 */
#define V3D_TYPEINFO_WITHPARENT(TheType, TheParent) \
	template<> class v3d::InitTypeInfo<TheType>\
	{\
	public:\
		void operator()(VTypeInfo* out_pTypeInfo)\
			{\
				/* Check if TheType derives from TheParent*/\
				TheParent* p = (TheType*)0;\
				\
				out_pTypeInfo->SetName(#TheType);\
				out_pTypeInfo->AddSuperType<TheParent>();\
			}\
	};

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
void InitTypeInfo<T>::operator()(VTypeInfo* out_pTypeInfo)
{
	// in order for a type T to be used with velox's simple type info there
	// must be a specialization of InitTypeInfo<T> which constructs the 
	// VTypeInfo object. See example in declaration
	typeLacksGetTypeInfoSpecialization();
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
