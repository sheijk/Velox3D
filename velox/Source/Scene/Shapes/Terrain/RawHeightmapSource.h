#ifndef GEOMCLIPTERRAIN_RAWHEIGHTMAPSOURCE_H_INCLUDE
#define GEOMCLIPTERRAIN_RAWHEIGHTMAPSOURCE_H_INCLUDE

#include "Utils.h"
#include "HeightmapSource.h"

#include <limits>
#include <stdio.h>
#include <vector>

namespace geomclip {
	class RawHeightmapSource : public HeightmapSource {
	public:
		enum Endianness { LittleEndian, BigEndian };

	protected:
		std::vector<float> heightValues_;
		uint size_;
		Endianness endianness_;
		float minHeight_;
		float maxHeight_;

	public:
		RawHeightmapSource() {
			size_ = 0;
			minHeight_ = maxHeight_ = 0;
		}

		RawHeightmapSource(const char* fileName, uint size, uint bitdepth, float maxHeight, Endianness endian) {
			size_ = size;
			endianness_ = endian;

			if( bitdepth == 16 ) {
				readFile<u16>( fileName, maxHeight );
			}
			else if( bitdepth == 8 ) {
				readFile<u8>( fileName, maxHeight );
			}
		}

		void init( uint size, const std::vector<float>& heights ) {
			heightValues_ = heights;
			size_ = size;
		}

		~RawHeightmapSource() {
		}

		void flip(u8* data, uint count) {
			u8* first = data;
			u8* last = data + count - 1;

			for( ; first < last; ++first, --last ) {
				u8 temp = *first;
				*first = *last;
				*last = temp;

				//std::swap( *first, *last );
			}
		}

		template<typename T>
		void readFile(const char* fileName, float maxHeight) {
			FILE* file = fopen( fileName, "r" );
			GCT_ASSERT( file != 0 );
			std::vector<T> data;
			data.resize( size_ * size_ );
			fread( &data[0], sizeof(T), size_ * size_, file);
			fclose( file );

			T minh = std::numeric_limits<T>::max();
			T maxh = std::numeric_limits<T>::min();

			const uint dataSize = data.size();
			for( uint i = 0; i < dataSize; ++i ) {
				T* pData = &data[i];

				if( endianness_ == BigEndian ) {
					flip( (u8*)pData, sizeof(T) );
				}

				maxh = std::max( maxh, *pData );
				minh = std::min( minh, *pData );
			}

			double range = maxh - minh;

			heightValues_.reserve( size_ * size_ );
			for( uint y = 0; y < size_; ++y ) {
				for( uint x = 0; x < size_; ++x ) {
					double height = data[x + y*size_];
					height -= minh;
					height *= maxHeight / range;
					heightValues_.push_back( height );
				}
			}

			minHeight_ = std::numeric_limits<T>::max();
			maxHeight_ = std::numeric_limits<T>::min();

			for( int i = heightValues_.size() - 1; i >= 0; --i ) {
				const float h = heightValues_[i];

				minHeight_ = std::min( minHeight_, h );
				maxHeight_ = std::max( maxHeight_, h );
			}
		}

		virtual float heightAt(WorldCoord xWorld, WorldCoord yWorld) const {
			//if( xWorld < 0 || xWorld >= size_ || yWorld < 0 || yWorld >= size_ ) {
			//	return 0.0f;
			//}
			//else {
			//	const uint index = yWorld * size_ + xWorld;

			//	return heightValues_[index];
			//}

			//const float centerDiff = sqrt( float(xWorld * xWorld + yWorld * yWorld) );

			xWorld = mymod( xWorld, 2 * size_ );
			if( xWorld >= size_ )
				xWorld = 2 * size_ - xWorld - 1;
			yWorld = mymod( yWorld, 2 * size_ );
			if( yWorld >= size_ )
				yWorld = 2 * size_ - yWorld - 1;

			const uint index = yWorld * size_ + xWorld;

			return heightValues_[index];
		}

		virtual uint getSize() const {
			return size_;
		}
	};
}
#endif
