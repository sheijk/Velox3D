#ifndef GEOMCLIP_STRETCHEDHEIGHTMAPSOURCE_H_INCLUDE
#define GEOMCLIP_STRETCHEDHEIGHTMAPSOURCE_H_INCLUDE

#include "RawHeightmapSource.h"
#include "Noise.h"

#include <V3d/Core/VException.h>

namespace geomclip {

	class StretchedHeightmapSource : public RawHeightmapSource {
		//std::auto_ptr<HeightmapSource> base_;
		float scaling_;

	public:
		StretchedHeightmapSource( 
			float scaling, 
			const char* fileName, 
			uint size, 
			uint bitdepth, 
			float maxHeight, 
			Endianness endian) 
			: RawHeightmapSource(fileName, size, bitdepth, maxHeight, endian)
		{
			scaling_ = scaling;
			//base_.reset( source );
		}

		virtual float heightAt(WorldCoord xWorld, WorldCoord yWorld) const {
			const float xbase = float(xWorld) / scaling_;
			const float ybase = float(yWorld) / scaling_;

			int xl = (int) xbase;
			if( xbase < 0.0f )
				--xl;
			const float xd = xbase - float(xl);
			int yl = (int) ybase;
			if( ybase < 0.0f )
				--yl;
			const float yd = ybase - float(yl);

			//-- cubic interpolation
			//float temps[4];
			//for( int y = 3; y >= 0; --y ) {
			//	float xtemps[4];
			//	for( int x = 3; x >= 0; --x ) {
			//		xtemps[x] = baseHeight( x + xl-1, y + yl-1 );
			//	}

			//	temps[y] = cubicInterpolate( xd, xtemps[0], xtemps[1], xtemps[2], xtemps[3] );
			//}

			//float h = cubicInterpolate( yd, temps[0], temps[1], temps[2], temps[3] );

			//-- bicubic interpolation
			float h = 0.0f;

			//h += baseHeight( xl - 1, yl - 1 ) * bicubicWeight( yd + 1 ) * bicubicWeight( xd + 1 );
			//h += baseHeight( xl - 1, yl + 0 ) * bicubicWeight( yd - 0 ) * bicubicWeight( xd + 1 );
			//h += baseHeight( xl - 1, yl + 1 ) * bicubicWeight( yd - 1 ) * bicubicWeight( xd + 1 );
			//h += baseHeight( xl - 1, yl + 2 ) * bicubicWeight( yd - 2 ) * bicubicWeight( xd + 1 );

			//h += baseHeight( xl + 0, yl - 1 ) * bicubicWeight( yd + 1 ) * bicubicWeight( xd - 0 );
			//h += baseHeight( xl + 0, yl + 0 ) * bicubicWeight( yd - 0 ) * bicubicWeight( xd - 0 );
			//h += baseHeight( xl + 0, yl + 1 ) * bicubicWeight( yd - 1 ) * bicubicWeight( xd - 0 );
			//h += baseHeight( xl + 0, yl + 2 ) * bicubicWeight( yd - 2 ) * bicubicWeight( xd - 0 );

			//h += baseHeight( xl + 1, yl - 1 ) * bicubicWeight( yd + 1 ) * bicubicWeight( xd - 1 );
			//h += baseHeight( xl + 1, yl + 0 ) * bicubicWeight( yd - 0 ) * bicubicWeight( xd - 1 );
			//h += baseHeight( xl + 1, yl + 1 ) * bicubicWeight( yd - 1 ) * bicubicWeight( xd - 1 );
			//h += baseHeight( xl + 1, yl + 2 ) * bicubicWeight( yd - 2 ) * bicubicWeight( xd - 1 );

			//h += baseHeight( xl + 2, yl - 1 ) * bicubicWeight( yd + 1 ) * bicubicWeight( xd - 2 );
			//h += baseHeight( xl + 2, yl + 0 ) * bicubicWeight( yd - 0 ) * bicubicWeight( xd - 2 );
			//h += baseHeight( xl + 2, yl + 1 ) * bicubicWeight( yd - 1 ) * bicubicWeight( xd - 2 );
			//h += baseHeight( xl + 2, yl + 2 ) * bicubicWeight( yd - 2 ) * bicubicWeight( xd - 2 );

			//for( int m = -1; m <= 2; ++m ) {
			//	const float xw = bicubicWeight( xd - m );

			//	const float f = 1.0f / 6.0f;
			//	float r = 0.0f;

			//	const float xp2 = yd + 2.0f;
			//	r += xp2 * xp2 * xp2;
			//	const float xp1 = yd + 1.0f;
			//	r -= 4.0f * xp1 * xp1 * xp1;
			//	h += baseHeight( xl + m, yl - 1 ) * r*f * xw;
			//	r += 6.0f * yd * yd * yd;
			//	h += baseHeight( xl + m, yl + 0 ) * r*f * xw;
			//	const float xm1 = yd - 1.0f;
			//	r -= 4.0f * xm1 * xm1 * xm1;
			//	h += baseHeight( xl + m, yl + 1 ) * r*f * xw;
			//	h += baseHeight( xl + m, yl + 2 ) * r*f * xw;
			//}

			for( int m = -1; m <= 2; ++m ) {
				const float xw = bicubicWeight( xd - m );

				h += baseHeight( xl + m, yl - 1 ) * bicubicWeight( yd + 1 ) * xw;
				h += baseHeight( xl + m, yl + 0 ) * bicubicWeight( yd - 0 ) * xw;
				h += baseHeight( xl + m, yl + 1 ) * bicubicWeight( yd - 1 ) * xw;
				h += baseHeight( xl + m, yl + 2 ) * bicubicWeight( yd - 2 ) * xw;
			}

			//for( int m = -1; m <= 2; ++m ) {
			//	const float xw = bicubicWeight( xd - m );

			//	h += baseHeight( xl + m, yl - 1 ) * bicubicWeight( yd + 1 ) * xw;
			//	h += baseHeight( xl + m, yl + 0 ) * bicubicWeight( yd - 0 ) * xw;
			//	h += baseHeight( xl + m, yl + 1 ) * bicubicWeight( yd - 1 ) * xw;
			//	h += baseHeight( xl + m, yl + 2 ) * bicubicWeight( yd - 2 ) * xw;
			//}

			//for( int m = -1; m <= 2; ++m ) {
			//	for( int n = -1; n <= 2; ++n ) {
			//		h += baseHeight( xl + m, yl + n ) * bicubicWeight( yd - n ) * bicubicWeight( xd - m );
			//	}
			//}

			//-- linear interpolation
			//float h1 = interpolate( xd, baseHeight(xbase, ybase), baseHeight(xbase+1, ybase) );
			//float h2 = interpolate( xd, baseHeight(xbase, ybase+1), baseHeight(xbase+1, ybase+1) );

			//float h = interpolate( yd, h1, h2 );

			//-- filtering. crap.. will always look like box filtering (all vertices in "quad" get the same value) :/
			//static const int filterSize = 4;
			//static float filterWeights[] = { 0.25f, 0.25f, 0.25f, 0.25f };
			//static int xOffsets[] =        { -1,    -1,     1,     1 };
			//static int yOffsets[] =        { -1,     1,     1,    -1 };

			//float h = 0.0f;

			//for( int i = filterSize - 1; i >= 0; --i ) {
			//	h += filterWeights[i] * baseHeight( xl + xOffsets[i], yl + yOffsets[i] );
			//}

			float n = noise( float(xWorld) * 0.9f, float(yWorld) * 0.9f, 0.0f ) * 0.8f;
			//float n = 0.0f;
			return h + n;
		}

