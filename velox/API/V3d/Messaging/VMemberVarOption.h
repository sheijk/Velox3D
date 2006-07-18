#ifndef V3D_VMEMBERVAROPTION_2006_07_18_H
#define V3D_VMEMBERVAROPTION_2006_07_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A property/option which will be get/set by reading/writing a member
 * variable of the part. This circumvents the getter/setter functions
 * for it. The member option call only be created by the part itself
 * because access to the member variable is needed (which is intended)
 *
 * @author
 */
template<typename T>
class VMemberVarOption : public VOption
{
public:
	VMemberVarOption(const std::string& name, void* object, T* member) :
	  VOption(name)
	  {
		  m_nOffsetBytes = BytesDistance(object, member);
	  }

	  virtual void Write(const std::string& value, void* object)
	  {
		  T* address = MemberAddress(object);

		  utils::VStringValue val(value);
		  T newValue = val.Get<T>();
		  *address = newValue;
	  }

	  virtual std::string Read(void* object)
	  {
		  T* address = MemberAddress(object);

		  utils::VStringValue val;
		  val.Set(*address);
		  return val.Get<std::string>();
	  }

private:
	T* MemberAddress(void* object)
	{
		vbyte* objectAddress = reinterpret_cast<vbyte*>(object);
		vbyte* memberAddress = objectAddress + m_nOffsetBytes;
		return reinterpret_cast<T*>(memberAddress);
	}

	vuint BytesDistance(void* a, void* b)
	{
		return vuint((vbyte*)b - (vbyte*)a);
	}

	vuint m_nOffsetBytes;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------
#endif // V3D_VMEMBERVAROPTION_2006_07_18_H
