#ifndef V3D_VTEMPDATAPROVIDER_H
#define V3D_VTEMPDATAPROVIDER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Vfs/IVTempDataProvider.h>
#include <string>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Implementation of the IVTempDataProvider
 */

class VTempDataProvider : public IVTempDataProvider
{
public:
	VTempDataProvider();
	virtual ~VTempDataProvider();

	/**
	* Copies the buffer into a file on disc ind returns local file name
	* @param in_pBuffer: the buffer to be copied
	*        in_nBytes:  size to be copied
	*/

	VStringParam CreateFile(void* in_pBuffer, vuint in_nBytes);

	/**
	* Writes the stream into a binary flile
	*/
	VStringParam CreateFile(IVStream* in_pStream);

	/**
	* Returns an empty file name
	*/

	VStringParam CreateFile();

private:

	VStringParam GetFileName();
	void GetWorkDir();
	void DeleteFiles();

	enum PathSize
	{
		SizeWorkDir = 256,
	};

	vint m_nFileCount;
	std::string m_sWorkingDir;
	std::string m_sFilename;

	std::string m_sTempFileFolder;
	std::string m_sTempFileName;
	std::string m_sTempFileExtension;

	std::list<std::string> m_sFilelist;

};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTEMPDATAPROVIDER_H
