#ifndef GEOMCLIPMAP_COMPRESSEDHEIGHTMAPSOURCE_H_INCLUDE
#define GEOMCLIPMAP_COMPRESSEDHEIGHTMAPSOURCE_H_INCLUDE

#include "Types.h"
#include "HeightmapSource.h"

namespace geomclip {

	class Node;

	class CompressedHeightmapSource {
	private:
		Node* rootNode_;

	public:
		float heightAt(float x, float y);

		bool init( HeightmapSource* source );

		void print();
	};

}

#endif
