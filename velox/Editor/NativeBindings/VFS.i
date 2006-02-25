
%include "../../API/V3d/VFS/VFlags.h"
%include "../../API/V3d/VFS/IVAccessRights.h"
%include "../../API/V3d/VFS/VAccessRightsFlags.h"
%include "../../API/V3d/VFS/IVStream.h"
%include "../../API/V3d/VFS/IVOfflineStream.h"
%include "../../API/V3d/VFS/IVBufferStream.h"
%include "../../API/V3d/VFS/IVFileSysObject.h"
%template(VBufferStreamPtr) v3d::VSharedPtr<v3d::vfs::IVBufferStream>;
%include "../../API/V3d/VFS/IVFile.h"
%template(VFileIterator) v3d::VRangeIterator<v3d::vfs::IVFile>;
%template(VDirectoryIterator) v3d::VRangeIterator<v3d::vfs::IVDirectory>;
%ignore v3d::vfs::IVDirectory::Files() const;
%ignore v3d::vfs::IVDirectory::SubDirs() const;
%include "../../API/V3d/VFS/IVDirectory.h"
%include "../../API/V3d/VFS/IVLegalOperations.h"
%include "../../API/V3d/VFS/IVFileSystem.h"

