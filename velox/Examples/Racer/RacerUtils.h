#ifndef V3D_RACERUTILS_2004_10_12_H
#define V3D_RACERUTILS_2004_10_12_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------

// some useful functions (candidates for beeing moved to the velox lib)

IVStream::ByteCount GetSize(IVStream& in_Stream)
{
	V3D_ASSERT(in_Stream.GetLegalOps()->AllowPositioning());
	V3D_ASSERT(in_Stream.GetLegalOps()->AllowGetPosition());

	const IVStream::ByteCount originalPosition = in_Stream.GetPos();
	in_Stream.SetPos(IVStream::End, 0);
	const IVStream::ByteCount size = in_Stream.GetPos();
	in_Stream.SetPos(IVStream::Begin, originalPosition);

	return size;
}

template<typename VertexStructure>
typename VPointer< VHeightmapMesh<VertexStructure> >::SharedPtr LoadHeightmap(
	IVStream& in_Stream, vuint in_nSize)
{
	const vuint horSize = GetSize(in_Stream) / in_nSize;
	V3D_ASSERT(in_nSize * horSize == GetSize(in_Stream));

	VPointer< VHeightmapMesh<VertexStructure> >::SharedPtr	pHeightmap;
	pHeightmap.Assign(new VHeightmapMesh<VertexStructure>(in_nSize, horSize));

	pHeightmap->GenerateIndices();

	// set heightdata
	vbyte heightValue = 0;
	vfloat32 height = 0.0f;

	vfloat32 maxh = -100.0f;
	vfloat32 minh = 100.0f;

	for(vuint y = 0; y < in_nSize; ++y)
	for(vuint x = 0; x < in_nSize; ++x)
	{
		in_Stream >> heightValue;

		// scale to [0,1]
		height = vfloat32(heightValue) / 256.0f;
		height = 1 - height;

		maxh = std::max(maxh, height);
		minh = std::min(minh, height);
        
		pHeightmap->GetVertex(x, y).position.z = height;
	}

	return pHeightmap;
}

template<typename VertexStructure>
typename VPointer< VHeightmapMesh<VertexStructure> >::SharedPtr LoadHeightmap(
	VStringParam in_strFileName)
{
	// open file and get size
	VServicePtr<IVFileSystem> pFS;

	vfs::IVFileSystem::FileStreamPtr pStream = 
		pFS->OpenFile(in_strFileName, vfs::VReadAccess);

	const vuint nSize = pStream->GetSize();
	const vfloat32 fSizeLen = std::sqrt(vfloat32(nSize));
	const vuint nSizeLen = vuint(fSizeLen);

	if( nSizeLen * nSizeLen != nSize )
	{
		V3D_THROW(VTerrainGenException, 
			VString("raw file must have n^2 filesize") +
			" filename=" + in_strFileName +
			" size=" + nSize
			);
	}

	return LoadHeightmap<VertexStructure>(*pStream, nSizeLen);
}

//-----------------------------------------------------------------------------
#endif // V3D_RACERUTILS_2004_10_12_H
