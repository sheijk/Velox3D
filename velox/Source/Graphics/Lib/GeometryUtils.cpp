/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//-----------------------------------------------------------------------------
#include <V3d/Graphics/Geometry/VGeometryUtil.h>
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

//TODO: turn into proper class following velox conventions
template<typename T>
class scope_ptr
{
	T* ptr;

	void release()
	{
		if( ptr != 0 )
			delete ptr;
		ptr = 0;
	}

public:
	scope_ptr(T* t) : ptr(t) {}
	~scope_ptr() { release(); }

	void operator=(T* t)
	{
		Release();
		ptr = t;
	}

	T* operator->() { return ptr; }
	const T* operator->() const { return ptr; }
	T& operator*() { return *ptr; }
	const T& operator*() const { return *ptr; }

	T* drop() {
		T* t = ptr;
		ptr = 0;
		return t;
	}
};

VMeshDescription* CreateMeshDescription(
	VMeshDescription::GeometryType in_Primitives,
	const VVertexBuffer& in_VertexBuffer,
	const std::string& in_strVBResource,
	const std::string& in_strIndexResource)
{
	VVertexFormat format(in_VertexBuffer.GetFormat());

	scope_ptr<VMeshDescription> pMeshDescription(new VMeshDescription(format));

	pMeshDescription->SetGeometryType(in_Primitives);

	if( format.GetColorFormat().GetCount() > 0 )
	{
		pMeshDescription->SetColorResource(in_strVBResource);
	}

	if( format.GetCoordinateFormat().GetCount() > 0 )
	{
		pMeshDescription->SetCoordinateResource(in_strVBResource);
	}

	if( format.GetIndexFormat().GetCount() > 0 )
	{
		pMeshDescription->SetIndexResource(in_strIndexResource);
	}

	if( format.GetNormalFormat().GetCount() > 0 )
	{
		pMeshDescription->SetNormalResource(in_strVBResource);
	}

	for( vuint texcoord = 0; texcoord < format.GetTexCoordCount(); ++texcoord)
	{
		if( format.GetTexCoordFormat(texcoord).GetCount() > 0 )
		{
			pMeshDescription->SetTexCoordResource(texcoord, in_strVBResource);
		}
	}

	return pMeshDescription.drop();
}

VMeshDescription* CreateMeshDescription(
	VMeshDescription::GeometryType in_Primitives,
	const VVertexBuffer& in_VertexBuffer,
	const std::string& in_strVBResource)
{
	return CreateMeshDescription(
		in_Primitives,
		in_VertexBuffer,
		in_strVBResource,
		in_strVBResource);
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------

