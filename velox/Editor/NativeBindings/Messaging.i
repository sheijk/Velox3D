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

