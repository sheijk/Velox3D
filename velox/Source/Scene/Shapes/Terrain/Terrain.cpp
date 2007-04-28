#include "Terrain.h"
#include "OpenGL.h"
#include "CommonMath.h"
#include "Utils.h"
#include "DummyLodObjects.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <limits>
//------------------------------------------------------------------------------

using namespace geomclip;

namespace {
	const uint REGION_SIZE = 128;
	const u8 TEXTURE_MASK_OPAQUE = 1;
	const u8 TEXTURE_MASK_TRANSPARENT = 0;
	enum { LOD_LEVEL_COUNT = 8 };
}

namespace {
	void makeMultipleOf(int* num, int divisor) {
		*num -= mymod( *num, divisor );
	}

	int roundDown(int num, int divisor) {
		// dirty but saves a local var ;)
		makeMultipleOf( &num, divisor );
		return num;
	}

	int roundUp(int num, int divisor) {
		return roundDown(num-1, divisor) + divisor;
	}

	int prevLevelAlignedPos(int start, int level) {
		if( level <= 0 ) {
			return start;
		}
		else {
			int prev = prevLevelAlignedPos( start, level - 1 ) - 1;
			makeMultipleOf( &prev, powi(2, level) );
			return prev;
		}
	}

	int nextLevelAlignedPos(int start, int level) {
		if( level <= 0 ) {
			return start;
		}
		else {
			int prev = nextLevelAlignedPos( start, level - 1 ) + 1;
			makeMultipleOf( &prev, powi(2, level) );
			return prev + powi(2, level);
		}
	}

	void extendToMultipleOf(Rect<int>* rect, int n) {
		rect->left = roundDown( rect->left, n );
		rect->top = roundDown( rect->top, n );
		rect->right = roundUp( rect->right, n );
		rect->bottom = roundUp( rect->bottom, n );
	}

	void extendToMultipleOf(Rect<float>* rect, int n) {
		rect->left = roundDown( rect->left, n );
		rect->top = roundDown( rect->top, n );
		rect->right = roundUp( rect->right, n );
		rect->bottom = roundUp( rect->bottom, n );
	}

	Point<float> clipInto( const Point<float>& p, const Rect<float>& r ) {
		return Point<float>(
			std::min<float>( std::max<float>(p.x, r.left), r.right ),
			std::min<float>( std::max<float>(p.y, r.top), r.bottom ) );
	}

	Rect<float> outerBorderForBorderStrip(const Rect<int>& hole, uint coarsestLevel, uint borderLevel) {
		//Rect<float> regionBorder = Rect<float>(hole);
		Rect<int> regionBorder = Rect<int>(hole);
		extendToMultipleOf( &regionBorder, powi(2, coarsestLevel) );

		for( uint level = coarsestLevel; level > borderLevel; --level ) {
			regionBorder.extend( 1 );
			extendToMultipleOf( &regionBorder, powi(2, level) );
		}

		return Rect<float>(regionBorder);
	}

	void addRegularGridIndices(VertexBuffer* vb, uint width, uint height) {
		const uint indexCount = (height-1) * (width * 2 + 2);
		vb->setIndexCount(indexCount);

		// ???
		for(int i = 0; i < indexCount; ++i) {
			vb->setIndex(i, 64);
		}

		uint index = 0;
		for(uint y = 0; y < height-1; ++y) {
			for(uint x = 0; x < width; ++x) {
				vb->setIndex(index++, x + (y * width));
				vb->setIndex(index++, x + ((y+1) * width));
			}

			vb->setIndex(index++, (width-1) + ((y+1) * width));
			vb->setIndex(index++, 0 + ((y+1) * width));
		}

		if( index != indexCount ) {
			GEOMCLIP_ERROR("expected index count of " << indexCount << " got " << index);
		}
	}
}

//------------------------------------------------------------------------------

namespace geomclip {
	/**
	* Represents a clip region together with the active region
	* of the same level
	*/
	class LodRegion {
	public:
		LodRegion();
		virtual ~LodRegion();

		void init(HeightmapSource* source, Shader* shader, uint level, LodRegion* lowerLevel);

		/**
		* Assumes that the terrain shader is bound
		*/
		void render();
		void renderGap();
		//void renderHoleBorders();

		/** Tells region about a new center */
		void setCenter(WorldCoord xWorld, WorldCoord yWorld);

		/**
		* Fetches new data from heightmap source if
		* clip region != active region
		* @param maxLookups maximum number of allowed rows to fetch
		*/
		void update(uint maxLookups);

		Rect<int> getActiveRegion() const;

		/**
		* @param area in world coordinates
		*/
		void addHole(const Terrain::HoleInfo* area);

	private:
		// no copying (no implementation provided to get linker errors if one
		// of these functions will be called accidently)
		LodRegion(const LodRegion&);
		void operator=(const LodRegion&);

		void setHeight(WorldCoord xWorld, WorldCoord yWorld, float height, float heightNextLevel);
		int getBufferOffset(WorldCoord xWorld, WorldCoord yWorld) const;

		/**
		* Resizes the vector and fills it with pixel data.
		* Puts 0 for opaque areas and 1 for transparent.
		* Size is 2*regionSize_ ^2
		*/
		void clearTextureMask(std::vector<u8> &pixels);
		void buildTextureMask(
			std::vector<u8> &pixels, 
			uint firstHoleNum, 
			uint lastHoleNum);
		void updateMaskTexture(std::vector<u8>& pixels);

		/** 
		* holes_[0] is the region level_ - 1 
		* in world coordinates
		*/
		std::vector< const Terrain::HoleInfo* > holes_;
		//Rect<WorldCoord> lowerLevelRegion_;
		Terrain::HoleInfo lowerLevelRegion_;

		bool maskTextureUpdateRequired_;

		void calculateNormal(WorldCoord x, WorldCoord y);
		//void updateNormalTexture();

		//TODO: world/local coords?
		Vector3f getPosition(uint x, uint y) const;

		/** Level of the region. 0 is highest detail */
		uint level_;

		uint bufferWidth() const { return regionSize_ - 1; }
		uint regionSize_;

		/**
		* The region centered around the viewer which we would
		* like to render ideally
		*/            
		Rect<WorldCoord> desiredRegion_;

		/**
		* The region for which we fetched height values
		*/
		Rect<WorldCoord> updatedRegion_;

		/** Camera position */
		Point<WorldCoord> center_;

		/**
		* A vertex stream of two float elements, containing
		* the height and the height at level+1
		*/
		VertexStream* heights_;
		uint bufferOffset_;

		// xz components of the coords
		VertexStream* coords_;
		VertexStream* normals_;
		//std::vector<float> normalValues_;
		//GLuint normalTexture_;

