#ifndef V3D_VMEMORYSTREAM_H
#define V3D_VMEMORYSTREAM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVStream.h>
#include <v3d/Core/SmartPtr/VGuards.h>

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
	std::vector<vchar> m_Data;

	/** the current read/write position */
	StreamPos m_nRWPos;

	/** returns the size of the buffer */
	ByteCount GetSize() const;

	/** returns the address of byte in_nPos */
	vchar* GetAddressOfByte(ByteCount in_nPos);
public:
	VMemoryStream();

	explicit VMemoryStream(ByteCount in_nInitialSize);

	virtual ~VMemoryStream();

	virtual void Write(const void* in_pSource, ByteCount in_nByteCount);

	virtual ByteCount Read(void* out_pDest, ByteCount in_pBytesToRead);

	virtual void SetPos(Anchor in_Anchor, ByteCount in_nDistance);

	virtual StreamPos GetPos() const;

	virtual LegalOpsPtr GetLegalOps() const;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMEMORYSTREAM_H
