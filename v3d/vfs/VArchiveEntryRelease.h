#ifndef VArchiveEntryRelease_h
#define VArchiveEntryRelease_h

class VArchiveStream;

//! interface, used by VArchiveStream to notify VArchive when stream is closed
class VArchiveEntryRelease
{
	// only VArchiveStream may use this function
	friend VArchiveStream;
protected:
	virtual void ReleaseEntry(VArchiveStream* in_pStream) = 0;
};

#endif // VArchiveEntryRelease_h