
#define V3D_DEPRECATED

%include "../../API/V3d/Core/VTypes.h"
// %pragma(java) jniclassbase=%{java.lang.RuntimeException%}
%include "../../API/V3d/Core/VException.h"


%rename(Next) v3d::VRangeIterator::operator++();
%ignore v3d::VRangeIterator::operator++(int);
%rename(Equals) v3d::VRangeIterator::operator==;
%ignore v3d::VRangeIterator::operator!=;
%rename(SetTo) v3d::VRangeIterator::operator=;
%rename(Get) v3d::VRangeIterator::operator*;
%ignore v3d::VRangeIterator::operator->;
%include "VRangeIter.h"
%rename(Next) v3d::VRangeIterator<const std::string>::operator++;

%template(VStringIter) v3d::VRangeIterator<const std::string>;

// bind VStringValue and instantiate the Get<T> function for some common types
%include "../../API/V3d/Utils/VStringValue.h"
%extend v3d::utils::VStringValue {
	%template(ToString) Get<std::string>;
	%template(ToInt) Get<int>;
	%template(ToFloat) Get<float>;
};

%rename(Assign) v3d::VString::operator=;
%rename(toString) v3d::VString::operator const char*;
%ignore v3d::VString::operator<;
%ignore v3d::VString::operator!=;
%ignore operator+(const vchar* in_pcChar, const VString& in_VStr);
%ignore operator+(const VString& in_VStr, const vchar* in_pcChar);
%ignore operator==(const VString& left, const VString& right);
%ignore operator!=(const VString& left, const VString& right);
%ignore operator!=(const VString& left, VStringParam right);
%ignore operator!=(VStringParam left, const VString& right);
%rename(equals) v3d::VString::operator==;
%include "../../API/V3d/Core/Wrappers/VString.h"

%rename(Assign) v3d::VSharedPtr::operator=;
%include "VSharedPtr.h"
//%include "../../API/V3d/Core/SmartPtr/VSharedPtr.h"
%include "../../API/V3d/Core/SmartPtr/VGuards.h"

// the VTypeInfo header causes swig to crash...
namespace v3d {
	class VTypeInfo
	{
	public:
		std::string GetName() const;
	};
}

