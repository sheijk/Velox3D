#ifndef V3D_VLIST_H
#define V3D_VLIST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VGenericUtils.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/** declare an exception for accessing an out of bounds element */
V3D_DECLARE_EXCEPTION(VOutOfBoundsAccess, VException);

template<typename Type, typename DiffType = int>
struct VIteratorTypedefs
{
	typedef Type Value;
	typedef Type* Pointer;
	typedef Type& Reference;

	typedef DiffType DifferenceType;
};

/**
 * A generic list template
 */
template<typename Type>
class VList
{
	class Node
	{
		Node* m_pPrev;
		Node* m_pNext;
		Type m_Value;

	public:
		Node(const Type& in_Val) :
			m_Value(in_Val)
		{
			m_pPrev = m_pNext = 0;
		}

		Node() :
		m_Value()		
		{
			m_pPrev = 0;
			m_pNext = 0;
		}

		~Node()
		{
			if( m_pPrev )
			{
				m_pPrev->m_pNext = 0;
			}

			if( m_pNext )
			{
				delete m_pNext;
			}
			m_pNext = m_pPrev = 0;
		}

		Type& GetValue()
		{
			return m_Value;
		}

		Node* GetNext() const
		{
			return m_pNext;
		}

		Node* GetPrevious() const
		{
			return m_pPrev;
		}

		void PutBehind(const Type& in_Value)
		{
			// create a new node
			Node* pNewNode = new Node(in_Value);

			// insert it
			if( m_pNext )
			{
				m_pNext->m_pPrev = pNewNode;
				pNewNode->m_pNext = m_pNext;
			}
			
			m_pNext = pNewNode;
			pNewNode->m_pPrev = this;
		}

		void RemoveNext()
		{
			if( m_pNext )
			{
				delete m_pNext;
				m_pNext = 0;
			}
		}
	};

	static Node* GetLast(Node* in_pFrom)
	{
		Node* pNode = in_pFrom;

		while( pNode->GetNext() )
		{
			pNode = pNode->GetNext();
		}

		return pNode;
	};

	class IterImplBase : public VIteratorTypedefs<Type>
	{
		Node* m_pNode;

		void Proceed()
		{
			m_pNode = m_pNode->GetNext();
		}

		void MoveBack()
		{
			m_pNode = m_pNode->GetPrevious();
		}
	protected:
        void AssignStartNode(Node* in_pNewNode)
		{
			m_pNode = in_pNewNode;
		}

	public:
		void MoveBy(int in_nDistance)
		{
			if( in_nDistance < 0 )
			{
				for( ; in_nDistance < 0; in_nDistance++)
				{
					MoveBack();
				}
			}
			else if( in_nDistance > 0 )
			{
				for( ; in_nDistance > 0; in_nDistance--)
				{
					Proceed();
				}
			}
		}

		Type* GetTarget() const
		{
			return &(m_pNode->GetValue());
		}

		int Compare(const IterImplBase& in_Other) const
		{
			Type& me(m_pNode->GetValue());
			Type& other(m_pNode->GetValue());

			return VCompare(me, other);
		}

		vbool IsEqual(const IterImplBase& in_Other) const
		{
			return (m_pNode == in_Other.m_pNode);
		}
	};

	class Iterator
		: public VBidirectionalIteratorCustumBase<Type, IterImplBase>
	{
	public:
		Iterator(Node* in_pNode)
		{
			AssignStartNode(in_pNode);
		}
	};


	/** the list's head */
	Node* m_pHead;

public:
	VList()
	{
		m_pHead = new Node();
	}

	~VList()
	{
		delete m_pHead;
	}

	typedef Iterator iterator;

	iterator begin()
	{
		return iterator(m_pHead);
	}

	iterator end()
	{
		return iterator(GetLast(m_pHead));
	}

	//iterator push_back(const Type& in_Val)
	//{
	//	Node* pLast = m_pHead->GetLast();
	//	
	//	pLast->PutBehind(in_Val);

	//	return iterator(pLast);
	//}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VLIST_H
