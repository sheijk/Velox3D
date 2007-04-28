#include "VertexBuffer.h"
#include "OpenGL.h"

using namespace geomclip;


uint VertexStream::defaultElements(Kind kind) {
    switch( kind ) {
    case CoordKind: return 3;
    case NormalKind: return 3;
    case ColorKind: return 4;
    default: return 0;
    }
}

VertexStream::Kind VertexStream::kind(const std::string& name) {
    if( name == "gl_Position" )
        return CoordKind;
    else if( name == "gl_Normal" )
        return NormalKind;
    else if( name == "gl_Color" )
        return ColorKind;
    else
        return CustomKind;
}

VertexStream::VertexStream() {
    count_ = 0;
    elements_ = 0;
	firstElementNum_ = 0;
    kind_ = NoneKind;
}

void VertexStream::setData(uint count, const std::string& name, uint elements) {
    count_ = count;
    name_ = name;
    elements_ = elements;
    kind_ = kind( name );
    if( DEFAULT_STREAM_ELEMENTS == elements_ )
        elements_ = defaultElements( kind_ );

    data_.resize(count_ * elements_);
}

template<typename T>
bool bitset(T value, T bits) {
    return (value & bits) == bits;
}

void VertexStream::bind(GLint program) {
	const uint firstIndex = firstElementNum_ * elements_;
	float* data = &data_[firstIndex];

    if( name_.length() > 0 ) {
        switch( kind_ ) {
        case CoordKind: {
            glEnableClientState( GL_VERTEX_ARRAY );
            glVertexPointer( elements_, GL_FLOAT, 0, data );
        } break;
        case NormalKind: {
            glEnableClientState( GL_NORMAL_ARRAY );
            glNormalPointer( GL_FLOAT, 0, data );
        } break;
        case CustomKind: {
            GLint loc = glGetAttribLocation(program, name_.c_str());

            if( loc >= 0 ) {
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, elements_, GL_FLOAT, 0, 0, data);
            }
        } break;
		default: GCT_ASSERT( false );
        }
    }
}

void VertexStream::unbind(GLint program) {
    GLint loc = 0;
	
	if( program != 0 ) {
		glGetAttribLocation( program, name_.c_str() );
	}

    if( loc >= 0 ) {
        glDisableVertexAttribArray(loc);
    } else {
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
    }
}

void VertexStream::set2(uint index, float a, float b) {
	GCT_ASSERT( index < count_ );
    float* dest = &data_[0] + (index * elements_);

    dest[0] = a;
    dest[1] = b;        
}

void VertexStream::set3(uint index, float a, float b, float c) {
	GCT_ASSERT( index < count_ );
    float* dest = &data_[0] + (index * elements_);

    dest[0] = a;
    dest[1] = b;
    dest[2] = c;
}

void VertexStream::set3(uint index, const Vector3f& vec) {
	GCT_ASSERT( index < count_ );
    set3( index, vec.x, vec.y, vec.z );
}

void VertexStream::set4(uint index, float a, float b, float c, float d) {
	GCT_ASSERT( index < count_ );
    float* dest = &data_[0] + (index * elements_);

    dest[0] = a;
    dest[1] = b;
    dest[2] = c;
    dest[3] = d;
}

uint VertexStream::getElements() const {
    return elements_;
}

uint VertexStream::getCount() const {
    return count_;
}

float geomclip::VertexStream::get( uint index ) const
{
	const float* dest = &data_[0] + (index * elements_);
	return *dest;
}

Vector3f VertexStream::get3(uint index) const {
    const float* dest = &data_[0] + (index * elements_);

    return vector3f(dest[0], dest[1], dest[2]); 
}

void VertexStream::get3(uint index, float* x, float* y, float* z) const {
    const float* dest = &data_[0] + (index * elements_);
   
    *x = dest[0];
    *y = dest[1];
    *z = dest[2];
}

uint VertexStream::getFirstElementNum() const {
	return firstElementNum_;
}

void VertexStream::setFirstElementNum(uint newFirstElementNum) {
	//GCT_ASSERT( (newFirstElementNum + count_) * elements_ <= data_.size() );

	firstElementNum_ = newFirstElementNum;
}

//------------------------------------------------------------------------------

VertexBuffer::VertexBuffer() {
    vertexCount_ = 0;
    indexCount_ = 0;
}

void VertexBuffer::send(GLenum primitive, GLint program) {
	if( vertexCount_ > 0 ) {
		bindStreams( program );

		if( indexCount_ <= 0 ) {
			glDrawArrays(primitive, 0, vertexCount_);
		}
		else {
			glDrawElements(primitive, indexCount_, GL_UNSIGNED_INT, &indices_[0]);
		}

		unbindStreams( program );
	}
}

void VertexBuffer::send(GLenum primitive, const std::vector<int>& indices, GLint program) {
	if( vertexCount_ > 0 ) {
		bindStreams( program );

		glDrawElements( primitive, indices.size(), GL_UNSIGNED_INT, &indices[0] );

		unbindStreams( program );
	}
}

void VertexBuffer::bindStreams(GLint program) {
	for(StreamMap::iterator stream = streams_.begin();
		stream != streams_.end();
		++stream) {
			stream->second->bind(program);
	}
}

void VertexBuffer::unbindStreams(GLint program) {
	for(StreamMap::iterator stream = streams_.begin();
		stream != streams_.end();
		++stream) {
			stream->second->unbind(program);
	}
}

void VertexBuffer::showNormals(float length) {
    VertexStream* coords = getStream(Coords);
    VertexStream* normals = getStream(Normals);

    glBegin(GL_LINES);
    for(uint vertexNum = 0; vertexNum < vertexCount_; ++vertexNum) {
        Vector3f pos = coords->get3(vertexNum);
        Vector3f normalEnd = pos + (normals->get3(vertexNum) * length);

        glVertex3f(pos.x, pos.y, pos.z);
        glVertex3f(normalEnd.x, normalEnd.y, normalEnd.z);
    }
    glEnd();
}
    
void VertexBuffer::setSize(uint newSize) {
    for(StreamMap::iterator stream = streams_.begin();
        stream != streams_.end();
        ++stream) {
        stream->second->setData(newSize, stream->first, stream->second->getElements());
    }

    vertexCount_ = newSize;
}

uint VertexBuffer::getSize() const {
    return vertexCount_;
}

VertexStream* VertexBuffer::addStream(const std::string& name, uint elements, uint streamVertexCount) {
	if( 0 == streamVertexCount )
		streamVertexCount = vertexCount_;

	GCT_ASSERT( streamVertexCount >= vertexCount_ );

    StreamMap::iterator it = streams_.find(name);
    
    if( it == streams_.end() ) {
        VertexStream* pStream = new VertexStream();
        pStream->setData(streamVertexCount, name, elements);
		elements = pStream->getElements();
        
        streams_.insert(StreamMap::value_type(name, pStream));
        it = streams_.find(name);
    }

	if( it->second->getElements() == elements )
		return it->second;
	else
		return NULL;
}

VertexStream* VertexBuffer::getStream(const std::string& name) {
    StreamMap::iterator stream = streams_.find(name);

    if( stream != streams_.end() )
        return stream->second;
    else
        return 0;
}

void VertexBuffer::setIndexCount(uint newCount) {
    indices_.resize(newCount);
    indexCount_ = newCount;
}

uint VertexBuffer::getIndex(uint num) const {
    return indices_[num];
}

void VertexBuffer::setIndex(uint num, uint index) {
    indices_[num] = index;
}


