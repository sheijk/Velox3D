#ifndef VOPENFLAGS_H
#define VOPENFLAGS_H

namespace v3d_vfs {

enum VEResourceOpenFlags
{
	read_access = 1,
	write_access = 2
};

enum VEResMngrFlags
{
	mount_normal = 0,
	mount_readonly = 1
};

}; // namespace v3d_vfs

#endif