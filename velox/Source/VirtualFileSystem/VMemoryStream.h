#ifndef V3D_VMEMORYSTREAM_H
#define V3D_VMEMORYSTREAM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVStream.h>
#include <v3d/Core/SmartPtr/VGuards.h>

#include <v3d/Core/SmartPtr/VArray.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

class VMemoryStream : public IVStream
{
private:
	/** all memory streams have the same access rights */
	static VPointer<IVLegalOperations>::AutoPtr s_pLegalOps;

	/** the buffer */
	VArray<vchar> m_Data;

	/** the current read/write position */
	StreamPos m_nRWPos;

	/** returns the size of the buffer */
	ByteCount GetSize() const;
public:
	VMemoryStream();

	VMemoryStream(ByteCount in_nInitialSize);

	virtual ~VMemoryStream();

	virtual void Write(void* in_pSource, ByteCount in_nByteCount);

	virtual void Read(void* out_pDest, ByteCount in_pBytesToRead);

	virtual void SetPos(Anchor in_Anchor, ByteCount in_nDistance);

	virtual StreamPos GetPos() const;

	virtual LegalOpsPtr GetLegalOps() const;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMEMORYSTREAM_H
