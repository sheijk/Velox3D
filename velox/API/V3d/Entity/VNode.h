/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VNODE_2007_05_18_H
#define V3D_VNODE_2007_05_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
	namespace xml {
		class IVXMLElement;
	}

	namespace messaging {
		class VMessage;
		class VMessageInterpreter;
	}
}

namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A node is the basic block of the velox entity system (scene graph). 
 * You can find an introduction to the entity in the velox trac at
 * http://www.sechsta-sinn.de/velox
 *
 * Nodes can receive message using the Send method.
 *
 * A node can provide properties which have a name and a value. These are
 * automatically serialized in the Load/Save methods and can be edited by the
 * velox editor. If a class provides properties it has to override the methods
 * GetMessageInterpreterForClass and SetupProperties. For the first one simply
 * copy the implementation in VNode.cpp to your new class (the message
 * interpreter is specific for a class, so every class needs to provide it's
 * own one). To provide properties, use the AddOption methods in
 * VMessageInterpreter in SetupProperties. Be sure to call the method for
 * super to get super classes' properties
 *
 * @author sheijk
 *
 * @see IVPart
 * @see VEntity
 */
class VNode
{
public:
	VNode();
	virtual ~VNode();

	virtual void Load(const xml::IVXMLElement& in_Element) = 0;
	virtual void Save(xml::IVXMLElement& in_Element) = 0;

	enum ActivationResult
	{
		ActivatedAll, ActivatedSome, ActivatedNone
	};

	/** When called, the part has to register itself to it's subsystem */
	virtual ActivationResult Activate();

	/** When called, the part has to unregister itself from it's subsystem */
	virtual void Deactivate();

	/** Send a message to the part. Used by the serialization manager, the
	 * editor and maybe in the future to notify parts about events */
	void Send(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

private:
	/** 
	* Each node class needs it's own message interpreter, return the correct
	* one for this classes instance
	*/
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();

protected:
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	virtual void OnActivate();
	virtual void OnDeactivate();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VNODE_2007_05_18_H

