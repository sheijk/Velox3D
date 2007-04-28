#ifndef GEOMCLIPTERRAIN_DUMMYLODOBJECTS_H_INCLUDE
#define GEOMCLIPTERRAIN_DUMMYLODOBJECTS_H_INCLUDE

#include "VertexBuffer.h"
#include "Utils.h"
#include "CommonMath.h"

#include <vector>
#include <list>

namespace geomclip {
	class HeightmapSource;
	class Terrain;

	class LodObject {
		std::vector<VertexBuffer*> lodVertices;

		VertexBuffer* getSubArea(const Rect<int>& area, uint level, HeightmapSource* heightmapSource);

		friend class HoleFillers;
	public:
		LodObject( HeightmapSource* heightmapSource, const Rect<int>& area );

		~LodObject() {
			deleteAll( lodVertices );
		}
	};

	class HoleFillers {
		std::vector<LodObject*> objects;
		typedef std::list< Rect<int> > RectList;
		RectList holes_;

	public:
		~HoleFillers();
		void render( Terrain* terrain );

		void addLodRegion( HeightmapSource* heightmapSource, const Rect<int>& area );
	};
}

#endif
