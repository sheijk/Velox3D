#include "HeightmapSource.h"
#include "CommonMath.h"

using namespace geomclip;

namespace {
	float distance(float x1, float y1, float x2, float y2) {
		return length(vector3f(x1, y1, 0.0f) - vector3f(x2, y2, 0.0f));
	}

	float f(float x, float y) {
		return std::sin(x / 10.0f) * std::cos(y / 10.0f);
	}

	float f2(float x, float y) {
		const float xn = fmodf(x, 100.0f) / 100.0f - 0.5f;
		const float yn = fmodf(y, 100.0f) / 100.0f - 0.5f;

		const float dist = length( vector3f(x, y, 0.0f) );

		return 0.5f + 0.5f * sin( 3.1415 * (dist - 0.5f) );
	}

	float heightAt(float x, float y) {
		Point<float> pos( x, y );

		float scale = 1.0f;
		float value = 0.0f;

		for(uint octave = 0; octave < 4; ++octave) {
			const float next = f( pos.x, pos.y );

			value += next * scale;

			scale *= 0.5f;
			pos *= 2.1f;
			pos = rotate( pos, M_PI * 1.234f );
		}

		return value;
	}
}

float geomclip::HeightmapSource::heightAt(WorldCoord xWorld, WorldCoord yWorld) const {
	//return 100 * sin( float(xWorld) / 100.0f );

	//if( abs(xWorld) < 32 )
	//	return 100.0f;
	//else
	//	return 10.0f;
	//return 0.0f;

	xWorld %= getSize();
	yWorld %= getSize();

	float h = 0.0f;

	const float centerDist = distance(xWorld, yWorld, getSize()/2, getSize()/2);
	const float range = getSize() * 7 / 16;
	if( centerDist <= range ) {
		const float cdnorm = 1.0f - centerDist / range;
		h += 250.0f * (0.5f + (0.5f * sin(3.1415 * (cdnorm - 0.5f))));
	}

	h += 2.0f * ::heightAt(xWorld, yWorld);

	return h;
}

uint geomclip::HeightmapSource::getSize() const {
	return 1010;
}

Vector3f geomclip::HeightmapSource::normalAt( WorldCoord xWorld, WorldCoord yWorld ) const
{
	Vector3f xdiff = vertexAt( xWorld - 1, yWorld ) - vertexAt( xWorld + 1, yWorld );
	Vector3f ydiff = vertexAt( xWorld, yWorld - 1 ) - vertexAt( xWorld, yWorld + 1 );

	Vector3f normal;
	cross( &normal, ydiff, xdiff );
	normalize( &normal );

	GCT_ASSERT( normal.y > 0.0f );
	return normal;
}

Vector3f geomclip::HeightmapSource::vertexAt( WorldCoord xWorld, WorldCoord yWorld ) const
{
	return Vector3f( xWorld, heightAt(xWorld, yWorld), yWorld );
}

uint HeightmapSource::customDataCount() const {
	return 0;
}

namespace {
	bool methodMayNotBeCalledCauseCountIs0 = false;
}

HeightmapSource::DataType HeightmapSource::customDataType(uint index) const {
	GCT_ASSERT( methodMayNotBeCalledCauseCountIs0 );
}

std::string HeightmapSource::customDataName(uint index) const {
	GCT_ASSERT( methodMayNotBeCalledCauseCountIs0 );
}

void HeightmapSource::loadCustomData(
	uint index, 
	WorldCoord xStart, WorldCoord yStart,
	uint count,
	uint xStep, uint yStep,
	void* destAddress) const
{
	GCT_ASSERT( methodMayNotBeCalledCauseCountIs0 );
}

uint HeightmapSource::sizeOf(DataType dataType) {
	switch( dataType ) {
		case Byte4:	return 4;
		default: return 0;
	}
}
