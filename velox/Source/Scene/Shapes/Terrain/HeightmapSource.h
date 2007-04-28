#ifndef GEOMCLIP_HEIGHTMAPSOURCE_H_INCLUDE
#define GEOMCLIP_HEIGHTMAPSOURCE_H_INCLUDE

#include "Types.h"
#include "CommonMath.h"

namespace geomclip {

	typedef int WorldCoord;
	typedef int LodCoord;

	class HeightmapSource {
	public:
		virtual float heightAt(WorldCoord xWorld, WorldCoord yWorld) const;
		virtual Vector3f normalAt(WorldCoord xWorld, WorldCoord yWorld) const;
		virtual Vector3f vertexAt(WorldCoord xWorld, WorldCoord yWorld) const;
		virtual uint getSize() const;

		enum DataType {
			Byte4
		};

		static uint sizeOf( DataType dataType );

		/** Must return the same value everytime */
		virtual uint customDataCount() const;
		virtual DataType customDataType(uint index) const;
		virtual std::string customDataName(uint index) const;

		/**
		 * Calculate count elements and write them to destAddress
		 *
		 * write elementAt: (xStart,yStart) + n * (xStep, yStep)
		 * to: destAddress + n * sizeof(dataType)
		 *
		 * dataType must be type returned by customDataType(index)
		 */
		virtual void loadCustomData(
			uint index, 
			WorldCoord xStart, WorldCoord yStart,
			uint count,
			uint xStep, uint yStep,
			void* destAddress) const;

		//virtual u32 colorAt( WorldCoord x, WorldCoord y ) const = 0;
	};
}

#endif
