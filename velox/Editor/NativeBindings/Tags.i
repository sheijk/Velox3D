%include "../../API/V3d/Tags/VTag.h"
%include "../../API/V3d/Tags/VTagRegistry.h"

%rename(equals) v3d::tags::VTag::operator==;
%ignore v3d::tags::VTag::operator!=;

%template(VTagIterator) v3d::VRangeIterator<const v3d::tags::VTag>;
