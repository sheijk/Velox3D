#ifndef V3D_VLOGMODEENUM_H
#define V3D_VLOGMODEENUM_H

namespace v3d {
namespace error {

	/**
	 * Different types of message logging.
	 */
	//TODO: muesste VLogMode heissen, weil nicht in einer Klasse
	enum LogMode {

		Ok,
		Warning,
		Error
	};

} //error
} //v3d

#endif