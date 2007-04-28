#include "CompressedHeightmapSource.h"

#include <vector>
#include <limits>
#include <iostream>
#include "Utils.h"

namespace geomclip {

	namespace {
		const uint NODE_SIZE = 4;
	}

	namespace {
		template<typename OutputType, typename T>
		void printArray2d(const std::vector<T>& v, uint size) {
			using namespace std;

			cout << "\n";

			cout.precision(2);
			cout << fixed;

			for( uint y = 0; y < size; ++y ) {
				for( uint x = 0; x < size; ++x ) {
					cout << OutputType(v[x + y * size]) << " ";
				}
				cout << "\n";
			}

			cout << "\n";
		}
	}

	class Node {
		friend class CompressedHeightmapSource;
	private:
		/** diffs between interpolated heights of parent and real heights */
		std::vector<s8> diffs_;
		float scale_;
		float base_;
		uint size_;

		uint basex_;
		uint basey_;

		std::vector<Node*> childs_;

		Node(const Node&);
		void operator=(const Node&);
	public:
		Node() {
			basex_ = basey_ = 0;
			size_ = 0;
			base_ = 0.0f;
			scale_ = 1.f;
			childs_.resize(4);
		}

		~Node() {
			for( uint childNum = 0; childNum < childs_.size(); ++childNum ) {
				delete childs_[childNum];
				childs_[childNum] = 0;
			}
		}

		void init(uint size, float scale) {
			size_ = size;
			diffs_.resize( size_ * size_ );

			scale_ = scale;
		}

		void init( HeightmapSource* source, Node* parent, uint levelScale, uint basex, uint basey ) {
			init( NODE_SIZE, 1.0f );

			basex_ = basex;
			basey_ = basey;

			//const uint levelScale = powi( 2, level );

			std::vector<float> heights;
			heights.resize( NODE_SIZE * NODE_SIZE );

			float maxHeight = std::numeric_limits<float>::min();
			float minHeight = std::numeric_limits<float>::max();
			
			const int sourceSize = source->getSize();

			for( int y = NODE_SIZE - 1; y >= 0; --y ) {
				for( int x = NODE_SIZE - 1; x >= 0; --x ) {
					float h = 0.0f;
					
					const int xworld = basex + x*levelScale;
					const int yworld = basey + y*levelScale;

					if( xworld < sourceSize && yworld < sourceSize ) {
						h += source->heightAt( xworld, yworld );
					}

					heights[x + y * NODE_SIZE] = h;

					maxHeight = std::max( maxHeight, h );
					minHeight = std::min( minHeight, h );
				}
			}

			//if( parent != NULL ) {
			//	for( int y = 0; y < NODE_SIZE/2; ++y ) {
			//		for( int x = 0; x < NODE_SIZE/2; ++x ) {
			//			float h;

			//			if( x % 2 == 0 ) {
			//				h = parent->heightA
			//			}
			//		}
			//	}
			//}

			scale_ = ( (maxHeight - minHeight) / 255.0f );
			base_ = ( minHeight + (128.0f * (maxHeight - minHeight) / 255.0f) );

			const float scaleInv = 1.0f / scale_;

			for( int i = heights.size() - 1; i >= 0; --i ) {
				float h = heights[i];
				diffs_[i] = (h - base_) * scaleInv;
			}

			if( levelScale > 1 ) {
				const uint childLevelScale = levelScale / 2;
				const int basediff = levelScale / 2;

				for( int x = 0; x < 2; ++x ) {
					for( int y = 0; y < 2; ++y ) {
						Node* child = new Node();
						child->init( source, this, childLevelScale, basex + basediff, basey + basediff );

						childs_[x + y*2] = child;
					}
				}
			}
		}

		float diffAt(float x, float y) {
			GCT_ASSERT( x >= 0 && x < size_ );
			GCT_ASSERT( y >= 0 && y < size_ );

			return scale_ * diffs_[uint(x) + uint(y)*size_];
		}

		void transformTo(Node** node, uint* xloc, uint* yloc ) {
			const uint x = *xloc;
			const uint y = *yloc;

			GCT_ASSERT( x >= 0 && x < size_ );
			GCT_ASSERT( y >= 0 && y < size_ );

			uint num = 0;

			*xloc *= 2;
			*yloc *= 2;

			if( x >= size_/2 ) {
				num += 1;
				xloc -= size_;
			}

			if( y >= size_/2 ) {
				num += 2;
				yloc -= size_;
			}

			*node = childs_[num];
		}

		//static Node* create( uint level, uint x, uint y, uint nodeSize, Node* parent, HeightmapSource* heightmap ) {
		//}
	};

	float CompressedHeightmapSource::heightAt(float xWorld, float yWorld) {
		Node* currentNode = rootNode_;

		uint xloc = xWorld;
		uint yloc = yWorld;
		float height = 0.0f;

		while( currentNode != NULL ) {
			currentNode->transformTo( &currentNode, &xloc, &yloc );
			height += currentNode->diffAt( xloc, yloc );
		}

		return height;
	}

	bool CompressedHeightmapSource::init( HeightmapSource* source ) {
		const uint baseSize = nextPowerOf( 2, source->getSize() );
		const uint levelScale = baseSize / NODE_SIZE;

		rootNode_ = new Node();
		rootNode_->init( source, NULL, levelScale, 0, 0 );

		return false;
	}

	void CompressedHeightmapSource::print() {
		printArray2d<int>( rootNode_->diffs_, NODE_SIZE );
	}
}
