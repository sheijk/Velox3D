/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVMESSAGE_2004_11_04_H
#define V3D_IVMESSAGE_2004_11_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Core/VException.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

V3D_DECLARE_EXCEPTION(VInvalidMessageTypeException, VException)

enum VMessageTreatment
{
	MessageProcessed,
	MessageIgnored
};

/**
 * Base class for messages which can be sent between plugins, the editor suite
 * and the active editor. Concrete message classes are derived from this which
 * provide the nessecary data
 *
 * @author sheijk
 */
class IVMessage
{
public:
	/** make the type polymorph */
	virtual ~IVMessage() {}

	/**
	 * Returns a reference to a message of the type MessageType if the message
	 * is an instance of MessageType or a child class of it. Will throw an 
	 * exception of type VInvalidMessageTypeException if the exception type
	 * does not match
	 */
    template<typename MessageType>
	inline MessageType& Convert();

	template<typename MessageType>
	inline const MessageType& Convert() const;


	/** Returns whether the message is of the given message type */
	template<typename MessageType>
	inline vbool IsOfType() const;
};

//-----------------------------------------------------------------------------

template<typename MessageType>
MessageType& IVMessage::Convert()
{
	try
	{
		MessageType* pMessage = dynamic_cast<MessageType*>(this);

		if( pMessage != 0 )
		{
			return *pMessage;
		}
	}
	catch(std::bad_cast&)
	{}

	V3D_THROW(
		VInvalidMessageTypeException, 
		"tried to cast message to an invalid type"
		);
}

template<typename MessageType>
const MessageType& IVMessage::Convert() const
{
	try
	{
		const MessageType* pMessage = dynamic_cast<const MessageType*>(this);

		if( pMessage != 0 )
		{
			return *pMessage;
		}
	}
	catch(std::bad_cast&)
	{}

	V3D_THROW(
		VInvalidMessageTypeException, 
		"tried to cast message to an invalid type"
		);
}

template<typename MessageType>
vbool IVMessage::IsOfType() const
{
	try
	{
		return &(Convert<MessageType>()) != 0;
	}
	catch(VInvalidMessageTypeException&)
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_IVMESSAGE_2004_11_04_H