		std::vector<uint> borderIndices_;

		HeightmapSource* heightmapSource_;

		VertexBuffer buffer_;
		Shader* shader_;
		Shader* borderShader_;
		GLuint maskTexture_;

		LodRegion* lowerLevel_;

		struct CustomDataTexture {
			GLuint texture;
			std::vector<u8> data;
			u32* dataU32;
			std::string name;
			uint size;
			HeightmapSource::DataType dataType;

			void init( uint size, const std::string& name, HeightmapSource::DataType dataType ) {
				this->size = size;
				this->name = name;
				this->dataType = dataType;

				data.resize( size * size * HeightmapSource::sizeOf(dataType) );
				dataU32 = (u32*) &data[0];

				memset( dataU32, 255, data.size() );

				//for( int y = size-1; y >= 0; --y ) {
				//	for( int x = size-1; x >= 0; --x ) {
				//		const uint index = 4 * (x + y*size);
				//		data[index+0] = 255.0f * ( 0.5f + 0.5f * sin( M_PI * 2.0f * float(x) * 0.04f ) );
				//		data[index+1] = 255;
				//		data[index+2] = 255;
				//		data[index+3] = 255;
				//	}
				//}

				//for( int y = 10; y >= 0; --y ) {
				//	for( int x = 20; x >= 0; --x ) {
				//		const uint index = 4 * (x + y*size);
				//		data[index+1] = 0.0f;
				//	}
				//}

				glGenTextures( 1, &texture );
				glBindTexture( GL_TEXTURE_2D, texture );

				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

				gluBuild2DMipmaps(
					GL_TEXTURE_2D,
					GL_RGBA,
					size, size,
					GL_RGBA,
					GL_UNSIGNED_BYTE, 
					dataU32 );
				glBindTexture( GL_TEXTURE_2D, 0 );
			}
		};

		std::vector<CustomDataTexture> customData_;

		void initCustomData() {
			const uint count = heightmapSource_->customDataCount();
			customData_.resize( count );

			for( uint i = 0; i < count; ++i ) {
				CustomDataTexture& cd( customData_[i] );

				cd.init( 
					REGION_SIZE, 
					heightmapSource_->customDataName(i),
					heightmapSource_->customDataType(i) );
			}
		}

		void updateCustomData( const Rect<WorldCoord>& area ) {
			const int levelScale = powi(2, level_);
			//Rect<WorldCoord> area = desiredRegion_;

			for( int dataIndex = customData_.size() - 1; dataIndex >= 0; --dataIndex ) {
				CustomDataTexture& tex( customData_[dataIndex] );

				//for( int yw = area.top; yw < area.bottom; yw += levelScale ) {
				//	const int xw = area.left;

				//	const int x = mymod( xw / levelScale, REGION_SIZE );
				//	const int y = mymod( yw / levelScale, REGION_SIZE );
				//	const int index = x + y * REGION_SIZE;

				//	//TODO: split up in two reads, because memory region is not necessary continuous..
				//	heightmapSource_->loadCustomData( dataIndex, xw, yw, area.width() / 2 / levelScale, 1, 0, tex.dataU32 + index );
				//}

				for( int yw = area.top; yw < area.bottom; yw += levelScale ) {
					for( int xw = area.left; xw < area.right; xw += levelScale ) {
						const int x = mymod( xw / levelScale, REGION_SIZE );
						const int y = mymod( yw / levelScale, REGION_SIZE );
						const int index = x + y * REGION_SIZE;

						heightmapSource_->loadCustomData( dataIndex, xw, yw, 1, 1, 0, tex.dataU32 + index );
					}
				}

				glBindTexture( GL_TEXTURE_2D, tex.texture );
				gluBuild2DMipmaps(
					GL_TEXTURE_2D,
					GL_RGBA,
					tex.size, tex.size,
					GL_RGBA,
					GL_UNSIGNED_BYTE, 
					tex.dataU32 );
			}
		}

		// shortcut for debugging purposes.. TODO: remove
		friend class Terrain;
	};
}

//------------------------------------------------------------------------------

geomclip::LodRegion::LodRegion() {
    level_ = 0;
    regionSize_ = REGION_SIZE;
    maskTexture_ = 0;
	//normalTexture_ = 0;
	bufferOffset_ = 0;
	lowerLevel_ = NULL;
	shader_ = NULL;
	borderShader_ = NULL;
}

geomclip::LodRegion::~LodRegion() {
	//releaseHoleBorderVBs();
}

