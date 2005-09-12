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

class VPartConnectionManager;

class VUntypedPartConnection
{
public:
	VUntypedPartConnection(
		VPartDependency::Location in_Location,
		const std::string& in_Id,
		VPartDependency::Condition in_Condition,
		VPartConnectionManager* in_pRegisterTo);

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
		VPartConnectionManager* in_pRegisterTo);

	VPartConnection(
		VPartDependency::Location in_Location,
		VPartConnectionManager* in_pRegisterTo);

	VPartConnection(
		VPartDependency::Location in_Location,
		VPartDependency::Condition in_Condition,
		VPartConnectionManager* in_pRegisterTo);

	VPartConnection(
		VPartDependency::Location in_Location,
		const std::string& in_Id,
		VPartDependency::Condition in_Condition,
		VPartConnectionManager* in_pRegisterTo);

	T* Get() const;
	T* operator->() const;

	vbool IsConnected() const { return m_pPart != 0; }
};

//-----------------------------------------------------------------------------

class VPartConnectionManager
{
	friend class VUntypedPartConnection;

	std::vector<VUntypedPartConnection*> m_Dependencies;

public:
	VPartConnectionManager();
	virtual ~VPartConnectionManager();

	void Connect(
		VPartDependency::Location in_Location, 
		const std::string& in_Id, 
		IVPart& in_Part);

	void Disconnect(
		VPartDependency::Location in_Location,
		const std::string& in_Id,
		IVPart& in_Part);

	vbool IsReady() const;
	vuint DependencyCount() const;
	VPartDependency GetDependencyInfo(vuint in_nIndex) const;

private:
	void Register(VUntypedPartConnection& in_Connection);
};

template<typename Parent>
class VPartBaseAdapter : public Parent
{
public:
	virtual void Connect(
		VPartDependency::Location in_Location, 
		const std::string& in_Id, 
		IVPart& in_Part)
	{
		m_ConnectionManager.Connect(in_Location, in_Id, in_Part);
	}

	virtual void Disconnect(
		VPartDependency::Location in_Location,
		const std::string& in_Id,
		IVPart& in_Part)
	{
		m_ConnectionManager.Disconnect(in_Location, in_Id, in_Part);
	}

	vbool IsReady() const { return m_ConnectionManager.IsReady(); }
	vuint DependencyCount() const { return m_ConnectionManager.DependencyCount(); }
	VPartDependency GetDependencyInfo(vuint in_nIndex) const
	{ return m_ConnectionManager.GetDependencyInfo(in_nIndex); }

protected:
	VPartConnectionManager* RegisterTo() { return &m_ConnectionManager; }

private:
	VPartConnectionManager m_ConnectionManager;

	void Register(VUntypedPartConnection& in_Connection) 
	{ m_ConnectionManager.Register(in_Connection); }

	friend class VUntypedPartConnection;
};

typedef VPartBaseAdapter<IVPart> VPartBase;
//-----------------------------------------------------------------------------

template<typename T>
VPartConnection<T>::VPartConnection(
	IVPart::Location in_Location, 
	const std::string& in_Id, 
	VPartConnectionManager* in_pRegisterTo)
	:
	VUntypedPartConnection(
		in_Location, 
		in_Id, 
		VPartDependency::Mandatory,
		in_pRegisterTo)
{
	m_pPart = 0;
}

template<typename T>
VPartConnection<T>::VPartConnection(
	VPartDependency::Location in_Location,
	VPartConnectionManager* in_pRegisterTo)
	:
	VUntypedPartConnection(
		in_Location, 
		T::GetDefaultId(), 
		VPartDependency::Mandatory,
		in_pRegisterTo)
{
	m_pPart = 0;
}

template<typename T>
VPartConnection<T>::VPartConnection(
	VPartDependency::Location in_Location,
	VPartDependency::Condition in_Condition,
	VPartConnectionManager* in_pRegisterTo) 
	:
	VUntypedPartConnection(
		in_Location, 
		T::GetDefaultId(), 
		in_Condition,
		in_pRegisterTo)
{
	m_pPart = 0;
}

template<typename T>
VPartConnection<T>::VPartConnection(
	VPartDependency::Location in_Location,
	const std::string& in_Id,
	VPartDependency::Condition in_Condition,
	VPartConnectionManager* in_pRegisterTo)
	:
	VUntypedPartConnection(
		in_Location,
		in_Id,
		in_Condition,
		in_pRegisterTo)
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
