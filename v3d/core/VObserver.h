//
// *** VObserver ***
//
// synopsis:
//    - Implements the observer pattern
//
// author: 
//	  - Ray Virzi
//	  - taken from http://www.codeguru.com/cpp_mfc/virzi_observer.shtml
//

#ifndef V3D_VOBSERVER_H
#define V3D_VOBSERVER_H

#include <list>
#include <vector>

class VObserver;

class VSubject
{
public :

	virtual void Attach(VObserver* in_pObserver);
	virtual void Detach(VObserver* in_pObserver);
	virtual void Notify(void);

protected :

	VSubject(void);
	virtual ~VSubject(void);

	std::list<VObserver*> m_Observers;
};

class VObserver
{
public :

	virtual void UpdateFromSubject(VSubject* in_pSubject) = 0;

protected :

	VObserver(void);
	virtual ~VObserver(void);
};

template <class T> class VActiveObserver
{
protected :

	T& m_ToObserve;
	T m_OriginalObject;

	VActiveObserver(void);
	virtual ~VActiveObserver(void);

public :

	virtual void CheckSubject(void)
	{
		if (m_ToObserve != m_OriginalObject)
		{
			UpdateFromSubject();
			m_OriginalObject = m_ToObserve;
		}
	}

	void SetSubject(T& in_rSubject)
	{
		m_ToObserve = in_rSubject;
		m_OriginalObject = in_rSubject;
	}

	virtual void UpdateFromSubject(void) = 0;
};

/*
class VObserver
{
protected:
	
	VObserver();
	virtual ~VObserver();

	// copy constructor - same as default constructor
	VObserver(const VObserver& other);		

	// does nothing
	VObserver& operator=(const VObserver& other);	

	// Subject functions
	void Notify(bool propagate);
	void Notify();
	void Invalidate(VObserver *from = NULL);

	// Observer functions
	virtual void OnUpdate();
	void Update(bool propagate = false);
	bool IsDirty(VObserver& subject) const;

	// Observer functions for subject management
	void AddSubject(VObserver& subject);
	void RemoveSubject(VObserver& subject);
	void RemoveAllSubjects()
	void AddSubjectsOf(VObserver& observer);
public:
    
	bool IsObserver() const;
	bool IsSubject() const;
	void Propagate();	// same as Notify(true)
};
*/

#endif


