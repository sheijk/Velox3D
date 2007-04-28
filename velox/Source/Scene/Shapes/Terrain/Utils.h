#ifndef GEOMCLIPTERRAIN_UTILS_H_INCLUDE
#define GEOMCLIPTERRAIN_UTILS_H_INCLUDE

#include "Types.h"
#include <string>

namespace geomclip {
    std::string loadFile(const std::string& fileName);
    void sendOrientationGrid();

	int mymod(int value, int mod);
	uint powi(uint b, uint e);
	int nextPowerOf( int n, int start );

	void glColorForDetailLevel(uint level);

	template<typename STLContainer>
	void deleteAll(STLContainer& elements) {
		const STLContainer::iterator elementsEnd = elements.end();

		for( STLContainer::iterator iter = elements.begin(); iter != elementsEnd; ++iter ) {
			delete *iter;
			*iter = NULL;
		}

		elements.clear();
	}
}

#endif
