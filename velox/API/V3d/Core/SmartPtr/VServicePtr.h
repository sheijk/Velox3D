#ifndef V3D_VSERVICEPTR_2004_04_24_H
#define V3D_VSERVICEPTR_2004_04_24_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d;

template<typename ServiceType>
ServiceType* QueryService()
{
	// create a template specialisation for QueryService for each service
	// in order to use VServicePtr
	ErrorTypeNotSupported();
}

/**
 * A smart pointer class for simplifying access to services
 * Overload the QueryService function with all types which shall be used
 * with VServicePtr
 *
 * @author sheijk
 */
template<typename ServiceType>
class VServicePtr
{
	ServiceType* m_pService;

	// copy kills service
	void operator=(const VServicePtr&);
	VServicePtr(const VServicePtr&);

public:
	VServicePtr()
	{
		// query service
		m_pService = QueryService<ServiceType>();
	}

	ServiceType* Get()
	{
		return m_pService;
	}

	const ServiceType* Get() const
	{
		return m_pService;
	}

	ServiceType& operator*()
	{
		return *Get();
	}

	const ServiceType& operator*() const
	{
		return *Get();
	}

	ServiceType* operator->()
	{
		return m_pService;
	}

	const ServiceType* operator->() const
	{
		return m_pService;
	}	
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSERVICEPTR_2004_04_24_H
