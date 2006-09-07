/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

%include "../../API/V3d/Messaging/VMessage.h"
%extend v3d::messaging::VMessage {
	%template(AddProperty) AddProperty<std::string>;
	%template(AddProperty) AddProperty<int>;
	%template(AddProperty) AddProperty<float>;
	
	%template(GetAsString) GetAs<std::string>;
	%template(GetAsInt) GetAs<int>;
	%template(GetAsFloat) GetAs<float>;
};
%include "../../API/V3d/Messaging/VProtocol.h"