void geomclip::LodRegion::init(HeightmapSource* source, Shader* shader, uint level, LodRegion* lowerLevel) {
    level_ = level;
    heightmapSource_ = source;
    shader_ = shader;
	borderShader_ = shader;
	lowerLevel_ = lowerLevel;

	const uint size = bufferWidth();
	const uint bufferSize = size * size;

    buffer_.setSize( bufferSize );
    coords_ = buffer_.addStream( "xz", 2 );
    normals_ = buffer_.addStream( Normals, 3, buffer_.getSize() * 2 );
    heights_ = buffer_.addStream( "height", 2, buffer_.getSize() * 2 );

    // setup vertices
    for(uint x = 0; x < size; ++x)
    for(uint y = 0; y < size; ++y) {
        const uint index = x + y * size;
        coords_->set2( index, x, y );
    }
    
	//for( uint i = 0; i < size * size * 2; ++i )
	//	heights_->set2( i, 50.0f, 50.0f );
	{
		setCenter( 0, 0 );
		const uint levelScale = powi(2, level_);
		for(WorldCoord y = desiredRegion_.top; y < desiredRegion_.bottom; y += levelScale) 
		for(WorldCoord x = desiredRegion_.left; x < desiredRegion_.right; x += levelScale) {
			float h = heightmapSource_->heightAt(x, y);
			//heights_->set2( index, h, 1.0f );
			//heights_->set2( (index + bufferSize) % (2 * bufferSize), h, 1.0f );
			//heights_->set2( index, -100.0f, -100.0f );
			setHeight( x, y, -100.0f, -100.0f );
		}
	}

	//buildNormals();

    //Vector3f up = vector3f(0.f, 1.f, 0.f);
    //for(uint xy = 0; xy < size; ++xy) {
    //    normals_->set3(xy + 0 * size, up);
    //    normals_->set3(xy + (size-1) * size, up);
    //    normals_->set3(0 + xy * size, up);
    //    normals_->set3((size-1) + xy * size, up);
    //}

    // setup indices
	addRegularGridIndices( &buffer_, size, size );

	// setup indices for border gap
	const uint triPerBorderCount = bufferWidth()/2;
	const uint firstBottomIndex = bufferWidth() * (bufferWidth()-1);
	borderIndices_.reserve( 4 * 3 * triPerBorderCount );
	for( uint xy = 0; xy < triPerBorderCount * 2; xy += 2 ) {
		// top
		borderIndices_.push_back( xy+0 );
		borderIndices_.push_back( xy+1 );
		borderIndices_.push_back( xy+2 );
	}
	for( uint xy = 0; xy < triPerBorderCount * 2; xy += 2 ) {
		// bottom
		borderIndices_.push_back( xy+0 + firstBottomIndex );
		borderIndices_.push_back( xy+1 + firstBottomIndex );
		borderIndices_.push_back( xy+2 + firstBottomIndex );
	}
	for( uint xy = 0; xy < triPerBorderCount * 2; xy += 2 ) {
		// left
		borderIndices_.push_back( (xy + 0) * bufferWidth() );
		borderIndices_.push_back( (xy + 1) * bufferWidth() );
		borderIndices_.push_back( (xy + 2) * bufferWidth() );
	}
	for( uint xy = 0; xy < triPerBorderCount * 2; xy += 2 ) {
		// right
		borderIndices_.push_back( (xy + 0) * bufferWidth() + bufferWidth() - 1 );
		borderIndices_.push_back( (xy + 1) * bufferWidth() + bufferWidth() - 1 );
		borderIndices_.push_back( (xy + 2) * bufferWidth() + bufferWidth() - 1 );
	}

	if( lowerLevel_ != NULL ) {
		lowerLevelRegion_.area = lowerLevel_->getActiveRegion();
		lowerLevelRegion_.detailLevel = level_ - 1;
	}
	else {
		lowerLevelRegion_.area = Rect<WorldCoord>( 0, 0, 0, 0 );
		lowerLevelRegion_.detailLevel = 0;
	}
	holes_.push_back( &lowerLevelRegion_ );

	//normalValues_.resize( bufferWidth() * bufferWidth() * 3 );

	//glGenTextures( 1, &normalTexture_ );
	//GCT_ASSERT( normalTexture_ != 0 );

	//glBindTexture( GL_TEXTURE_2D, normalTexture_ );

	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, 0.0f );
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 0.0f );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0 );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0 );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	//updateNormalTexture();
	//glBindTexture( GL_TEXTURE_2D, 0 );

	std::vector<u8> pixels;
	const uint textureSize = regionSize_ * 2;
	pixels.resize( textureSize * textureSize );
	//buildTextureMask(pixels);
	GCT_ASSERT( textureSize	* textureSize == pixels.size() );

    glGenTextures(1, &maskTexture_);
    GCT_ASSERT( maskTexture_ != 0 );

	glBindTexture(GL_TEXTURE_2D, maskTexture_);

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, 0.0f );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 0.0f );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0 );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0 );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		1,
		textureSize,
		textureSize,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		&pixels[0]);

	glBindTexture( GL_TEXTURE_2D, 0 );

	initCustomData();
}

void geomclip::LodRegion::clearTextureMask( std::vector<u8> &pixels ) 
{
	const u8* pixelsEnd = &pixels[0] + pixels.size();
	for( u8* pixel = &pixels[0]; pixel < pixelsEnd; ++pixel )
		*pixel = TEXTURE_MASK_OPAQUE;
}

void geomclip::LodRegion::buildTextureMask(
	std::vector<u8> &pixels, 
	uint firstHoleNum, 
	uint lastHoleNum )
{
	const int textureSize = regionSize_ * 2;
	const int levelScale = powi(2, level_);

	for( uint holeNum = firstHoleNum; holeNum <= lastHoleNum; ++holeNum ) {
		Rect<int> globalArea = holes_[holeNum]->area;
		const uint holeDetail = holes_[holeNum]->detailLevel;
		const uint holeScale = powi(2, holeDetail);

		Rect<int> localArea = globalArea;

		if( holeNum > 0 ) {
			localArea = Rect<int>( outerBorderForBorderStrip(localArea, holeDetail, level_) );
		}

		localArea.moveBy( -desiredRegion_.left, -desiredRegion_.top );

		localArea.left *= 2;
		localArea.left /= levelScale;
		localArea.right *= 2;
		localArea.right /= levelScale;
		localArea.top *= 2;
		localArea.top /= levelScale;
		localArea.bottom *= 2;
		localArea.bottom /= levelScale;

		u8* pixel = &pixels[0];
		for(int y = 0; y < textureSize; ++y)
		for(int x = 0; x < textureSize; ++x)
		{
			if( localArea.contains(x, y) )
				*pixel = TEXTURE_MASK_TRANSPARENT;

			++pixel;
		}
	}
}

void print3( VertexStream* vs ) {
	uint vertexCount = vs->getCount();
	GCT_LOG( vertexCount << " vertices\n" );
	for( uint vertexNum = 0; vertexNum < vertexCount; ++vertexNum ) {
		Vector3f v = vs->get3( vertexNum );
		GCT_LOG( v.x << ", " << v.y << ", " << v.z << "\n" );
	}
}

void geomclip::LodRegion::updateMaskTexture( std::vector<u8>& pixels )
{
	const uint textureSize = regionSize_ * 2;

	glBindTexture( GL_TEXTURE_2D, maskTexture_ );

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		1,
		textureSize,
		textureSize,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		&pixels[0]);
}

void LodRegion::addHole(const Terrain::HoleInfo* holeInfo) {
	holes_.push_back( holeInfo );
}

