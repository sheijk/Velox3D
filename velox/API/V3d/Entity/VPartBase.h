#ifndef V3D_VPARTBASE_2005_07_30_H
#define V3D_VPARTBASE_2005_07_30_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VPartBase;

class VUntypedPartConnection
{
public:
	VUntypedPartConnection(
		IVPart::Location in_Location, 
		const std::string& in_Id, 
		VPartBase* in_pRegisterTo);

	void Disconnect();
	void Connect(
		IVPart::Location in_Location,
		const std::string& in_Id,
		IVPart& in_Part);

	const IVPart::Dependency& GetDependency() const;

	IVPart* GetPart() const;
protected:
	IVPart::Dependency m_Dependency;
	IVPart* m_pPart;
};

template<typename T>
class VPartConnection : public VUntypedPartConnection
{
public:
	VPartConnection(
		IVPart::Location in_Location, 
		const std::string& in_Id, 
		VPartBase* in_pRegisterTo);

	T* Get() const;
	T* operator->() const;
};

//-----------------------------------------------------------------------------

class VPartBase : public IVPart
{
	std::vector<VUntypedPartConnection*> m_Dependencies;

public:
	VPartBase();
	virtual ~VPartBase();

	virtual void Connect(
		Location in_Location, 
		const std::string& in_Id, 
		IVPart& in_Part);

	virtual void Disconnect(
		Location in_Location,
		const std::string& in_Id,
		IVPart& in_Part);

	virtual vbool IsReady() const;
	virtual vuint DependencyCount() const;
	virtual Dependency GetDependencyInfo(vuint in_nIndex) const;

private:
	void Register(VUntypedPartConnection& in_Connection);

	friend class VUntypedPartConnection;
};

//-----------------------------------------------------------------------------

template<typename T>
VPartConnection<T>::VPartConnection(
	IVPart::Location in_Location, 
	const std::string& in_Id, 
	VPartBase* in_pRegisterTo)
	:
	VUntypedPartConnection(in_Location, in_Id, in_pRegisterTo)
{
	m_pPart = 0;
}

template<typename T>
T* VPartConnection<T>::Get() const
{
	return reinterpret_cast<T*>(m_pPart);
}

template<typename T>
T* VPartConnection<T>::operator->() const
{
	return reinterpret_cast<T*>(m_pPart);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VPARTBASE_2005_07_30_H
