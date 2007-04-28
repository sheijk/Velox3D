#ifndef GEOMCLIPTERRAIN_VERTEXBUFFER_H_INCLUDED
#define GEOMCLIPTERRAIN_VERTEXBUFFER_H_INCLUDED

#include "Types.h"
#include "OpenGL.h"
#include "CommonMath.h"

#include <vector>
#include <map>
#include <string>

namespace geomclip {

// enum DataType {
//     None,
//     Coords,
//     Normals,
//     Colors
// //     Custom
// };

const std::string Coords = "gl_Position";
const std::string Normals = "gl_Normal";
const std::string Colors = "gl_Color";
    
const int DEFAULT_STREAM_ELEMENTS = 0;

class VertexStream {
public:
    VertexStream();
    
    void setData(uint count, const std::string& name, uint elements = DEFAULT_STREAM_ELEMENTS);

    void bind(GLint program);
    void unbind(GLint program);

    void set2(uint index, float a, float b);
    void set3(uint index, float a, float b, float c);
    void set3(uint index, const Vector3f& vec);
    void set4(uint index, float a, float b, float c, float d);

	float get(uint index) const;
    Vector3f get3(uint index) const;
    void get3(uint index, float* x, float* y, float* z) const;

    uint getElements() const;

    uint getCount() const;

	uint getFirstElementNum() const;
	void setFirstElementNum(uint newFirstElementNum);

private:
    enum Kind { NoneKind, CoordKind, NormalKind, ColorKind, CustomKind };
    static uint defaultElements(Kind kind);
    static Kind kind(const std::string& name);

    Kind kind_;
    uint count_;
    uint elements_;
    std::vector<float> data_;
    std::string name_;
	uint firstElementNum_;
};

class VertexBuffer {
public:
    VertexBuffer();
    
    void send(GLenum primitive, GLint program);
	void send(GLenum primitive, const std::vector<int>& indices, GLint program);
    void showNormals(float length = 1.0f);

	void bindStreams(GLint program);
	void unbindStreams(GLint program);
    
    void setSize(uint newSize);
    uint getSize() const;
    
    VertexStream* addStream(
		const std::string& name, 
		uint elements = DEFAULT_STREAM_ELEMENTS,
		uint vertexCount = 0);

    VertexStream* getStream(const std::string& name);

    void setIndexCount(uint newCount);
    uint getIndex(uint num) const;
    void setIndex(uint num, uint index);

private:
    std::vector<uint> indices_;
    uint indexCount_;
    
    typedef std::map<std::string, VertexStream*> StreamMap;
    StreamMap streams_;
    uint vertexCount_;
};

} // namespace geomclip
#endif
