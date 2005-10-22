#include <V3dLib/Utils/VRegisterGuard.h>
//-----------------------------------------------------------------------------

#include <functional>
#include <algorithm>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace std;

namespace {
	//static std::set<VRegisterGuardBase*> m_Guards;
	struct Node
	{
		Node* next;
		VRegisterGuardBase* object;
	};

	static Node* nodes = 0;
	static Node* lastNode = 0;
}

void VRegisterGuardBase::RegisterAll()
{
	Node* currentNode = nodes;
	while(currentNode)
	{
		currentNode->object->Register();
		currentNode = currentNode->next;
	}
	//for_each(m_Guards.begin(), m_Guards.end(), 
	//	std::mem_fun(VRegisterGuardBase::Register));
}

void VRegisterGuardBase::UnregisterAll()
{
	Node* currentNode = nodes;
	while(currentNode)
	{
		currentNode->object->Unregister();
		currentNode = currentNode->next;
	}
	//for_each(m_Guards.begin(), m_Guards.end(), 
	//	mem_fun(VRegisterGuardBase::Unregister));
}

void VRegisterGuardBase::Register(VRegisterGuardBase* in_pGuard)
{
	Node* newNode = reinterpret_cast<Node*>(malloc(sizeof(Node)));
	newNode->object = in_pGuard;
	newNode->next = 0;

	if( lastNode == 0 )
	{
		lastNode = newNode;
		nodes = newNode;
	}
	else
	{
		lastNode->next = newNode;
		lastNode = newNode;
	}

	//m_Guards.insert(in_pGuard);
}

void VRegisterGuardBase::Unregister(VRegisterGuardBase* in_pGuard)
{
	//m_Guards.erase(in_pGuard);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