void geomclip::LodRegion::render() {
	const int INVALID_OFFSET = -1;

	//std::vector<u8> mask;
	//const uint textureSize = regionSize_ * 2;
	//mask.resize( textureSize * textureSize );

	//clearTextureMask( mask );
	//buildTextureMask( mask, 0, holes_.size()-1 );
	//updateMaskTexture( mask );

    //glColor4fv( colors + (4 * (level_ % colorCount)) );

	glBindTexture( GL_TEXTURE_2D, maskTexture_ );
	GLint maskLocation = glGetUniformLocation( shader_->program(), "mask" );
	glUniform1i( maskLocation, 0 );

	for( int dataIndex = customData_.size() - 1; dataIndex >= 0; --dataIndex ) {
		CustomDataTexture& tex( customData_[dataIndex] );
		
		const uint textureNum = 2 + dataIndex;
		const GLenum textureUnit = GL_TEXTURE0 + textureNum;
		GLint location = glGetUniformLocation( shader_->program(), tex.name.c_str() );
		if( location >= 0 ) {
			glActiveTexture( textureUnit );
			glBindTexture( GL_TEXTURE_2D, tex.texture );
			glActiveTexture( GL_TEXTURE0 );

			glUniform1i( location, textureNum );
		}
	}

	const float levelScale = powi( 2, level_ );

	GLint offsetLocation = glGetUniformLocation( shader_->program(), "groundOffset" );
	//GCT_ASSERT( offsetLocation != INVALID_OFFSET );
	Point<float> offset = Point<float>( updatedRegion_.topleft() );
	offset *= 1.0f / (float(REGION_SIZE) * levelScale);
	//TODO: fuer normalen: x - REGION_SIZE-1, y - ?
	//offset.x *= 1.0f / (float(REGION_SIZE-1) * levelScale);
	//offset.x = mymod( offset.x, 1.0f );
	//offset.y = mymod( offset.y, 1.0f );
	glUniform2f( offsetLocation, offset.x, offset.y );
	//glUniform2f( offsetLocation, 0.5f, 0.1f );

	GLint scaleLocation = glGetUniformLocation( shader_->program(), "groundScale" );
	//GCT_ASSERT( scaleLocation != INVALID_OFFSET );
	glUniform1f( scaleLocation, levelScale );

	//glActiveTexture( GL_TEXTURE2 );
	//glBindTexture( GL_TEXTURE_2D, normalTexture_ );
	//glActiveTexture( GL_TEXTURE0 );
	//GLint normalLocation = glGetUniformLocation( shader_->program(), "normals" );
	//GCT_ASSERT( normalLocation != INVALID_OFFSET );
	//glUniform1i( normalLocation, 2 );

    buffer_.send( GL_TRIANGLE_STRIP, shader_->program() );
}

void geomclip::LodRegion::renderGap() {
	buffer_.bindStreams( borderShader_->program() );
	glDrawElements( GL_TRIANGLES, borderIndices_.size(), GL_UNSIGNED_INT, &borderIndices_[0] );
	buffer_.unbindStreams( borderShader_->program() );
}


void vertexQuad(const Rect<float>& area, float y = 0.0f) {
	glVertex3f( area.left, y, area.top );
	glVertex3f( area.right, y, area.top );
	glVertex3f( area.right, y, area.bottom );
	glVertex3f( area.left, y, area.bottom );
}
//
//void geomclip::LodRegion::renderHoleBorders() {
//	glBegin( GL_QUADS );
//
//	for( uint holeNum = 1; holeNum < holes_.size(); ++holeNum ) {
//		const Rect<WorldCoord>& hole = *holes_[holeNum];
//
//		vertexQuad( Rect<float>(hole), level_ * 3.0f );
//	}
//
//	glEnd();
//}

/*
void geomclip::LodRegion::renderHoleBorders() {
	const uint borderCount = holeBorders_.size();
	for( uint borderNum = 0; borderNum < borderCount; ++borderNum ) {
		Rect<WorldCoord> area = *holes_[borderNum+1];

		if( ! area.intersection(updatedRegion_).isEmpty() &&
			! area.isInside(lowerLevelRegion_) ) 
		{
			VertexBuffer* vb = holeBorders_[borderNum];
			vb->send( GL_TRIANGLES, shader_->program() );
		}
	}
}
*/

void geomclip::LodRegion::setCenter(WorldCoord xWorld, WorldCoord yWorld) {
	const uint levelOffset = powi( 2, level_ + 1 );
	const int halfSize = regionSize_ * powi(2, level_) / 2;

	center_.set( xWorld, yWorld );
	desiredRegion_.set( 
		xWorld - halfSize, 
		yWorld - halfSize, 
		xWorld + halfSize - levelOffset, 
		yWorld + halfSize - levelOffset);

	const int xdiff = xWorld % levelOffset;
	const int ydiff = yWorld % levelOffset;
	GCT_ASSERT( xdiff >= 0 );
	GCT_ASSERT( xdiff < levelOffset );
	GCT_ASSERT( ydiff >= 0 );
	GCT_ASSERT( ydiff < levelOffset );
	desiredRegion_.moveBy( -xdiff, -ydiff );
}

geomclip::Rect<int> geomclip::LodRegion::getActiveRegion() const {
    return desiredRegion_;
}

int lookupCount = 0;

void geomclip::LodRegion::update(uint maxLookups) {
	bool updateMask = maskTextureUpdateRequired_;

	if( lowerLevel_ != NULL ) {
		Rect<WorldCoord> oldLowerLevelRegion = lowerLevelRegion_.area;
		lowerLevelRegion_.area = lowerLevel_->getActiveRegion();

		if( oldLowerLevelRegion != lowerLevelRegion_.area ) {
			updateMask = true;
		}
	}

	if( updatedRegion_ != desiredRegion_ )
		updateMask = true;

	if( updateMask ) {
		std::vector<u8> mask;
		const uint textureSize = regionSize_ * 2;
		mask.resize( textureSize * textureSize );

		clearTextureMask( mask );
		buildTextureMask( mask, 0, holes_.size()-1 );
		updateMaskTexture( mask );

		maskTextureUpdateRequired_ = false;
	}

	if( updatedRegion_ != desiredRegion_ ) {
		const uint levelScale = powi(2, level_);
		const uint bufferSize = bufferWidth() * bufferWidth();

		int bo = mymod( getBufferOffset(desiredRegion_.left, desiredRegion_.top), bufferSize );
		bufferOffset_ = bo;

		Rect<int> newAreas[2];
		desiredRegion_.minus( updatedRegion_, &newAreas[0], &newAreas[1] );

		for(int areaNum = 0; areaNum < 2; ++areaNum) {
			Rect<int>& area( newAreas[areaNum] );
			makeMultipleOf( &area.left, levelScale );
			makeMultipleOf( &area.top, levelScale );

			lookupCount += area.width() / levelScale * area.height() / levelScale;

			if( ! area.empty() )
			for( int y = area.top; y <= area.bottom; y += levelScale )
			for( int x = area.left; x <= area.right; x += levelScale ) {
				const float h = heightmapSource_->heightAt(x, y);
				const uint index = getBufferOffset( x, y );

				float hn = h;
				if( lowerLevel_ != 0 ) {
					float hnx = h;
					float hny = h;

					//if( ((x-desiredRegion_.left) / levelScale) % 2 == 1 ) {
					if( (x / levelScale) % 2 == 1 ) {
						float hnxp = heightmapSource_->heightAt( x+levelScale, y );
						float hnxn = heightmapSource_->heightAt( x-levelScale, y );
						hn = (hnxp + hnxn) / 2.0f;
					}
					else if( (y / levelScale) % 2 == 1 ) {
						float hnyp = heightmapSource_->heightAt( x, y+levelScale );
						float hnyn = heightmapSource_->heightAt( x, y-levelScale );
						hn = (hnyp + hnyn) / 2.0f;
					}
				}

				setHeight( x, y, h, hn );
				calculateNormal( x, y );
			}

			//updateCustomData( area );
		}

		updateCustomData( desiredRegion_ );

		heights_->setFirstElementNum( bufferOffset_ );
		normals_->setFirstElementNum( bufferOffset_ );

		updatedRegion_ = desiredRegion_;

		//for( int y = desiredRegion_.top; y <= desiredRegion_.bottom; y += levelScale )
		//for( int x = desiredRegion_.left; x <= desiredRegion_.right; x += levelScale ) {
		//	calculateNormal(x, y);
		//}
		//updateNormalTexture();
	}
}

