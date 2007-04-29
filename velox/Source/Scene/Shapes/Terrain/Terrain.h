#ifndef TERRAIN_H_200611_INCLUDED
#define TERRAIN_H_200611_INCLUDED
//------------------------------------------------------------------------------
#include "Types.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "HeightmapSource.h"

#include <vector>
#include <list>
#include <memory>

namespace geomclip {

	class LodRegion;

    /**
     * Terrain will be rendered in the x,z plane centered at origin
     */
    class Terrain {
    public:
        Terrain();
        /**
         * MUST be called for initialization
         * Separated from constructor because init requires
         * a valid OpenGL context + prior glewInit()
         */
		void init(HeightmapSource* heightmapSource);

		void setShaderSource(const std::string& vertexSource, const std::string& fragmentSource);

        void render();
        void update(float seconds);

        uint getSize() const;

        void tellCamera(const Orientation& cam);

		// debugging
		void invalidate();

		typedef uint HoleId;
		HoleId addHole(const Rect<WorldCoord>& area);
		/**
		 * The hole's border vertices depend on this. You will need to adjust
		 * your hole filling geometry to match the border vertices for the
		 * given detail level.
		 * The x and z coordinates of the border vertices are aligned at 2^n.
		 * This means that any for any border vertex x = x' * 2^n holds.
		 * The border rectangle's size is always >= the hole's size. This means
		 * that the border vertices are placed at the next aligned pos outside
		 * the hole (or on it's border)
		 *
		 * Returns 0 for invalid hole ids
		 */
		uint holeDetail(HoleId holeNum);
        
    private:
        Orientation camera_;
        std::vector<LodRegion*> regions_;
        Shader shader_;
		HeightmapSource* heightmapSource_;

		friend LodRegion;

		struct HoleInfo {
			Rect<WorldCoord> area;
			uint detailLevel;
		};

		typedef std::list< HoleInfo > RectList;
		RectList holes_;

		GLuint texture_;
		GLuint fakeMask_;

		/** requires shader_ to be bound */
		void renderHoleBorder(const HoleInfo& holeInfo);
		uint findDetailLevelForHoleBorder(const Rect<int>& hole);
		std::vector<Vector3f>* borderVertices_;
		void sendVertex(const Point<float>& v);
		void transitionStripes(const Point<float>& start, const Point<float>& end, int level, float width);

		std::string vertexShaderSource_;
		std::string fragmentShaderSource_;
    };

} // namespace terrain
//------------------------------------------------------------------------------
#endif

