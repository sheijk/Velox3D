#if !defined(VSimpleMeshDescription_AE70E258_7428_45e4_9687_0D0E67025397_H)
#define VSimpleMeshDescription_AE70E258_7428_45e4_9687_0D0E67025397_H
//-------------------------------------------------------------------------
#include <v3d/Graphics/IVMeshDescription.h>

#include <map>
#include <list>

//-------------------------------------------------------------------------

class VSimpleMeshDescription : public IVMeshDescription
{
public:
	VSimpleMeshDescription();
	virtual ~VSimpleMeshDescription();
	VSimpleMeshDescription(const VSimpleMeshDescription& theVSimpleMeshDescription);

	void AddTriangle(const sVTriangle& in_Triangle);
	void AddTriangleStrip(const VTriangleGroup& in_TriangleStrip);
	void AddTriangleFan(const VTriangleGroup& in_TriangleFan);

	virtual VertexIterator VertexBegin();
	virtual VertexIterator VertexEnd();
	virtual TriangleIterator TriangleBegin();
	virtual TriangleIterator TriangleEnd();
	virtual TriangleFanIterator TriangleFanBegin();
	virtual TriangleFanIterator TriangleFanEnd();
	virtual TriangleStripIterator TriangleStripBegin();
	virtual TriangleStripIterator TriangleStripEnd();

	class VertexIdList
	{

	public:
		VertexIdList();
		virtual ~VertexIdList();
		VertexIdList(const VertexIdList& theVertexIdList);

	private:
		vector<VertexId> m_VertexIds;
	};

private:
	std::map<VertexId, Vertex> m_Vertices;
	std::list<VertexIdList> m_Triangles;
	std::list<VertexIdList> m_TriangleFans;
	std::list<VertexIdList> m_TriangleStrips;

};

//-------------------------------------------------------------------------
#endif // !defined(VSimpleMeshDescription_AE70E258_7428_45e4_9687_0D0E67025397_H)