//void geomclip::LodRegion::buildNormals() {
//	for(uint y = 0; y < bufferWidth(); ++y)
//	for(uint x = 0; x < bufferWidth(); ++x) {
//		calculateNormal(x, y);
//	}
//}

//void geomclip::LodRegion::updateNormalTexture() {
//	glBindTexture( GL_TEXTURE_2D, normalTexture_ );
//
//	glTexImage2D(
//		GL_TEXTURE_2D,
//		0,
//		GL_RGB16F_ARB,
//		bufferWidth(), bufferWidth(),
//		0,
//		GL_RGB,
//		GL_FLOAT,
//		&normalValues_[0]);
//}

void geomclip::LodRegion::calculateNormal( WorldCoord xWorld, WorldCoord yWorld )
{
	const int levelScale = powi( 2, level_ );

	Vector3f xdiff = heightmapSource_->vertexAt( xWorld - levelScale, yWorld )
		- heightmapSource_->vertexAt( xWorld + levelScale, yWorld );
	Vector3f ydiff = heightmapSource_->vertexAt( xWorld, yWorld - levelScale )
		- heightmapSource_->vertexAt( xWorld, yWorld + levelScale );

	Vector3f normal;
	cross( &normal, ydiff, xdiff );
	//float oldY = normal.y;
	//scale( &normal, levelScale );
	//normal.y = oldY;

	const uint bufferSize = bufferWidth() * bufferWidth();
	const uint index = mymod( getBufferOffset(xWorld, yWorld), bufferSize );
	//const uint index = x + y * bufferWidth();
	normals_->set3( index, normal );
	normals_->set3( index + bufferSize, normal );
}

Vector3f geomclip::LodRegion::getPosition( uint x, uint y ) const
{
	const uint index = x + y * bufferWidth();
	Vector3f pos = coords_->get3( index );
	pos.z = pos.y;
	pos.y = heights_->get( index + bufferOffset_ );

	return pos;
}

int geomclip::LodRegion::getBufferOffset( WorldCoord xWorld, WorldCoord yWorld ) const
{
	const int levelOffset = powi( 2, level_ );
	const LodCoord xLod = xWorld / levelOffset;
	const LodCoord yLod = yWorld / levelOffset;
	return xLod + yLod * bufferWidth();
}

void geomclip::LodRegion::setHeight( WorldCoord xWorld, WorldCoord yWorld, float height, float heightNextLevel )
{
	const uint bufferSize = bufferWidth() * bufferWidth();
	const int index = mymod( getBufferOffset(xWorld, yWorld), bufferSize );

	heights_->set2( index, height, heightNextLevel );
	heights_->set2( index + bufferSize, height, heightNextLevel );
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

geomclip::Terrain::Terrain() {
}

geomclip::Terrain::HoleId geomclip::Terrain::addHole(const Rect<WorldCoord>& area) {
	HoleInfo holeInfo;
	holeInfo.area = area;
	holeInfo.detailLevel = 0;

	holes_.push_back( holeInfo );

	const uint regionsCount = regions_.size();
	for( uint regionNum = 0; regionNum < regionsCount; ++regionNum ) {
		regions_[regionNum]->addHole( &holes_.back() );
	}

	return holes_.size() - 1;
}

uint geomclip::Terrain::holeDetail(HoleId holeNum) {
	RectList::const_iterator holeIter = holes_.begin();
	std::advance( holeIter, holeNum );

	if( holeIter != holes_.end() ) {
		return holeIter->detailLevel;
	}
	else {
		return 0;
	}
}

void geomclip::Terrain::setShaderSource(const std::string& vertexSource, const std::string& fragmentSource)
{
	vertexShaderSource_ = vertexSource;
	fragmentShaderSource_ = fragmentSource;
}

void geomclip::Terrain::init(HeightmapSource* heightmapSource) {
	//heightmapSource.reset( new RawHeightmapSource("../volcanic_1025_16.raw", 1025, 16, 100.0f) );
	heightmapSource_.reset( heightmapSource );
	//heightmapSource_.reset( new RawHeightmapSource("../bitmap", 6000, 16, 3.0f) );
	//heightmapSource_.reset( new RawHeightmapSource("../terrains/island_1025_8.raw", 1025, 8, 10.0f) );
	//heightmapSource_.reset( new RawHeightmapSource("../terrains/island_8193_8.raw", 8193, 8, 100.0f) );
	//heightmapSource_.reset( new HeightmapSource() );

	if( vertexShaderSource_.length() == 0 || fragmentShaderSource_.length() == 0 ) {
		shader_.loadFiles("terrain.vert", "terrain.frag");
	}
	else {
		shader_.setSource( vertexShaderSource_, fragmentShaderSource_ );
	}

    for(int i = 0; i < LOD_LEVEL_COUNT; ++i) {
		regions_.push_back( new LodRegion() );
	}

	LodRegion* lowerLevel = NULL;
	const int regionsSize = regions_.size();
	for( int i = 0; i < regionsSize; ++i ) {
		LodRegion* r = regions_[i];

        r->init( heightmapSource_.get(), &shader_, i, lowerLevel );

		lowerLevel = r;
    }

	glGenTextures( 1, &fakeMask_ );
	glBindTexture( GL_TEXTURE_2D, fakeMask_ );
	//u8 opaque = TEXTURE_MASK_OPAQUE;
	u8 opaque = 255;
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		1,
		1, 1,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		&opaque);

	glGenTextures( 1, &texture_ );
	glBindTexture( GL_TEXTURE_2D, texture_ );
	//GCT_ASSERT( GL_TRUE == glfwLoadTexture2D("../grass.tga", GLFW_BUILD_MIPMAPS_BIT) );
}

void sendHLines(Point<float> start, Point<float> end, float height, uint count) {
	Point<float> step = (end - start) / float(count);

	glBegin(GL_LINES);

	glVertex3f( start.x, -height, start.y );
	glVertex3f( start.x, height, start.y );

	glVertex3f( end.x, -height, end.y );
	glVertex3f( end.x, height, end.y );

	Point<float> p = start;
	for(uint i = 0; i < count; ++i) {
		glVertex3f( p.x, -height, p.y );
		glVertex3f( p.x, height, p.y );

		p = p + step;
	}

	glEnd();
}