/*
Explanation of Functions
CObserver();
// Default constructor

virtual ~CObserver();
// Destructor. Will cleanup the pointers to other observers/subjects.

CObserver(const CObserver& other);
// Copy constructor. Same as default constructor - no observer data is
// copied. Prevent default copy constructor from being generated since
// it would be incorrect.

CObserver& operator=(const CObserver& other);
// Assignment operator. Does nothing, but does prevent default
// assignment function from being generated (incorrectly).

virtual void OnUpdate();
// Update function. Override this to update your derived observer.

void Update(bool propagate = false);
// Updates the object's internal value, but only if at least one
// of its subjects is dirty (i.e., has changed since the last 
// update). The dirty flags are cleared after the update is complete.

bool IsDirty(CObserver& subject) const
// Returns true if 'subject' belongs to this observer and has changed 
// since the last update.

void Invalidate(CObserver *from = NULL);
// Invalidates this object and notifies all observers, but not if the 
// object is already invalid. There is normally no need to call this 
// function directly. An optional argument 'from' tells which subject 
// caused the invalidation. If given, only that subject's dirty flag 
// will be set, otherwise all dirty flags are set.

void Notify();
// Notifies all observers that the object has changed. Observers are
// not updated until they are needed.

void Notify(bool propagate)
// Notify with propagation. Notifies all observers that the object 
// has changed and, if 'propagate' is true, immediately propagates 
// the change to all observers as well. If 'propagate' is false and 
// an update is in progress with propagation in effect, propagation 
// will be cancelled at this observer.

void AddSubject(CObserver& subject);
// Registers a subject with this observer and then invalidates it.

void RemoveSubject(CObserver& subject);
// Unregisters a subject from this observer and then invalidates it.

void RemoveAllSubjects();
// Unregisters all subjects from this observer.

void AddSubjectsOf(CObserver& subject);
// Registers with this observer all of the subject of another observer.

bool IsObserver() const
// Returns true if this object has at least one subject.

bool IsSubject() const
// Returns true if this object has at least one observer.

Usage
To use the class, include the observer.h file in your project and then follow the steps given below. If an object is both an observer and a subject, follow both sets of steps: 
For an Observer
Derive your observer class from CObserver. Encapsulate the value of the observer so that it cannot be directly accessed by outside clients of the class. 
Override the virtual function OnUpdate() with your customized update function. Make sure the update depends on at least one other CObserver object. For efficiency, use the IsDirty() function to determine if a subject has changed since the last update. 
For any function in your class that either uses the observer's value or exposes it to an outside client, call Update() once just before the first read operation or before the value is returned, whichever comes first. NOTE: This does not apply to OnUpdate(). 
Before any call to Update(), make sure all subjects used by the OnUpdate() function have been registered by calling AddSubject() with the subject as an argument. If the viewset of the observer varies over time, use RemoveSubject() to unregister a subject that will no longer be used in OnUpdate(). There are also helper functions AddSubjectsOf() and RemoveAllSubjects() to help with registration management. 
For a Subject
Derive your subject class from CObserver. Encapsulate the value of the subject so that it cannot be directly modified by outside clients of the class. 
For any function in your class that modifies the subject's value, call Notify() once after the last modification. Only call Notify() if the value actually changed from the original value. NOTE: If your subject class is also an observer, remember to call Notify() from your customized OnUpdate() function if the update changes the value. 
That is all there is to it. Note that the functions used to create the observer/subject are all protected. Clients of your class should never have to know that they are using an object that is participating in the observer pattern. All the update management is done in the background, with the exception of a few optional public functions provided. 

Features
IMMEDIATE PROPAGATION
If a change must be propagated to all observers immediately, you can call Notify(true) just after the change is made. In case a client needs to do this for a particular change, a public function called Propagate() is provided which simply calls Notify(true). You can make your observer immediately propagate all changes by using Notify(true) wherever you would have called Notify(). Once propagation is turned on for a change, it continues all the way up unless it is specifically cancelled. This is done by called Notify(false) from within the OnUpdate() function. An observer that uses Notify(false) will cancel any further propagation beyond itself for any change that is made to it. This does not mean its observers will not get updated, but that they will not necessarily be updated immediately. You can also call Update(true) which propagates any change that occurs as a result of the update. 
CYCLIC UPDATES
Also note that the class supports cyclic updating. This is a really cool feature that allows observers to observe each other or be connected into cycles or graphs with cycles in them. Updating will continue to iterate back and forth until all values are stable. Be careful though, not all update schemes are guaranteed to stabilize. During a cyclic update, the entire network is updated before the next iteration is begun, ensuring that all values remain in sync. Cyclic updates also work during immediate propagation. 
PERTURBATIONS
If you make a change to an observer at any time other than during an update, this is called a 'perturbation', because it is assumed that the new value, since it was introduced independent of the subjects, is not the "true" value of the observer and should be erased on the next update. Thus, an observer is invalidated following such an operation. If nothing else is done, the perturbation is erased and has no effect. However, if you immediately propagate the perturbation by calling Notify(true) just after the change, it will reach the other observers and have whatever side effects it is intended to have. The change is still temporary, however, and will be erased on the next update, but now the erasure will also eventually propagate back up the perturbation path to bring things back to normal again. This is called the "relaxation" phase of the perturbation. 
SELF REFERENCE
It should be rare case, but if you wish to have an observer that observes itself, just call 'AddSubject(*this)' and it should work, assuming that such an object has an OnUpdate() that will converge. A more common form of self-refernce is an object, such as a container, whose subjects are objects within itself, or vice versa. This also does not seem like a very common usage since it is easy to handle class members internally via dedicated member functions. However, if you have pre-made observer classes and don't want to re-write the interface, you may choose to hook them up in this manner. 
COPY SEMANTICS
The copy constructor for CObserver does not copy any of the data members to the new class. This includes the object's subjects, observers, and current state. If you copy construct a CObserver object, you are essentially creating a new observer. If you are copying a subject, you would not want its observers to watch both copies. If you are copying an observer, however, you may in fact wish for the new observer to watch the same subjects as the first. This decision is left to the programmer and aided by the function AddSubjectsOf(), which calls AddSubject() for each subject in the source object. This function does not remove any existing subjects, so call RemoveAllSubjects() first if that is your intention. 
The assignment operator for CObserver does nothing. If you are assigning a new value to an observer or subject, you will want to make sure the environment that the observer lives in remains unchanged. Even if the derived class does not implement operator=(), the compiler will still use this dummy assignment operator for the base class, ensuring correct copy semantics for both base and derived portions. 

CONST TYPES
Although the read-only functions are designed to be const-correct, you are not allowed to pass a const observer into any of the functions which take CObserver as an argument. This is because both observers and subjects are by their definition mutable objects. I don't think this will cause any real problems, but I have yet to discover if this is true. 
DUPLICATE REGISTRATION
If you try to add the same subject to an observer twice, the second registration is ignored. If you try to unregister a subject that the observer does not own, this will also be ignored. The fact that you are not warned about an illegal registration operation seems to be a good trade-off for making the bookkeeping easier. 
*/