		virtual uint customDataCount() const {
			return 2;
		}

		virtual DataType customDataType(uint index) const {
			return Byte4;
		}

		virtual std::string customDataName(uint index) const {
			if( index == 0 ) {
				return "colorTex";
			}
			else if( index == 1 ) {
				return "normals";
			}

			V3D_THROW(v3d::VException, "Invalid index");
			//return "colorTex";
		}

		virtual void loadCustomData(
			uint index, 
			WorldCoord xStart, WorldCoord yStart,
			uint count,
			uint xStep, uint yStep,
			void* destAddress) const
		{
			int x = xStart;
			int y = yStart;

			u32* dest = (u32*) destAddress;

			for( int i = count - 1; i >= 0; --i ) {
				*dest = customData( index, x, y );

				x += xStep;
				y += yStep;
				++dest;
			}
		}

	private:
		static u32 color(u8 red, u8 green, u8 blue, u8 alpha) {
			return
				(red << 0)
				+ (green << 8)
				+ (blue << 16)
				+ (alpha << 24);
		}

		u32 customData( uint index, WorldCoord x, WorldCoord y ) const {
			if( index == 0 ) {
				return colorAt( x, y );
			}
			else {
				return normal32At( x, y );
			}
		}

		static u8 unit2byte(float f) {
			return (f + 1.0f) * 0.5f * 255.0f;
		}

		u32 normal32At( WorldCoord x, WorldCoord y ) const {
			Vector3f normal = normalAt( x, y );
			//Vector3f normal( -1.f, 1.f, -1.f );
			return color( unit2byte(normal.x), unit2byte(normal.y), unit2byte(normal.z), 0 );
			//return color( 0, 255, 0, 0 );
		}

		u32 colorAt( WorldCoord x, WorldCoord y ) const {
			const float h = heightAt( x, y );
			const float percent = (h - minHeight_) / (maxHeight_ - minHeight_);

			//return color( 255, 128.0f + 128.0f * sin( float(x) * 2.0f * M_PI * 0.1f ), 255, 255 );
			//return color( sin(float(x) / 200.0f) * 255.0f, sin(float(y) / 200.0f) * 255.0f, 0.0f, 255.0f );

			return color( 255, 255, u8(percent * 255.0f), 255 );
		}

		inline float baseHeight( WorldCoord x, WorldCoord y ) const {
			if( x >= 0 && x < size_ && y >= 0 && y < size_ ) {
				return heightValues_[x + y*size_];
			}
			else {
				return 0.0f;
			}

			//return RawHeightmapSource::heightAt( x, y );
		}

		static float bicubicWeight( float x ) {
			using std::max;

			float r = 0.0f;

			const float xp2 = x + 2.0f;
			if( xp2 > 0.0f )
				r += xp2 * xp2 * xp2;

			const float xp1 = x + 1.0f;
			if( xp1 > 0.0f )
				r -= 4.0f * xp1 * xp1 * xp1;

			if( x > 0.0f )
				r += 6.0f * x * x * x;

			const float xm1 = x - 1.0f;
			if( xm1 > 0.0f )
				r -= 4.0f * xm1 * xm1 * xm1;

			r /= 6.0f;

			return r;

			//const float xp0 = max(0.0f, x);
			//const float xp1 = max(0.0f, x + 1.0f);
			//const float xp2 = max(0.0f, x + 2.0f);
			//const float xm1 = max(0.0f, x - 1.0f);

			//return (
			//	(xp2 * xp2 * xp2)
			//	- (4.0f * xp1 * xp1 * xp1)
			//	+ (6.0f * xp0 * xp0 * xp0)
			//	- (4.0f * xm1 * xm1 * xm1) ) / 6.0f;
		}
	};
}

#endif