void sendBorder(const Rect<float>& pos, float height = 10.0f) {
	const uint count = 10;

	sendHLines( Point<float>(pos.left, pos.top), Point<float>(pos.right, pos.top), height, count );
	sendHLines( Point<float>(pos.left, pos.bottom), Point<float>(pos.right, pos.bottom), height, count );
	sendHLines( Point<float>(pos.left, pos.top), Point<float>(pos.left, pos.bottom), height, count );
	sendHLines( Point<float>(pos.right, pos.top), Point<float>(pos.right, pos.bottom), height, count );
}

void sendHLines( const Rect<int>& area, float minh = -50.0f, float maxh = 250.0f ) {
	glVertex3f( area.left, minh, area.top );
	glVertex3f( area.left, maxh, area.top );

	glVertex3f( area.left, minh, area.bottom );
	glVertex3f( area.left, maxh, area.bottom);

	glVertex3f( area.right, minh, area.bottom );
	glVertex3f( area.right, maxh, area.bottom );

	glVertex3f( area.right, minh, area.top );
	glVertex3f( area.right, maxh, area.top );
}

void geomclip::Terrain::sendVertex(const Point<float>& v) {
	borderVertices_->push_back( Vector3f(v.x, heightmapSource_->heightAt(v.x, v.y), v.y) );
	//glVertex3f( v.x, heightmapSource_->heightAt(v.x, v.y), v.y );
}

void geomclip::Terrain::transitionStripes(
	const Point<float>& thestart, const Point<float>& theend, int level, float width) 
{
	const uint levelScale = powi(2, level);

	const Rect<float> outerBorder = Rect<float>(regions_[level-1]->getActiveRegion());
	Point<float> start = clipInto( thestart, outerBorder );
	Point<float> end = clipInto( theend, outerBorder );

	const int startEndDistance = abs( start.x - end.x ) + abs( start.y - end.y );
	const int stepCount = startEndDistance / levelScale;

	Point<float> step = Point<float>(end - start);
	step.x /= stepCount;
	step.y /= stepCount;

	Point<float> perp = Point<float>( step.y, -step.x );
	perp *= width / perp.length();

	Rect<int> outerBorderi = Rect<int>( outerBorder );
	Point<float> perp2 = perp * 0.9f;
	Point<int> outerStart = Point<int>( thestart + perp2 );
	Point<int> outerEnd = Point<int>( theend + perp2 );

	//if( !outerBorderi.contains(outerStart) && !outerBorderi.contains(outerEnd) ) {
	//	return;
	//}
	GCT_ASSERT( start.x == end.x || start.y == end.y );

	Point<float> pos = Point<float>( start );

	for( uint stepNum = 0; stepNum < stepCount; ++stepNum, pos += step ) {
		const Point<float> vs = pos + step;
		const Point<float> vsp = pos + perp + (step*0.5f);
		
		sendVertex( pos );
		sendVertex( vsp );
		sendVertex( pos + perp );

		sendVertex( pos );
		sendVertex( vs );
		sendVertex( vsp );

		sendVertex( vs );
		sendVertex( vs + perp );
		sendVertex( vsp );
	}
}

uint geomclip::Terrain::findDetailLevelForHoleBorder(const Rect<int>& hole) {
	uint resultingLevel = regions_.size() - 1;
	Rect<int> extrudedHole = hole;

	for( uint level = 0; level < regions_.size(); ++level ) {
		extendToMultipleOf( &extrudedHole, powi(2, level) );

		if( extrudedHole.isInsideAndSmaller(regions_[level]->updatedRegion_) ) {
			resultingLevel = level;
			break;
		}
	}

	return resultingLevel;
}

