#ifndef V3D_VLIST_H
#define V3D_VLIST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VGenericUtils.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

//TODO: kommentar schreiben!!!!!!!!1111111111111eins

/** declare an exception for accessing an out of bounds element */
V3D_DECLARE_EXCEPTION(VListOutOfBoundsAccess, VException);
V3D_DECLARE_EXCEPTION(VUnsupportedListOperation, VException);
V3D_DECLARE_EXCEPTION(VListIntegrityCheckFailure, VException);

template<typename Type, typename Category, typename DiffType = int>
struct VIteratorTypedefs
{
	typedef Type Value;
	typedef Type* Pointer;
	typedef Type& Reference;

	typedef DiffType DifferenceType;

	typedef Value value_type;
	typedef Pointer pointer;
	typedef Reference reference;
	typedef DifferenceType difference_type;
	typedef Category iterator_category;
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

		void PutBefore(const Type& in_Value)
		{
			// create a new node
			Node* pNewNode = new Node(in_Value);

			// insert it
			if( m_pPrev )
			{
				m_pPrev->m_pNext = pNewNode;
				pNewNode->m_pPrev = m_pPrev;
			}

			m_pPrev = pNewNode;
			pNewNode->m_pNext = this;
		}

		Node* RemoveSelf()
		{
			Node* pNext = m_pNext;

            if( m_pNext ) 
			{
				m_pNext->m_pPrev = m_pPrev;
			}
			
			if( m_pPrev )
			{
				m_pPrev->m_pNext = m_pNext;
			}

			m_pPrev = 0;
			m_pNext = 0;

			delete this;
			
			return pNext;
		}
	};

	static Node* GetLast(Node* in_pFrom)
	{
		Node* pNode = in_pFrom;

		if( in_pFrom == 0 )
			return 0;

		while( pNode->GetNext() )
		{
			pNode = pNode->GetNext();
		}

		return pNode;
	};
	
	//TODO: position hinter letztem element einnehmen koennen..
	//TODO: exception bei verlassen des list range werfen
	class IterImplBase : 
		public VIteratorTypedefs<Type, std::bidirectional_iterator_tag>
	{
		Node* m_pNode;
		Node* m_pPrevious;

		void Proceed()
		{
			if( ! m_pNode )
			{
				V3D_THROW(
					VListOutOfBoundsAccess, 
					"VList::Proceed: out of bounds"
					);
			}

			m_pPrevious = m_pNode;
			m_pNode = m_pNode->GetNext();
		}

		void MoveBack()
		{
			if( m_pPrevious )
			{
				m_pNode = m_pPrevious;
				m_pPrevious = m_pPrevious->GetPrevious();
			}
			else
			{
				V3D_THROW(
					VListOutOfBoundsAccess,
					"VList::MoveBack: out of bounds"
					);
			}
		}

	protected:
        void AssignStartNode(Node* in_pNewNode)
		{
			m_pNode = in_pNewNode;
			
			if( m_pNode )
				m_pPrevious = m_pNode->GetPrevious();
			else
				m_pPrevious = 0;
		}

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
			if( m_pNode )
			{
				return &(m_pNode->GetValue());
			}
			else
			{
				V3D_THROW(
					VListOutOfBoundsAccess,
					"VList::GetTarget accessed while pointing to last element"
					);
			}
		}

		int Compare(const IterImplBase& in_Other) const
		{
			V3D_THROW(
				VUnsupportedListOperation,
				"VList::iterators are not comparable"
				);
		}

		vbool IsEqual(const IterImplBase& in_Other) const
		{
			if( m_pNode && in_Other.m_pNode )
			{
				return (m_pNode == in_Other.m_pNode);
			}
			else if( ! m_pNode && ! in_Other.m_pNode )
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		Node* GetNode() const
		{
			return m_pNode;
		}
	};

	class Iterator :
		public VBidirectionalIteratorCustumBase<Type, IterImplBase>
		//public VIteratorTypedefs<Type, std::bidirectional_iterator_tag>
	{
		//Node* GetNode() const
		//{
		//	return GetIterImpl()->GetNode();
		//}

		friend VList;

	public:
		Iterator(Node* in_pNode)
		{
			AssignStartNode(in_pNode);
		}
	};


	/** the list's head */
	Node* m_pHead;

	void CheckIntegrity()
	{
		Node* pNode = m_pHead;

		while( pNode )
		{
			if( pNode->GetPrevious() && pNode->GetPrevious()->GetNext() != pNode )
			{
				V3D_THROW(VListIntegrityCheckFailure, "node->prev->next != node");
			}

			if( pNode->GetNext() && pNode->GetNext()->GetPrevious() != pNode )
			{
				V3D_THROW(VListIntegrityCheckFailure, "node->next->prev != node");
			}

			pNode = pNode->GetNext();
		}
	}

public:
	VList()
	{
		m_pHead = 0;
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
		iterator last(GetLast(m_pHead));

		if( m_pHead != 0 )
			++last;

		return last;
	}

	void push_back(const Type& in_Val)
	{
		Node* pLast;

		if( m_pHead )
		{
			Node* pLast = GetLast(m_pHead);

			pLast->PutBehind(in_Val);
		}
		else
		{
			m_pHead = new Node(in_Val);
			pLast = m_pHead;
		}

		CheckIntegrity();
	}

	iterator erase(iterator in_Element)
	{
		Node* pNode = in_Element.GetNode();

		if( pNode == m_pHead )
		{
			m_pHead = pNode->GetNext();
		}

		CheckIntegrity();

		return iterator(pNode->RemoveSelf());
	}

	/** insterts the element in front of the given position */
	iterator insert(iterator in_Pos, const Type& in_Value)
	{
		Node* pNode = in_Pos.GetNode();

		pNode->PutBefore(in_Value);

		if( pNode == m_pHead )
		{
			m_pHead = pNode->GetPrevious();
		}

		CheckIntegrity();

		return iterator(pNode->GetPrevious());
	}

	void clear()
	{
		delete m_pHead;
		m_pHead = 0;
	}

	vuint size()
	{
		int nSize = 0;

		Node* pNode = m_pHead;

		while( pNode != 0 )
		{
			pNode = pNode->GetNext();
			++nSize;
		}

		return nSize;
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d

//-----------------------------------------------------------------------------
#endif // V3D_VLIST_H
