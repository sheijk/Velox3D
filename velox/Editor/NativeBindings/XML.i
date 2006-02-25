%template(VXMLAttributeIterator) v3d::VRangeIterator<v3d::xml::IVXMLAttribute>;
%template(VXMLNodeIterator) v3d::VRangeIterator<v3d::xml::IVXMLNode>;
%include "../../API/V3d/XML/IVXMLNode.h"
%include "../../API/V3d/XML/IVXMLAttribute.h"
%include "../../API/V3d/XML/IVXMLComment.h"
%ignore v3d::xml::IVXMLElement::GetFirstAttribute;
%ignore v3d::xml::IVXMLElement::NextAttribute;
%ignore v3d::xml::IVXMLElement::VisitChildren;
%include "../../API/V3d/XML/IVXMLElement.h"
%include "../../API/V3d/XML/IVXMLText.h"

%ignore v3d::xml::IVXMLService::CreateXMLWriter;
%ignore v3d::xml::IVXMLService::Visit;
%template(VXMLElementPtr) v3d::VSharedPtr<v3d::xml::IVXMLElement>;
%include "../../API/V3d/XML/IVXMLService.h"

%include "../../API/V3d/XML/XMLUtils.h"