void geomclip::Terrain::renderHoleBorder(const HoleInfo& holeInfo) {
	const Rect<WorldCoord> hole = holeInfo.area;
	const uint holeDetailLevel = holeInfo.detailLevel;
	const uint holeScale = powi( 2, holeDetailLevel );
	Rect<float> regionHole = Rect<float>(hole);

	std::vector<Vector3f> vertices;
	vertices.reserve( 1000 );
	borderVertices_ = &vertices;

	for( int level = holeDetailLevel; level > 0; --level ) {
		const uint scale = powi( 2, level );
		const float stripeWidth = scale;

		regionHole = outerBorderForBorderStrip( hole, holeDetailLevel, level );

		Rect<float> outerBorder = Rect<float>(regions_[level-1]->getActiveRegion());
		outerBorder.extend( powi(2, level) );

		Rect<int> outerBorderi = regions_[level-1]->getActiveRegion();

		const float border09 = float( powi(2, level) ) * 0.9f;

		const bool leftInside = int( regionHole.left - border09 ) >= outerBorderi.left && int( regionHole.left - border09 ) < outerBorderi.right;
		const bool topInside = int( regionHole.top - border09 ) >= outerBorderi.top && int( regionHole.top - border09 ) < outerBorderi.bottom;
		const bool rightInside = int( regionHole.right + border09 ) >= outerBorderi.left && int( regionHole.right + border09 ) < outerBorderi.right;
		const bool bottomInside = int( regionHole.bottom + border09 ) >= outerBorderi.top && int( regionHole.bottom + border09 ) < outerBorderi.bottom;

		if( topInside )
			transitionStripes( regionHole.topleft(), regionHole.topright(), level, stripeWidth );
		if( rightInside )
			transitionStripes( regionHole.topright(), regionHole.bottomright(), level, stripeWidth );
		if( bottomInside )
			transitionStripes( regionHole.bottomright(), regionHole.bottomleft(), level, stripeWidth );
		if( leftInside )
			transitionStripes( regionHole.bottomleft(), regionHole.topleft(), level, stripeWidth );

		{
			Point<float> tl = Point<float>(regionHole.topleft());
			Point<float> tr( tl.x - scale, tl.y );
			Point<float> bl( tl.x, tl.y - scale );
			Point<float> br( tl.x - scale, tl.y - scale );
			Point<float> hr( tl.x - scale, tl.y - scale/2 );
			Point<float> hb( tl.x - scale/2, tl.y - scale );

			if( outerBorder.contains(tl) && outerBorder.contains(br) ) {
				sendVertex(tl); sendVertex(bl); sendVertex(tr);
				sendVertex(tr); sendVertex(bl); sendVertex(hb);
				sendVertex(tr); sendVertex(hb); sendVertex(hr);
				sendVertex(hr); sendVertex(hb); sendVertex(br);
			}
		}

		{
			Point<float> tl = Point<float>(regionHole.bottomright());
			Point<float> tr( tl.x + scale, tl.y );
			Point<float> bl( tl.x, tl.y + scale );
			Point<float> br( tl.x + scale, tl.y + scale );
			Point<float> hr( tl.x + scale, tl.y + scale/2 );
			Point<float> hb( tl.x + scale/2, tl.y + scale );

			if( outerBorder.contains(tl) && outerBorder.contains(br) ) {
				sendVertex(tl); sendVertex(bl); sendVertex(tr);
				sendVertex(tr); sendVertex(bl); sendVertex(hb);
				sendVertex(tr); sendVertex(hb); sendVertex(hr);
				sendVertex(hr); sendVertex(hb); sendVertex(br);
			}
		}

		{
			Point<float> tr = Point<float>( regionHole.topright() );
			Point<float> tl( tr.x + scale, tr.y );
			Point<float> br( tr.x, tr.y - scale );
			Point<float> bl( tr.x + scale, tr.y - scale );
			Point<float> hl( tr.x + scale, tr.y - scale/2 );
			Point<float> hb( tr.x + scale/2, tr.y - scale );

			if( outerBorder.contains(tl) && outerBorder.contains(br) ) {
				sendVertex(tr); sendVertex(tl); sendVertex(hl);
				sendVertex(tr); sendVertex(hl); sendVertex(bl);
				sendVertex(tr); sendVertex(bl); sendVertex(hb);
				sendVertex(tr); sendVertex(hb); sendVertex(br);
			}
		}

		{
			Point<float> tr = Point<float>( regionHole.bottomleft() );
			Point<float> tl( tr.x - scale, tr.y );
			Point<float> br( tr.x, tr.y + scale );
			Point<float> bl( tr.x - scale, tr.y + scale );
			Point<float> hl( tr.x - scale, tr.y + scale/2 );
			Point<float> hb( tr.x - scale/2, tr.y + scale );

			if( outerBorder.contains(tl) && outerBorder.contains(br) ) {
				sendVertex(tr); sendVertex(tl); sendVertex(hl);
				sendVertex(tr); sendVertex(hl); sendVertex(bl);
				sendVertex(tr); sendVertex(bl); sendVertex(hb);
				sendVertex(tr); sendVertex(hb); sendVertex(br);
			}
		}
	}

	VertexBuffer buffer;
	buffer.setSize( vertices.size() );
	VertexStream* xzStream = buffer.addStream( "xz", 2 );
	VertexStream* heightStream = buffer.addStream( "height", 2 );
	VertexStream* normalStream = buffer.addStream( Normals );

	const uint verticesSize = vertices.size();
	for( uint vertexNum = 0; vertexNum < verticesSize; ++vertexNum ) {
		const Vector3f& vertex( vertices[vertexNum] );

		xzStream->set2( vertexNum, vertex.x, vertex.z );
		//TODO: interpolieren..
		heightStream->set2( vertexNum, vertex.y, vertex.y );
		normalStream->set3( vertexNum, heightmapSource_->normalAt(vertex.x, vertex.z) );
	}

	//GLint maskLocation = glGetUniformLocation( shader_.program(), "ground" );
	//glUniform1i( maskLocation, 0 );
	//glActiveTexture( GL_TEXTURE0 );

	buffer.send( GL_TRIANGLES, shader_.program() );
}

void geomclip::Terrain::render() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
	//glScalef( 10.0f, 10.0f, 10.0f );
    
    glColor3f(1.f, 1.f, 1.f);

	glDisable( GL_LIGHTING );

	//for(RectList::iterator hole = holes_.begin();
	//	hole != holes_.end();
	//	++hole)
	//{
	//	Rect<float> area( hole->area );
	//	sendBorder( area, 100.0f );
	//}

	enum GeometryMode {
		RMDefault,
		RMPoints,
		RMLines
	};
	static GeometryMode renderMode = RMDefault;

	enum SurfaceMode {
		SMShaded,
		SMColored,
		SMTextured
	};
	static SurfaceMode surfaceMode = SMColored;

	static bool renderMeshes = true;
	static bool renderHoleBorders = true;

	if( glfwGetKey( '1' ) == GL_TRUE ) {
		renderMode = RMDefault;
	}
	else if( glfwGetKey( '2' ) == GL_TRUE ) {
		renderMode = RMLines;
	}
	else if( glfwGetKey( '3' ) == GL_TRUE ) {
		renderMode = RMPoints;
	}
	else if( glfwGetKey( '4' ) == GL_TRUE ) {
		surfaceMode = SMShaded;
	}
	else if( glfwGetKey( '5' ) == GL_TRUE ) {
		surfaceMode = SMColored;
	}
	else if( glfwGetKey( '6' ) == GL_TRUE ) {
		surfaceMode = SMTextured;
	}
	//else if( glfwGetKey( '4' ) == GL_TRUE ) {
	//	renderMeshes = true;
	//}
	//else if( glfwGetKey( '5' ) == GL_TRUE ) {
	//	renderMeshes = false;
	//}
	//else if( glfwGetKey( '6' ) == GL_TRUE ) {
	//	renderHoleBorders = true;
	//}
	//else if( glfwGetKey( '7' ) == GL_TRUE ) {
	//	renderHoleBorders = false;
	//}

	GLenum polygonMode = GL_FILL;

	switch( renderMode ) {
		case RMLines: polygonMode = GL_LINE; break;
		case RMPoints: polygonMode = GL_POINT; break;
	}
	glPolygonMode( GL_FRONT_AND_BACK, polygonMode );

	const uint regionsSize = regions_.size();

	if( false ) {
		glActiveTexture( GL_TEXTURE1 );
		if( renderMode == RMDefault && surfaceMode == SMTextured ) {
			glBindTexture( GL_TEXTURE_2D, texture_ );
		}
		else {
			glBindTexture( GL_TEXTURE_2D, fakeMask_ );
		}
	}

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, fakeMask_ );

	shader_.bind();
	GLint maskLocation = glGetUniformLocation( shader_.program(), "mask" );
	glUniform1i( maskLocation, 1 );
	GLint maskTexScale = glGetUniformLocation( shader_.program(), "maskTexScale" );
	glUniform1f( maskTexScale, 1.0f );
	GLint maskTexOffset = glGetUniformLocation( shader_.program(), "maskTexOffset" );
	glUniform2f( maskTexOffset, 0.0f, 0.0f );

	for(RectList::const_iterator holeIter = holes_.begin();
		holeIter != holes_.end();
		++holeIter)
	{
		if( surfaceMode == SMColored )
			glColor3f( 1.f, 0.8f, 0.8f );
		else
			glColor3f( 1.f, 1.f, 1.f );

		renderHoleBorder( *holeIter );
	}
	shader_.unbind();

    for(uint i = 0; i < regionsSize; ++i) {
        LodRegion* region = regions_[i];
        float scale = pow(2.0f, float(i));
        
        glPushMatrix();
        Rect<int> activeRegion = region->getActiveRegion();
        glTranslatef(activeRegion.left, 0.f, activeRegion.top);
        //glScalef(scale, 1.0f, scale);

		shader_.bind();

		const GLint vertexScaleLoc = glGetUniformLocation( shader_.program(), "vertexScale" );
		glUniform1f( vertexScaleLoc, scale );

		//GLint maskLocation = glGetUniformLocation( shader_.program(), "ground" );
		glUniform1i( maskLocation, 1 );

		glUniform1f( maskTexScale, 1.0f / float(REGION_SIZE) );
		glUniform2f( maskTexOffset, 0.0f, 0.0f );

		const GLint textureOffsetLoc = glGetUniformLocation( shader_.program(), "textureOffset" );
		glUniform2f(
			textureOffsetLoc,
			mymod( float(region->desiredRegion_.left) / float(scale), REGION_SIZE ) / float(REGION_SIZE),
			mymod( float(region->desiredRegion_.top) / float(scale), REGION_SIZE ) / float(REGION_SIZE) );
		//glUniform2f( textureOffsetLoc, 0.0f, 0.0f );

		if( renderMode != RMDefault ) {
			glPushMatrix();
			glTranslatef( 0.f, -1.f, 0.f );

			glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
			glPolygonMode( GL_FRONT, GL_FILL );

			glEnable( GL_CULL_FACE );
			glPushAttrib( GL_CULL_FACE );
			glCullFace( GL_BACK );
			region->render();
			glPopAttrib();

			glPolygonMode( GL_FRONT_AND_BACK, polygonMode );
			glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );

			glPopMatrix();
		}

		if( surfaceMode == SMColored )
			glColorForDetailLevel(i);
		else
			glColor3f( 1.f, 1.f, 1.f );

		if( renderMeshes ) {
			region->render();
		}

		if( glfwGetKey( GLFW_KEY_F10 ) == GL_TRUE ) {
			glDisable( GL_DEPTH_TEST );
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
		}
		region->renderGap();
		glEnable( GL_DEPTH_TEST );
		glPolygonMode( GL_FRONT_AND_BACK, polygonMode );

		shader_.unbind();

		//glColor4fv( colors + (4 * (i % colorCount)) );
		//sendBorder( Rect<float>(0.0f, 0.0f, REGION_SIZE, REGION_SIZE), 100.0f ); 
        
        glPopMatrix();
    }
    //shader_.unbind();

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glPopMatrix();
}

float totalSeconds = 0.0f;

void geomclip::Terrain::update(float seconds) {
    totalSeconds += seconds;

	const uint regionsSize = regions_.size();
	for(int regionIndex = 0; regionIndex < regionsSize; ++regionIndex) {
		LodRegion* region = regions_[regionIndex];

		region->setCenter( int(camera_.pos.x), int(camera_.pos.z) );
	}

	const RectList::iterator holesEnd = holes_.end();
	for(RectList::iterator hole = holes_.begin();
		hole != holesEnd;
		++hole)
	{
		uint oldDetailLevel = hole->detailLevel;
		hole->detailLevel = findDetailLevelForHoleBorder( hole->area );

		if( oldDetailLevel != hole->detailLevel ) {
			const uint regionsSize = regions_.size();
			for( uint level = 0; level < regionsSize; ++level ) {
				regions_[level]->maskTextureUpdateRequired_ = true;
			}
		}
	}

	for(int regionIndex = 0; regionIndex < regionsSize; ++regionIndex) {
        LodRegion* region = regions_[regionIndex];
            
        region->update(1);
    }
}

uint geomclip::Terrain::getSize() const {
    return heightmapSource_->getSize();
}

void geomclip::Terrain::tellCamera(const Orientation& cam) {
    camera_ = cam;
	//camera_.pos.x = 0.0f;

    //std::cout << "cam "
    //          << cam.pos.x << ", "
    //          << cam.pos.y << ", "
    //          << cam.pos.z << std::endl;
}

void geomclip::Terrain::invalidate() {
	const uint regionsSize = regions_.size();
	for( uint i = 0; i < regionsSize; ++i ) {
		regions_[i]->updatedRegion_.set( 0, 0, 0, 0 );
	}
}

VertexBuffer* LodObject::getSubArea(const Rect<int>& area, uint level, HeightmapSource* heightmapSource) {
	const uint levelScale = powi( 2, level );

	VertexBuffer* vb = new VertexBuffer();
	const uint w = (area.width() / levelScale) + 1;
	const uint h = (area.height() / levelScale) + 1;
	vb->setSize( w * h );
	VertexStream* coords = vb->addStream( Coords );

	uint index = 0;
	for( uint z = area.top; z < area.bottom + levelScale; z += levelScale )
		for( uint x = area.left; x < area.right + levelScale; x += levelScale ) {
			coords->set3( index, x, heightmapSource->heightAt(x, z), z );

			++index;
		}
		GCT_ASSERT( index == vb->getSize() );

		addRegularGridIndices( vb, w, h );

		return vb;
}

LodObject::LodObject( HeightmapSource* heightmapSource, const Rect<int>& area ) {
	lodVertices.resize( LOD_LEVEL_COUNT );

	for( uint level = 0; level < LOD_LEVEL_COUNT; ++level ) {
		Rect<int> fillArea = area;

		extendToMultipleOf( &fillArea, powi(2, level) );

		lodVertices[level] = getSubArea( fillArea, level, heightmapSource );
	}
}

HoleFillers::~HoleFillers() {
	deleteAll( objects );
}

void HoleFillers::render( Terrain* terrain ) {
	const RectList::iterator holesEnd = holes_.end();
	RectList::iterator holeIter = holes_.begin();
	const uint holeFillersSize = objects.size();
	uint fillerNum = 0;

	for( ; holeIter != holes_.end() && fillerNum < holeFillersSize; ++holeIter, ++fillerNum ) {
		LodObject* lodObject = objects[fillerNum];
		const uint detailLevel = terrain->holeDetail( fillerNum );
		VertexBuffer* vb = lodObject->lodVertices[detailLevel];

		glColorForDetailLevel( detailLevel );
		vb->send( GL_TRIANGLE_STRIP, 0 );			
	}
}

void HoleFillers::addLodRegion( HeightmapSource* heightmapSource, const Rect<int>& area )
{
	objects.push_back( new LodObject(heightmapSource, area) );
	holes_.push_back( area );
}


